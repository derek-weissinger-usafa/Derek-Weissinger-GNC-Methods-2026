#include <Arduino.h>
#include <Adafruit_BNO08x.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <BasicLinearAlgebra.h>
using namespace BLA;


#define SEALEVELPRESSURE_HPA (30.27 * 33.8639) //Sourced as inHg from KAFF METAR, will add functionality to auto update this later
#define BNO08X_RESET -1 // No reset pin needed for I2C

Adafruit_BNO08x  bno08x(BNO08X_RESET); //Sensor Objects
Adafruit_BME280 bme;
sh2_SensorValue_t sensor;

void setState(int state); //Set launchstate and update sensor reports accordingly
void state0(); //Manage controller when in launch state 0
void state1(); //Manage controller when in launch state 1

void setReports(int state); //Configure BNO08x Sensor Reports for different launch states
void fillMats(); //Initializes all matrix objects
int read(); // Pull raw sensor data
BLA::Matrix<4> estimate(BLA::Matrix<3> omegas, BLA::Matrix<4> quat); //Estimate Attitude w/ Quat. Propagation
void control(); // PID controller
int command(); // Write actuator output
int log(); // Log telemetry to Serial or SD Card

int launchState = 0; //Current state of launch sequence. 0: Prelaunch on pad; 1: Under Thrust; 2: Coasting; 3: Apogee reached, deploy parachute.

unsigned long currentTime; // microseconds, expect approx. 80 min before overflow.
unsigned long tempo = 10000; // microseconds, corresponds to refresh rate of 100 Hz.
unsigned long previousTime; // Allows us to check the tempo, microseconds.
unsigned long elapsed; // Time elapsed after each loop() call, microseconds
unsigned long accelTime;
unsigned long gyroTime;
unsigned long accel_dt;
unsigned long gyro_dt;
unsigned long accelTime_prev;
unsigned long gyroTime_prev;
bool newAccel;
bool newGyro;

BLA::Matrix<3> accelRaw; //Raw Accelerometer data; x,y,z order in m/s^2; updated everytime read() is called; 3x1 vector. 
BLA::Matrix<3> gyroRaw; //Raw Gyro data; x,y,z order in rad/s; updated everytime read() is called; 3x1 vector.
BLA::Matrix<3> accelAvg; //Used to keep running avg of accel data from state 0; from this we determine initial launchpad attitude;
int accelSamples; //Used to compute above avg.
BLA::Matrix<3> gyroAvg; //Used to keep running avg of gyro data from state 0; from this we determine gyro bias to correct for in state 1; element 4 stores # of samples for comp. avg.
int gyroSamples; //Used to compute above avg.
BLA::Matrix<3> gyroCal; //Gyro data corrected for bias, used in state 1.
float baroPressure; //Raw barometric pressure, hPa.
float baroAltitude; //Converted barometric altitude.

BLA::Matrix<4> attitude = {1, 0, 0, 0}; //Master Attitude Quaternion; the real part is the 0th element.

void setup() {
  fillMats(); //Initialize matrices and vectors

  Serial.begin(115200);
  while (!Serial) delay(10); // Wait until serial console opens
  unsigned bmestatus;

  //Initialize bno08x sensor, force restart if not able
  if (!bno08x.begin_I2C()) {
    Serial.println("Failed to find BNO08x chip");
    while (1) { delay(10); }
  }
  setReports(launchState);

  //Attempt to start BME280 Sensor, default settings, force restart if not able
  bmestatus = bme.begin();

  if (!bmestatus) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }


}

void loop() {
  switch (launchState) {
    case 0:
      state0();
      break;
    case 1:
      state1();
      break;
  }

}

//Change what reports the sensors generate based on the current launch state.
//State 0: High freq. Accel, low freq. gyro, low freq. altimiter
//State 1: no accel, high freq. gyro, low freq. altimiter
//State 2 & 3: no accel, no gyro, high freq. altimiter
void setReports(int state) {
  switch (state) {
    case 0:
      if (!bno08x.enableReport(SH2_ACCELEROMETER, 5000UL)) {
        Serial.println("Could not set Accelerometer.");
        break;
      }

      if (!bno08x.enableReport(SH2_GYROSCOPE_UNCALIBRATED, 10000UL)) {
        Serial.println("Could not set Gyro.");
        break;
      } 
      break;
    case 1:
      if (!bno08x.enableReport(SH2_ACCELEROMETER, 0)) {
        Serial.println("Could not set Accelerometer.");
        break;
      }

      if (!bno08x.enableReport(SH2_GYROSCOPE_UNCALIBRATED, 5000UL)) {
        Serial.println("Could not set Gyro.");
        break;
      } 
      break;
    case 2:
      break;
    }
  }
  



void fillMats() {
  accelRaw.Fill(0);
  gyroRaw.Fill(0);
  accelAvg.Fill(0);
  gyroAvg.Fill(0);
}


void setState(int state) {
  launchState = state;
  setReports(state);
}

void state0() {
  //Keep track of time
  currentTime = micros();
  elapsed = currentTime - previousTime;
  //Read any new sensor events
  read();
  //Update running accel. avg.
  if (newAccel) {
    accelAvg = ((float(accelSamples) * accelAvg) + accelRaw) / (float(accelSamples) + 1);
    accelSamples++;
    newAccel = false;
  }
  //Update running gyro. avg.
  if (newGyro) {
    gyroAvg = ((float(gyroSamples) * gyroAvg) + gyroRaw) / (float(gyroSamples) + 1);
    gyroSamples++;
    newGyro = false;
  }

  elapsed = currentTime - previousTime;
  //Log data if refresh tempo (10000 us) has passed
  if (elapsed >= tempo) {
    log();
  }

}

void state1() {
  //Keep track of time
  currentTime = micros();
  elapsed = currentTime - previousTime;
  read();

  //If new gyro reading is available, use it, otherwise use the previous one.
  if (newGyro) {
    //Compensate for bias
    gyroCal = gyroRaw - gyroAvg;
  }

  //Call only once every 10000 us.
  if (elapsed >= tempo) {
    attitude = estimate(gyroCal, attitude);
    control();
    command();
    log();
  }
  
}

//Read raw sensor data; return 1 if successful, return 0 if unable.
int read() {
  //Generate Next BNO08x Report
  if (!bno08x.getSensorEvent(&sensor)) {
    //Serial.println("No New Report available");
    return 0;
  }

  else if (sensor.sensorId == SH2_ACCELEROMETER) {
    accelRaw(0) = sensor.un.accelerometer.x;
    accelRaw(1) = sensor.un.accelerometer.y;
    accelRaw(2) = sensor.un.accelerometer.z;
    accelTime = micros(); //Debugging, seeing interval between older and latest report
    accel_dt = accelTime - accelTime_prev;
    accelTime_prev = micros();
    newAccel = true;
  }
  
  else if (sensor.sensorId == SH2_GYROSCOPE_UNCALIBRATED) {
    gyroRaw(0) = sensor.un.gyroscopeUncal.x;
    gyroRaw(1) = sensor.un.gyroscopeUncal.y;
    gyroRaw(2) = sensor.un.gyroscopeUncal.z;
    gyroTime = micros(); //Debugging, seeing interval between older and latest report
    gyro_dt = gyroTime - gyroTime_prev;
    gyroTime_prev = micros();
    newGyro = true;
   }

    //baroAltitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
    // baroPressure = bme.readPressure(); //Validate that it is in hPa
    return 1;
}

//Use gyro data to determine attitude, via quaternion integration
BLA::Matrix<4> estimate(BLA::Matrix<3> omegas, BLA::Matrix<4> quat) {
  
  BLA::Matrix<4,4> OMEGA = {0, -omegas(1), -omegas(2), -omegas(3),
           omegas(1), 0, omegas(3), -omegas(2),
           omegas(2), -omegas(3), 0, omegas(1),
           omegas(3), omegas(2), -omegas(1), 0};
  BLA::Matrix<4> qdot = 0.5f * OMEGA * quat;
  BLA::Matrix<4> quatnew = qdot * float(elapsed/1000000) + quat; 
  quatnew = quatnew / Norm(quatnew);

  return quatnew;
}

void control() {

}

//Log data to Serial Monitor
int log() { 
  Serial.print(accelAvg);
  Serial.print(",");
  Serial.println(gyroAvg);
  // Serial.print(",");
  // Serial.println(misstime);
  // Serial.print(gyroRaw(0));
  // Serial.print(",");
  // Serial.print(gyroRaw(1));
  // Serial.print(",");
  // Serial.println(gyroRaw(2));
  //Serial.println(baroAltitude);
  //newAccel = false;
  //newGyro = false;
  return 1;
}


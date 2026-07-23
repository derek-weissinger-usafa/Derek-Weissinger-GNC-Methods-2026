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

void setReports(int state=0); //Configure BNO08x Sensor Reports
void fillMats(); //Initializes all matrix objects
int read(); // Pull raw sensor data
int estimate(); // Clean up raw data, then Estimate Attitude w/ Quat. Propagation
int control(); // PID controller
int command(); // Write actuator output
int log(); // Log telemetry to Serial or SD Card

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
long misstime; // If a 100 Hz cycle was missed, store how many microseconds it missed by
int readcounter; // Count number of times read() is called before log().

BLA::Matrix<3> accelRaw; //Raw Accelerometer data; x,y,z order in m/s^2; updated everytime read() is called; 3x1 vector. 
BLA::Matrix<3> gyroRaw; //Raw Gyro data; x,y,z order in rad/s; updated everytime read() is called; 3x1 vector.
float baroPressure; //Raw barometric pressure, hPa.
float baroAltitude; //Converted barometric altitude.
bool newAccel; //Flags to indicate new data has been loaded, use them to force sensor to gather other report
bool newGyro;

BLA::Matrix<4,4> OMEGA; //Used for quaternion integration

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

  setReports();

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
  currentTime = micros();
  /*
  We call read() every loop because we want to read new data ASAP: our goal is to have a new
  accel and gyro data every 10000 microseconds, and each call of read() will only update one 
  due to the nature of the BMO08x library. Therefore we will need to execute loop at least twice
  per tempo.
  */
  read();
  
  elapsed = currentTime - previousTime;
  if (elapsed >= tempo) {
    previousTime = currentTime;
    log();
    // If we missed a cycle, count how many microseconds it missed by and increase a counter
    // if (elapsed > tempo) {
    //   misscounter++;
      misstime = elapsed - tempo;
    //   Serial.print("Missed by: ");
    //   Serial.println(misstime);
    // }
    //We only wish to log once per tempo
    

  }

}
//Change what reports the sensors generate based on the current launch state.
void setReports(int state=0) {
  Serial.println("Setting desired reports");
  if (!bno08x.enableReport(SH2_ACCELEROMETER, 10000UL)) {
    Serial.println("Could not set Accelerometer.");
  }

  if (!bno08x.enableReport(SH2_GYROSCOPE_UNCALIBRATED, 5000UL)) {
    Serial.println("Could not set Gyro.");
  } 

}

void fillMats() {
  accelRaw.Fill(0);
  gyroRaw.Fill(0);
  OMEGA.Fill(0);
}

//Read raw sensor data; return 1 if successful, return 0 if unable.
int read() {
  //Generate Next BNO08x Report
  if (!bno08x.getSensorEvent(&sensor)) {
    //Serial.println("No New Report available");
    return 0;
  }
  else if (!newAccel && sensor.sensorId == SH2_ACCELEROMETER) {
    accelRaw(0) = sensor.un.accelerometer.x;
    accelRaw(1) = sensor.un.accelerometer.y;
    accelRaw(2) = sensor.un.accelerometer.z;
    accelTime = micros(); //Debugging, seeing interval between older and latest report
    accel_dt = accelTime - accelTime_prev;
    accelTime_prev = micros();
    newAccel = true;
  }
  
  else if (!newGyro && sensor.sensorId == SH2_GYROSCOPE_UNCALIBRATED) {
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
    //Return 0 if no new report, return 1 if new report, return 2 if both reports are new.
    return newGyro+newAccel;
}


//Log data to .csv in SD card and Serial Monitor
int log() { 
  //Format: timestamp,accelx,accely,accelz,gyrox,gyroy,gyroz,altitude
  // Serial.print(accel_dt);
  // Serial.print(",");
  // Serial.print(gyro_dt);
  // Serial.print(",");
  // Serial.println(misstime);
  Serial.print(gyroRaw(0));
  Serial.print(",");
  Serial.print(gyroRaw(1));
  Serial.print(",");
  Serial.println(gyroRaw(2));
  //Serial.println(baroAltitude);
  newAccel = false;
  newGyro = false;
  readcounter = 0;
  return 1;
}
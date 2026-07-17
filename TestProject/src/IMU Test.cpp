// Basic demo for readings from Adafruit BNO08x
#include <Adafruit_BNO08x.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>


#define SEALEVELPRESSURE_HPA (30.24 * 33.8639) //Sourced as inHg from KAFF METAR, will add functionality to auto update this later


// For SPI mode, we need a CS pin
#define BNO08X_CS 10
#define BNO08X_INT 9

// For SPI mode, we also need a RESET 
//#define BNO08X_RESET 5
// but not for I2C or UART
#define BNO08X_RESET -1

Adafruit_BNO08x  bno08x(BNO08X_RESET);
Adafruit_BME280 bme;
sh2_SensorValue_t Accel;
sh2_SensorValue_t Gyro;

void setReports();

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens
  unsigned bmestatus;

  Serial.println("Adafruit BNO08x test!");

  // Try to initialize!
  if (!bno08x.begin_I2C()) {
  //if (!bno08x.begin_UART(&Serial1)) {  // Requires a device with > 300 byte UART buffer!
  //if (!bno08x.begin_SPI(BNO08X_CS, BNO08X_INT)) {
    Serial.println("Failed to find BNO08x chip");
    while (1) { delay(10); }
  }
  Serial.println("BNO08x Found!");

  for (int n = 0; n < bno08x.prodIds.numEntries; n++) {
    Serial.print("Part ");
    Serial.print(bno08x.prodIds.entry[n].swPartNumber);
    Serial.print(": Version :");
    Serial.print(bno08x.prodIds.entry[n].swVersionMajor);
    Serial.print(".");
    Serial.print(bno08x.prodIds.entry[n].swVersionMinor);
    Serial.print(".");
    Serial.print(bno08x.prodIds.entry[n].swVersionPatch);
    Serial.print(" Build ");
    Serial.println(bno08x.prodIds.entry[n].swBuildNumber);
  }

  setReports();

  Serial.println("Reading events");
  delay(100);

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

// Here is where you define the sensor outputs you want to receive
void setReports(void) {
  Serial.println("Setting desired reports");
  if (! bno08x.enableReport(SH2_ACCELEROMETER)) {
    Serial.println("Could not set Accelerometer.");
  }
 /*  if (!bno08x.enableReport(SH2_GYROSCOPE_UNCALIBRATED)) {
    Serial.println("Could not set Gyro.");
  } */

}


void loop() {
  delay(10);

  if (bno08x.wasReset()) {
    Serial.print("sensor was reset ");
    setReports();
  }

  if (! bno08x.getSensorEvent(&Accel)) {
    return;
  }

    Serial.print(Accel.un.accelerometer.x, 6);
    Serial.print(",");
    Serial.print(Accel.un.accelerometer.y, 6);
    Serial.print(",");
    Serial.println(Accel.un.accelerometer.z, 6);
    //Serial.print(",");

 /*  if (!bno08x.getSensorEvent(&Gyro)){
    return;
  } 
  
//Data Format:timestamp(s), accelerometer (m/s^2), gyro (rad/s)?, barometer (ft) 
    Serial.print(Gyro.un.gyroscopeUncal.x, 6);
    Serial.print(",");
    Serial.print(Gyro.un.gyroscopeUncal.y, 6);
    Serial.print(",");
    Serial.print(Gyro.un.gyroscopeUncal.z, 6);
    Serial.print(",");
    Serial.println(bme.readAltitude(SEALEVELPRESSURE_HPA) * 3.281); //bme func outputs m, convert to ft
 */
}
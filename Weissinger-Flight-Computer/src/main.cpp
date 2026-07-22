#include <Arduino.h>
#include <Adafruit_BNO08x.h>
#include <Adafruit_BME280.h>

// put function declarations here:
int read(); // Pull sensor data
int estimate(); // Quaternion propagation attitude estimator
int control(); // PID controller
int command(); // Write actuator output
int log(); // Log telemetry to Serial or SD Card

unsigned long currentTime; // microsseconds, expect approx. 80 min before overflow.
unsigned long tempo = 10000; // Corresponds to refresh rate of 100 Hz.
unsigned long previousTime; // Allows us to check the tempo.

int misscounter; // Count number of times 100 Hz refresh is missed.

void setup() {
  Serial.begin(115200);
}

void loop() {
  currentTime = micros();
  unsigned long interval = currentTime - previousTime;
  if (interval == tempo) {
    previousTime = currentTime;
    Serial.println("Cycle on Time");
  }
  else if (interval > tempo) {
    previousTime = currentTime;
    misscounter++;
    int missedtime = interval - tempo;
    Serial.print("Cycle, missed by: ");
    Serial.print(missedtime);
    Serial.println(" Microseconds");
  }
  delay(11); //Intentionally miss
}


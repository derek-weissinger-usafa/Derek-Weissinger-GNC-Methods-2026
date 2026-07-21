#include <Arduino.h>

// put function declarations here:
int read(); // Pull sensor data
int estimate(); // Quaternion propagation attitude estimator
int control(); // PID controller
int command(); // Write actuator output
int log(); // Log telemetry to Serial or SD Card

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
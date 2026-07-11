#include <Arduino.h>

// put function declarations here:
int speakerPin = 33;
bool isPlaying = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  //Beep for 1 sec, silent for 1 sec
  delay(1000);
  isPlaying = !isPlaying;
  digitalWrite(speakerPin, isPlaying);
}


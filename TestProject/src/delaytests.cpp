#include <Arduino.h>
/*
Created an enforceable 10000 microsecond loop, use it to blink leds at the precise right rate.

*/

//Timer Variables
const int cycletime = 10000; // Microseconds, 0.01 sec or 100 Hz
const int STM = 1000000; //Convert seconds to microseconds
unsigned int currenttime;

//Led Constants
const int led1pin = 27;
const int led1interval = 1 * STM; // 1 second
int led1state = 0;
unsigned long int previoustime1;

const int led2pin = 38;
const int led2interval = 2 * STM; // 2 seconds
int led2state = 0;
unsigned long int previoustime2;

const int led3pin = 33;
const int led3interval = 3.5 * STM; // 3.5 seconds
int led3state = 0;
unsigned long int previoustime3;

int toggleled(int, int); //See below for definition

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led1pin, OUTPUT);
  pinMode(led2pin, OUTPUT);
  pinMode(led3pin, OUTPUT);
}

void loop() {

  currenttime = micros();

  if (currenttime - previoustime1 >= led1interval) {
    previoustime1 = currenttime;
    led1state = toggleled(led1pin, led1state);
    digitalWrite(led1pin, led1state);
  }

  if (currenttime - previoustime2 >= led2interval) {
    previoustime2 = currenttime;
    led2state = toggleled(led2pin, led2state);
    digitalWrite(led2pin, led2state);
  }

  if (currenttime - previoustime3 >= led3interval) {
    previoustime3 = currenttime;
    led3state = toggleled(led3pin, led3state);
    digitalWrite(led3pin, led3state);
  }

}

int toggleled(int pin, int state) {
  if (state == HIGH) {
    return LOW;
  }
  else if (state == LOW) {
    return HIGH;
  }
}
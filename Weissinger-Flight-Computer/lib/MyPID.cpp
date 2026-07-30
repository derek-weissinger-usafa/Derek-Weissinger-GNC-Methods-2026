#include <Arduino.h>

class MyPID {
    float Kp;
    float Ki;
    float Kd;

    public:
    MyPID(float p, float i, float d) {
        Kp = p;
        Ki = i;
        Kd = d;
    }
    //Perform one step of PID calculations, interval is in microseconds
    void compute(unsigned interval) {
        float dt = interval/1000000;

        float pterm = error * Kp;

    }
};
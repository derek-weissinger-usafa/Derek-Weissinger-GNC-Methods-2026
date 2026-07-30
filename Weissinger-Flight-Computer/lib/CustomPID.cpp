#include <Arduino.h>

class CustomPID {
    float Kp;
    float Ki;
    float Kd;
    float iterm;
    float targetAngle;
    float previousAngle;
    float gimbalAngle;
    bool inAuto;
    #define MANUAL 0
    #define AUTOMATIC 1
  

    public:
    CustomPID(float p=0, float i=0, float d=0) {
        Kp = p;
        Ki = i;
        Kd = d;
        iterm = 0;
        targetAngle = 0;
        previousAngle = 0;
        gimbalAngle = 0;
        bool inAuto = false;
    }

    void setTuning(float p, float i, float d) {
        Kp = p;
        Ki = i;
        Kd = d;
    }

    //Perform one step of PID calculations.
    //interval: timestep since last called; microseconds
    //angle: measured angle to compare to desired; deg
    //Returns 1 if successful
    float compute(unsigned interval, float angle) {
        //Check to see if controller is switched on
        if (!inAuto) return;

        float dt = interval/1000000;
        float error = targetAngle - angle;
        float pterm = error * Kp;
        float dterm = (-angle + previousAngle) * Kd / dt;
        iterm += Ki * clampdown(error) * dt;
        previousAngle = angle;
        float gimbal_angle = pterm + iterm + dterm;
        return 1;
    }

    //Check to see if saturation conditions exist and if they are caused by the iterm. If so, return 0, turning the integrator off. Otherwise pass the integral term along.
    float clampdown(float passAlong) {
        if (abs(gimbalAngle) >= 5 && iterm * gimbalAngle > 0) {
            return 0;
        }
        else {
            return passAlong;
        }
    }

    void setMode(int mode) {
        inAuto = (mode == AUTOMATIC);
    }
};
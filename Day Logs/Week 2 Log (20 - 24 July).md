# Week 2 Log (20 - 24 July)

## 20 July

#### Day 9

- Added 2 second pre-ignition sequence in thrust curve, adjusted kinematics to reflect that

- Struggled with creating an estimator
  
  - Quaternion Propogation in 3DoF
  
  - Accelerometer initial attitude fix

- Neither worked, for various reasons:
  
  - If statements not liking discrete time steps
  
  - Conceptual misunderstanding of quaternion math?
  
  - Too much noise in measured omega
  
  - Could not properly calculate the bias in-model

- After bypassing estimator and feeding perfect $\theta$, the controller and kinematics still work perfectly.

- My focus tomorrow morning will be debugging these problems and/or preparing to be able to talk about them intelligently with Col Harris.

Approximate Time Spent: 5 hours

## 21 July

#### Day 9

- Debugged Quaternion integrator w/ Col Harris

- Removed Accel. Fix; will just debug that in reality, won't model it.

- Working through [Attitude from angular rate — AHRS 0.4.0 documentation](https://ahrs.readthedocs.io/en/latest/filters/angular.html) to be able to derive the quat. kinematic equation by hand, I feel it's important to conceptual understanding.

- With Quaternion integrator fixed, I readded sensor noise and bias to the model. I added a LPF block (time constant = $2T_s$, vibed that number). 

- Model performed sufficiently well to warrant moving on to 6DoF. Day 9 deliverable made.

#### Day 11

- Created delayless LED blink program, giving skeleton to flight controller.

- Checked code with [Overview | Multi-tasking the Arduino - Part 1 | Adafruit Learning System](https://learn.adafruit.com/multi-tasking-the-arduino-part-1) afterwards; they used a class object for the LED, it would probably be smart for me to use OOP for my real flight controller.
  
  - There are 3 more parts to the guide that are worth reading through.

- Created logic for loop to self-check in skeleton, completing day 11.

Total Time Spent: 9 hours

## 22 July

#### Day 12

- Took notes on: [I2C - SparkFun Learn](https://learn.sparkfun.com/tutorials/i2c); skimmed  [Serial Peripheral Interface (SPI) - SparkFun Learn](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi), [Logic Levels - SparkFun Learn](https://learn.sparkfun.com/tutorials/logic-levels), [Shift Registers - SparkFun Learn](https://learn.sparkfun.com/tutorials/shift-registers), [Serial Communication - SparkFun Learn](https://learn.sparkfun.com/tutorials/serial-communication) for background on the data communications protocols I'll be using.

- Filled out flight controller skeleton with *read()* and *log()* functions; I am running into the same issue as before trying to read both the accelerometer and gyro simultaneously, and I am shooting past the 0.01 s refresh limit, I have to find what is blocking.
  
  - Per BNO08X data sheet, gyroscope max. refresh is 400 Hz and Accelerometer is 500 Hz, so I should be able to rule out refresh rate as a lim. fac.
  
  - Set Accel and Gyro refresh rates to 200 Hz
  
  - My controller is missing cycles by 5 ms on average. Reference library files: [Adafruit_BNO08x/src/Adafruit_BNO08x.cpp at master · adafruit/Adafruit_BNO08x](https://github.com/adafruit/Adafruit_BNO08x/blob/master/src/Adafruit_BNO08x.cpp) [Adafruit_BusIO/Adafruit_I2CDevice.cpp at master · adafruit/Adafruit_BusIO](https://github.com/adafruit/Adafruit_BusIO/blob/master/Adafruit_I2CDevice.cpp) [Adafruit_BNO08x/src/sh2_SensorValue.h at master · adafruit/Adafruit_BNO08x](https://github.com/adafruit/Adafruit_BNO08x/blob/master/src/sh2_SensorValue.h) To try to figure out why sensor reading takes so long.

- We can see that the gyro has considerable delays relative to the accelerometer, which tracks neatly with the overall timestamp

- Plot 1: read() runs once per loop; gyro time error is smaller but the overall program cannot maintain 100 Hz interval.

- Plot 2: read() runs once per loop; gyro time error much larger, program can maintain 100 Hz interval.

- ![](C:/Users/C27Derek.Weissinger/AppData/Roaming/marktext/images/2026-07-22-17-27-43-image.png)

- ![](C:/Users/C27Derek.Weissinger/AppData/Roaming/marktext/images/2026-07-22-17-30-00-image.png)

Approximate Time Spent: 9 hours



## 23 July

#### Day 10

- Derived the 6DOF equations of motion by hand
  
  - Talked with Col Harris about how we treat angular accel. and velocity differently, we will use a continuous quaternion integrator which will then be compared against the discrete one used by the estimator

#### Day 12

- After trying many different things, Col Harris and I concluded that it isn't worthwhile trying to keep the sensor measurements on a bound 100 Hz clock.  Therefore I set my program to call read() every loop, but only log once every 100 Hz cycle to free up as much processing space as possible.

- I will further solve this problem by adding a state selector for the flight controller: state 0 = pre-launch, state 1 = under thrust, state 2 = burnout pre-apogee, state 3 = deploy parachute.
  
  - In state 0, the accelerometer will run at high frequency, the gyro just fast enough to get an accurate baseline bias measurement
  
  - In state 1, the accelerometer will be deactivated and the gyro will run as fast as possible, allowing us to properly update our attitude every 100 Hz.

- Validated the gyro data output gives us the expected directions.





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



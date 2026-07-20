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



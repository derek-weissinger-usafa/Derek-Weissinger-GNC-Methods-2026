# Week 3 Log (25-31 July)

## 25 - 26 July

#### Day 10

- Believing that I got the plant model good, I added in all the other subsystems and expanded them for 6DoF

- I kept running into persistent errors where the euler angles would oscillate uncontrollably or run away immediately, regardless if I switched signs on the controller gains or not.

Approximate Time Spent: 4 hours

## 27 July

#### Day 10

- Working with Col Harris, I discovered several flaws in the plant model that I addressed

- I also rigged up the 6 DoF plant block to compare my plant model to MATLAB's

- After taking a little too long to properly adjust for the different coordinate systems of my model and MATLAB's, I got both to give me outputs that are wrong, but wrong in the same exact way, with the caveat that the yaw and roll are switched between the 2 models

- This means that the integrators functions properly, and I am simply feeding it the wrong data in the wrong way, which is a huge step forward in a clean 6DoF model.

Approximate Time Spent: 6 hours.

## 28 July

#### Day 10

- I fixed the yaw/roll discrepancy between the 2 plant models. This means that unless the data I'm feeding it is wrong (my hand derivation of thrust and gravity in the body frame) my hand-derived plant model is correct.

- I fixed a critical error in the I-term of my integrator: the windup clampdown actually set the I-term to 0 instead of simply stopping further integration if windup was detected. After fixing this, I was able to remove multiple bumps in various test cases that looked suspiciously like windup.

- In all test cases where there is an initial pitch and psi offset, the plant model ends up with a steady-state roll ($\phi$) angle ($< 0.1 \degree$) despite having no noticeable $\omega_x$ in the body frame. This occurs in both my hand-derived plant and the 6DoF Block. This is strange because $\omega_x$ being $0$ means there should be absolutely no roll. My current theory is that it's just an equivalent way to represent the attitude I still want. The issue if that is true is that $\theta$ and $\psi$ will not be entirely accurate to how I tuned my controllers. I will have to look into this more before I can declare my controller model working.

Approximate Time Spent: 5 hours.

## 29 July

#### Day 13

- After doing some experimenting, I was able to configure my sensors to refresh at an acceptable rate. The trick was not forcing them to wait until the timed `log()` function was called to check to see if there was another report available

- Setting the report time to 0 microseconds also seemed to effectively disable the sensor reports. 

- I added the logic for the controller to automatically find the gravity vector and the gyro bias vector while resting on the pad; I still have to convert the gravity vector to a usable quaternion for an attitude initial condition.

- I added the logic for quaternion integration; I still need to figure out how to best convert them to euler angles: since my MATLAB coded functions don't work, I would have to find a library to do it for me.
  
  - This is complicated by my choice to represent quaternions as a BLA library 4x1 matrix object

- I coded a basic PID controller and began to add the improvements from the *Improving the Arduino PID* site.

Approximate Time Spent: 5.5 hours.

## 30 July

#### Day 10

- Col Harris and I discussed how the slight roll we noticed was inherent due to the coupled nature of the euler angle diff eqs.. Although we use the quat. diff eq., we convert to Euler angles for the controller, which introduces the same issue.

- We also discussed a potential research idea: constructing a "naive" (decoupled 2-axis) PID controller, an 1 loop LQR controller, and a nested Quat. feedback controller (quat. feedback outer, PID on omega inner) and comparing its ability to control the rocket, both in simulation and reality. Col Harris gave me a brief handout describing the mathematics of the Quat. Feed. controller, and it looks pretty easy to implement (famous last words).

- I completed the Day 10 deliverable report on the 6DoF Simulink model; I will use it as a base to created the slide deck for my end of course briefing tomorrow.

#### Day 13

- I finished implementing the *Improving the Arduino PID* code to my teensy codebase. The code will still need to be tested and debugged, which will be difficult without any actuator (i.e. servo) code implemented.

Approximate Time Spent: 7 hours.

## 31 July

- I cleaned up the 6DoF model; making it more legible. I moved a copy of it to the Day 10 Deliverables folder.

- I created a first draft Quat. Feedback controller in Simulink; still needs to be debugged however.

- I cleaned up the repository and left it in more or less the state that it will be in when I present

- I talkwed with Col Harris about options on how to take this 499 further and pursue more novel research, some very promising paths we can take!

Approximate Time Spent: 4 hours.

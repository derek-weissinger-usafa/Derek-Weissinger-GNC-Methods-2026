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



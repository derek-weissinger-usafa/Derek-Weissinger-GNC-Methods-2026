# Day 1 (11 - 13 July) Log

## 11 July

#### Admin

- Setup Markdown Logs

- Setup Github repository

#### Teensy/PlatformIO Setup

- Setup PlatformIO in VSCode
  
  - Referenced this video: [Getting Started with PlatformIO - YouTube](https://www.youtube.com/watch?v=JmvMvIphMnY)

- Created basic speaker program (src/Day1AudioTest.cpp)

- Created basic speaker circuit
  
  <img title="" src="files/SpeakerCircuit.jpg" alt="Speaker Circuit" width="230">

#### GNC Block Diagram

- Skim watched [Scout F - Engineering Cut - YouTube](https://www.youtube.com/watch?v=4OmOwSB7xP8) to gain overview of overall system

- Created first overall GNC block diagram, using only above resources. In Deliverables folder as GNC Block Diagram Day 1.png

- Took notes on [What Is PID Control? | Understanding PID Control, Part 1](https://www.youtube.com/watch?v=wkfEZmsQqiA&list=PLn8PRpmsu08pQBgjxYFXSsODEF3Jqmm-y), going over intuition for each term of a PID controller

- Took notes on [Understanding Sensor Fusion and Tracking, Part 1: What Is Sensor Fusion? - YouTube](https://www.youtube.com/watch?v=6qV3YjFppuc&list=PLn8PRpmsu08ryYoBpEKzoMOveSTyS-h4a), describing high-level concept and benefits of sensor fusion

Approximate Time Spent: 4 hours

## 12 July

- Read and took notes on Day 2 website content

- Skimmed [DCM Tutorial – An Introduction to Orientation Kinematics – Starlino Electronics](https://www.starlino.com/dcm_tutorial.html) to better understand DCMs

- Did worksheet deliverable; provided answer is definietly wrong (I believe the AI defined the coordinate system for a plane, not a rocket); will double check tomorrow.

- Created euler2dcm.m MATLAB script; hand-derived 2D rotation matrices then debugged; Took absurdly long for me to realize that my hand-derived 2D matrices were for *active* rotations, not *passive* as is convention. Once fixed the script worked when compared to the built-in aerospace toolbox angle2dcm.

- Created dcm2euler.m and put in initial error checking; Still need to program meat of the script.

Approximate Time Spent: 3 hours

## 13 July

#### Day 2 (cont.)

- Skimmed MECH 632 Attitude Kinematics Slides up to Quaternions

- 321 Passive DCM:

- ![](C:/Users/C27Derek.Weissinger/AppData/Roaming/marktext/images/2026-07-13-08-18-08-image.png)

- Coded dcm2euler.m with above matrix

- Did multiple test cases on euler2dcm.m and dcm2euler; confirmed them with aerospace toolbox functions as well.

- Used euler2dcm.m to confirm the worked problem; found I defined my yaw coordinate system wrong in the worked problem and fixed it; uploaded to deliverables folder

- Created plot demonstrating issues with DCM and euler angles once pitch > 90; uploaded to deliverables folder

- <img src="file:///C:/Users/C27Derek.Weissinger/AppData/Roaming/marktext/images/2026-07-13-09-30-24-image.png" title="" alt="" width="333">

- Watched [Euler (gimbal lock) Explained](https://www.youtube.com/watch?v=zc8b2Jo7mno) for further intuition on Gimbal Lock, finally saw why gimbal lock only occurs for pitch in aerospace.

#### Day 3

- Took notes on Website Content and [Visualizing quaternions, an explorable video series](https://eater.net/quaternions), very complicated but I understand the concepts behind quaternions now.

- Created QuatPropagation.mlx script; plotting a constant-rate pitch maneuver using quaternion Diff Eq. and RK4. Plot is linear as expected and quaternions show movement is only occuring in pitch axis. 2 problems:

- ![](C:/Users/C27Derek.Weissinger/AppData/Roaming/marktext/images/2026-07-13-13-59-51-image.png)
  
  - Spike at 90 and -90, seemingly reversing pitch direction each time; perhaps some application of double cover?
  
  - Why does renormalizing have no effect, even for multi-axis omegas? is RK4 just that good?

- Started work on quat2dcm.m and dcm2quat.m; tried to hand-derive but just began to copy equation from textbook. They appear to be good; they can self-reproduce any given dcm.

- It appears my dcm2euler.m is wrong or spitting out equivalent, but different euler angles for I got [phi2, theta2, psi2] = [120, -20, -160] from [300, 200, 20]. When I applied dcm2euler to QuatPropagation.mlx, I got wildly wrong and inconsistent answers.

- Created quatmult.m and confirmed it correct with built-in function.

- My verdict: I don't think it is a good idea to get too in the weeds debugging matlab scripts, as this is ultimately what MATLAB's built-in functions are for. I know I have a sufficient understanding to be able to use these in an engineering context, so I believe I can move on to the next day. I should go over the quaternion propagation with Lt Col Harris as those errors may be conceptual.

Approximate Time Spent: 7 hours.

## 14 July

#### Day 3

- Worked with Col Harris on quat. propagation script: The inversions were caused by gimbal lock and the 2 quaternions were actually different, just infinitesimally so.

#### Day 4

- Wrote up 3DOF Equations of Motion deliverable, expressed as 3 second derivatives, and uploaded to repo.
- Created vehicle_params.m and downloaded F15 thrust curve as .csv

#### Day 5

- Went through Simulink Onramp tutorial

- Created 3DOF Plant model, still need to validate it but initial testing looks promising!

- Validated 3DoF Model and uploaded to Deliverables Folder.
  
  - Not sure how to do the instability demonstration

#### Day 6

- Skimmed the reading for Day 6 on the website.

Approximate Time Spent: 6 hours.

## 15 July

- Took notes on website's Day 6 reading

- Created PID controller in Simulink

- Tuned the controller for the various test cases given by the website

- Created and submitted Day 6 Deliverabley

- Took notes on [Understanding PID Control](https://www.youtube.com/playlist?list=PLn8PRpmsu08pQBgjxYFXSsODEF3Jqmm-y), videos 2-4.

Approximate time spent: 5.5 hours.

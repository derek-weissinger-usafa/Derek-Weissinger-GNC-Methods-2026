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



## 12 July

- Read content on Euler Angles and DCMs on website (Day 2)

- Skimmed [DCM Tutorial – An Introduction to Orientation Kinematics – Starlino Electronics](https://www.starlino.com/dcm_tutorial.html) to better understand DCMs

- Did worksheet deliverable; provided answer is definietly wrong (I believe the AI defined the coordinate system for a plane, not a rocket); will double check tomorrow.

- Created euler2dcm.m MATLAB script; hand-derived 2D rotation matrices then debugged; Took absurdly long for me to realize that my hand-derived 2D matrices were for *active* rotations, not *passive* as is convention. Once fixed the script worked when compared to the built-in aerospace toolbox angle2dcm.

- Created dcm2euler.m and put in initial error checking; Still need to program meat of the script.

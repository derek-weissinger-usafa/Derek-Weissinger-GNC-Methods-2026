# Summer 2026 499 Feedback

I will focus specifically on the website, looking mostly at correcting deadlinks and AI hallucinations. I will also devote some space to some changes to make to the overall course and some personal reflections on how I approached it.

## Day-by-Day Website Feedback

#### [Day 1](https://ghost3828.github.io/499-GNC-Methods-for-TVC/day01exp.html)

- Cut or tell student to quickly skim  [BPS.space — Scout F, Engineering Cut](https://youtu.be/4OmOwSB7xP8), this is a 2-hour video that provides much more detail than needed for an overview.

- Cut the insistence that the deliverable has units on every signal; this is not needed for a high-level system block diagram

- The *Concept 3* explanation of instability needs to be reworked. It makes the assumption that if the rocket tips, the thrust force still acts in line with gravity, causing a further torque. This obviously does not happen. The instability of the rocket is due to unavoidable manufacturing defects making the thrust vector off-center and not aligned on the longitudinal axis; and random aerodynamic disturbances.

#### [Day 2](https://ghost3828.github.io/499-GNC-Methods-for-TVC/day02exp.html)

- Claude makes the assumption that we are using default *aeronautics* body frame (e.g. x-axis aligned with longitudinal axis). This means that for a rocket on the launch pad, the x-axis in the body frame will be aligned with the z-axis of the navigation frame. This problem made understanding subsequent DCM and euler angle content difficult, as unless I arbitrarily defined the navigation frame to be x-axis up, we technically start at $\theta = 90 \degree$. Nowhere in the course content does it say to do this.

- I think developing the `dcm2euler` and `euler2dcm` MATLAB functions was redundant and much time was wasted debugging. I think conceptual understanding would be best supported by doing 1 euler to DCM by-hand exercise.

#### [Day 3](https://ghost3828.github.io/499-GNC-Methods-for-TVC/day03exp.html)

- The quaternion kinematic equation needs to be reworked in a form that is actually in the AFIT slides. Finding that the version of the kinematic equation in the website is equivalent to the one in the slides resulted in much wasted time.

- Cut out having to manually code `quat2dcm`, `dcm2quat`, and `quatmultiply`. Not much conceptual understanding is gained in my opinion and much time is wasted debugging.

- This is probably the hardest day conceptually, emphasize working through 3Blue1Brown's resources until students can completely visualize the axis-angle visualization of quaternions, will make subsequent programming much easier.

#### [Day 4](https://ghost3828.github.io/499-GNC-Methods-for-TVC/day04exp.html)

- Specify that `vehicle_params.m` should come from BPS Spaces' Scout-F rocket. This will take the guesswork out specifying parameters

#### [Day 5](https://ghost3828.github.io/499-GNC-Methods-for-TVC/day05exp.html)

- Despite being called a "Simulink Bootcamp," this day does not provide any guidance on how to use Simullink except for a link buried at the very bottom. I suggest making the website's link to the Simulink Onramp much more prominent.  I would also suggest teaching the student how to enable time step visualization and signal size visualization in the model, as knowing these things earlier would have helped immensely.

- The part suggesting comparing a student-built model with the built-in 3DoF block should also have a part explaining how to properly map the student built coordinate system (x-axis up) with MATLAB's default coordinate system (z-axis positive down).

#### [Day 6](https://ghost3828.github.io/499-GNC-Methods-for-TVC/day06exp.html)

- I suggest making the student build the PID by hand instead of using Simulink's `controller` block, as it will reinforce conceptual understanding of what a PID is.

- [TVC Rocket PID Tuning In Simulink Ep. 3](https://www.youtube.com/watch?v=jrrC53Lru9I) Students will be overwhelmed by this and not understand what is going on, I suggest removing it.

- The other readings are all good, if student time becomes an issue I suggest cutting out [Improving the Beginner's PID](http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/) (moving to later days once the suggested changes are actually implemented) and [Ziegler-Nichols method](https://en.wikipedia.org/wiki/Ziegler%E2%80%93Nichols_method).

#### [Day 7](https://ghost3828.github.io/499-GNC-Methods-for-TVC/day07exp.html)

- More explanation is needed for why Zero-order holds are needed and not just unit delays for discretization. I still don't understand myself.

- Move this link to Day 14: [How servo motors work & interfacing with Arduino](https://lastminuteengineers.com/servo-motor-arduino-tutorial/)

#### [Day 8](https://ghost3828.github.io/499-GNC-Methods-for-TVC/day08exp.html)

- There should be a better explanation for determining noise from datasheets. I do not understand myself and I simply determined it experimentally. The  [A Simple MEMS Gyro Model Using MATLAB/Simulink](https://www.youtube.com/watch?v=P1OEoA70YJo) video is too high-level in this regard.
  
  - I think an easy solution is to tell Claude to walk us through the BNO085 datasheet and finding the noise there.

- [MEMS gyroscope error sources](https://www.analog.com/en/resources/technical-articles/what-you-need-to-know-about-mems-gyroscopes.html) dead link.

- [Understanding Sensor Fusion and Tracking](https://www.youtube.com/watch?v=6qV3YjFppuc&list=PLn8PRpmsu08ryYoBpEKzoMOveSTyS-h4a) Only episode 2 is needed, not episode 1.

#### [Day 9](https://ghost3828.github.io/499-GNC-Methods-for-TVC/day09exp.html)

- Change the quaternion kinematic equation to what we decided to change day 3 to.

- We should validate  [Attitude from angular rate — quaternion integration](https://ahrs.readthedocs.io/en/latest/filters/angular.html), specifcally how it seems they do hamilton products the wrong way. It seems like a good resource if they are actually right.

- LaTeX rendering does not work for [TKJ Electronics » A practical approach to Kalman filter and how to implement it](https://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it/) on Microsoft Edge, making it practically unreadable.

- The [Understanding Sensor Fusion and Tracking - YouTube](https://www.youtube.com/playlist?list=PLn8PRpmsu08ryYoBpEKzoMOveSTyS-h4a) is neither linked nor do the videos explain what the AI claims they do.

#### [Day 10](https://ghost3828.github.io/499-GNC-Methods-for-TVC/day10exp.html)

- We should make the 6DoF model stretch the requirement of the day. We will need it for when we actually start programming the microcontroller.
  
  - We should budget extra days for this.

- I did not do the robustness study as specified in *Concept 2*, but I see how it'd be useful.

- https://www.mathworks.com/help/simulink/ug/simulink-simulation-in-a-loop.html dead link.

#### [Day 11](https://ghost3828.github.io/499-GNC-Methods-for-TVC/day11exp.html)

- Include a primer on using PlatformIO.

#### [Day 12](https://ghost3828.github.io/499-GNC-Methods-for-TVC/day12exp.html)

- Include a link to your serial monitor .exe and a quick tutorial on how to use it.

#### [Day 13](https://ghost3828.github.io/499-GNC-Methods-for-TVC/day13exp.html)

- http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it/ This has the same LaTeX problem mentioned in Day 9

- Change the quaternion kinematic equation to what we decided to change day 3 to.

#### [Day 14](https://ghost3828.github.io/499-GNC-Methods-for-TVC/day14exp.html)

- I did not get this far, so I have no substantial feedback to give.

#### [Day 15](https://ghost3828.github.io/499-GNC-Methods-for-TVC/day15exp.html)

- This is the presentation day, I have no substantial feedback to give.

## Overall Feedback

- It will be very useful to wait until after controls 1 or include a primer on some important controls 1 material (specifically representing things in s-space, solving for poles); I feel I missed out on a lot of the rigor that many resources took as given. That being said, I was able to get reasonably far without learning any classical control theory, so it is possible, just unsatisfying.
  
  - Care should be taken to make sure these theoretical introductions remain focused, so this class does not simply become controls 1 again.

- Veness's Control Engineering in the FIRST Robotics Competiton can and should be incorporated as a resource. Because it was a 300 page text and I did not know where to find answers to the specific questions I had, I felt I underutilized what otherwise seemed like a great resource.

- The AFIT Slides need further explanation, both for notation and overall content. I had a hard time discerning, especially for the kinematics and dynamics content, what exactly was being said and how to apply simplifying assumptions to my specific model.

- A module describing PlatformIO best practices and how to best integrate it to the specific project would be nice; I was able to do the basic IDE tasks just fine but many things I did with PlatformIO felt "hacky" and I just know there is a better, standard way to do it (like having more than one .cpp file in a project) but I was unable to spend the time digging through resources to figure it out.

- A tutorial should be developed - maybe I can make it - for using the BNO085 IMU. Many hours were wasted going through the poorly documented IMU code.

- The provided servo link should be updated for what we actually use.

- We should find more realistic requirements for the controller. The assumption of $100 \space Hz$ refresh rate was too rigidly stuck to and we wasted much time trying to force it on hardware that just simply couldn't accomodate.



## Overall Reflections

- I should not have been so overwhelmingly hostile to using AI. An obvious use of it would have been figuring how to properly enable/disable multiple reports on the IMU. This would have saved me a ton of time and I still would have been able to understand what was happening. My main objection is I still don't want to open the Pandora's Box of AI and become completely reliant on it.





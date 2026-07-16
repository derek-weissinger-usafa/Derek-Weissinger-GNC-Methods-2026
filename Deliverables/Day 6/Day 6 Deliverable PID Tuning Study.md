# Day 6 Deliverable: 3DoF PID Tuning Study

Scratch-made discrete PID controller modeling a rocket.

Goal: vertical flight path ($\theta = 0 \degree$)

Assumptions:

- Constant Mass

- Instant Actuator Response

- Perfect Sensor Data

| Parameters                               | Value                  |
| ---------------------------------------- | ---------------------- |
| Vehicle Motor                            | Estes F15              |
| Mass: $m$                                | $0.543 \space kg$      |
| Moment of Inertia $I$                    | $0.048 \space kg  m^2$ |
| Arm from Gimbal to CG $L_g$              | $0.28 \space m$        |
| Maximum Gimbal Deflection $\delta_{max}$ | $5 \degree$            |
| Sampling Rate ${T_s}^{-1}$               | $100 \space Hz$        |

See 3DOF_Sim.slx for Simulink Model.

## Test 1: Initial Offset

$\theta_0 = 5 \degree$

![](C:\Users\C27Derek.Weissinger\OneDrive%20-%20USAFA%20(AFAcademy.AF.edu)\Documents\Classes\Summer%2026\Astro%20499\Derek-Weissinger-GNC-Methods-2026\Deliverables\Day%206\files\Theta0=5.png)

- $K_p = 1$; $K_i = 0$, $K_d = 0.15$.

- $\theta$ rapidly approaches $0$ and stays there.

- $\delta$ shows no noisy or jittery behavior.

## Test 2: Initial Offset and Constant Disturbance Torque

$\theta_0 = 3 \degree$, $\tau = 0.02 \space Nm$.

![](C:\Users\C27Derek.Weissinger\OneDrive%20-%20USAFA%20(AFAcademy.AF.edu)\Documents\Classes\Summer%2026\Astro%20499\Derek-Weissinger-GNC-Methods-2026\Deliverables\Day%206\files\Initial%20Offset%20and%20Constant%20Torque.png)

- $K_p = 2$; $K_i = 0.01$, $K_d = 0.15$.

- $\theta$ rapidly approaches 0, slightly $(\approx 0.2 \degree) $ overshoots but $K_i$ term fixes flightpath
  
  - Any further increase in $K_i$ increases overshoot, decrease makes controller unable to account for constant torque.

- Slight jittery behavior in $\delta$ at $t \approx 0.1-0.2 \space s$, would likely be smoothed out by implementing servo transfer functions.

## Test 3: Initial Offset and Random Disturbance Torque

$\theta_0 = 3 \degree$, $\tau$ is random between $0.01 \space Nm$ and $-0.01 \space Nm$ with mean of $0$, sampled every $0.1 \space s$.

![](C:\Users\C27Derek.Weissinger\OneDrive%20-%20USAFA%20(AFAcademy.AF.edu)\Documents\Classes\Summer%2026\Astro%20499\Derek-Weissinger-GNC-Methods-2026\Deliverables\Day%206\files\Initial%20Offset%20and%20Random%20Torque.png)

- $K_p = 2$; $K_i = 0.01$, $K_d = 0.15$.

- Controller is able to keep $\theta$ between $1$ and $-1$ after initial correction.

- Gimbal reaches saturation limit after $t = 3.4 \space s$, this is due to loss of control authority after motor burnout at $t = 3.3 \space s$.

#### Test 3 Trajectory View



![](C:\Users\C27Derek.Weissinger\OneDrive%20-%20USAFA%20(AFAcademy.AF.edu)\Documents\Classes\Summer%2026\Astro%20499\Derek-Weissinger-GNC-Methods-2026\Deliverables\Day%206\files\Initial%20Offset%20and%20Random%20Torque%20Xn%20and%20Zn.png)

- Despite seeming jitteriness due to random $\tau$, the flight path is still overall vertical, with only slight movement in the z-axis.

#### Overall Tuning Table

| Test # | $K_p$ | $K_i$ | $K_d$ |
| ------ | ----- | ----- | ----- |
| 1      | 1     | 0     | 0.15  |
| 2      | 2     | 0.01  | 0.15  |
| 3      | 2     | 0.01  | 0.15  |

## Failure Modes

#### Excessive $K_p$ Failure

![](C:\Users\C27Derek.Weissinger\OneDrive%20-%20USAFA%20(AFAcademy.AF.edu)\Documents\Classes\Summer%2026\Astro%20499\Derek-Weissinger-GNC-Methods-2026\Deliverables\Day%206\files\High%20Kp%20Failure.png)

- $K_p = 0.2$; $K_i = 0$, $K_d = 0$.

- Oscillation around target point, as expected. This would happen for any $K_p$ in the absence of $K_d$ or $K_i$ terms.

#### Excessive $K_i$ Failure

![](C:\Users\C27Derek.Weissinger\OneDrive%20-%20USAFA%20(AFAcademy.AF.edu)\Documents\Classes\Summer%2026\Astro%20499\Derek-Weissinger-GNC-Methods-2026\Deliverables\Day%206\files\High%20Ki%20Failure.png)

- $K_p = 1$; $K_i = 0.1$, $K_d = 0.15$.

- We see oscillation due to windup, as the $K_i$ term stores too much correction.

#### Excessive $K_d$ Failure

![](C:\Users\C27Derek.Weissinger\OneDrive%20-%20USAFA%20(AFAcademy.AF.edu)\Documents\Classes\Summer%2026\Astro%20499\Derek-Weissinger-GNC-Methods-2026\Deliverables\Day%206\files\High%20Kd%20Failure.png)

- $K_p = 2$; $K_i = 0.1$, $K_d = 4$.

- Due to the random disturbance, excessive noise is brought into the $\delta$, causing wildly unrealistic swings. $\theta$, however, remains surprisingly stable.

Documentation: I used the Simulink Onramp to figure out how to model the $K_i$ term.

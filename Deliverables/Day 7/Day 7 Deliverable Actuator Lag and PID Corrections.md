# Day 7 Deliverable: Actuator Lag and PID Corrections

## Test 1: Discretization, no Tuning Change

- Although the I and D terms were already technically discrete* with unit holds, I used a zero-order hold at the beginning of the controller to force all terms to be discrete in the same way. 
  
  - The I and D terms were computed continuously, but with the discrete method (e.g. summation for I, slope of 2 points for D)

![](C:\Users\C27Derek.Weissinger\OneDrive%20-%20USAFA%20(AFAcademy.AF.edu)\Documents\Classes\Summer%2026\Astro%20499\Derek-Weissinger-GNC-Methods-2026\Deliverables\Day%207\files\Discreteized%20Controller%20No%20Gain%20Mod.png)

- Same conditions and weights as Day 6 controller ($K_p = 2$; $K_i = 0.01$, $K_d = 0.15$; $\theta_0 = 3 \degree$, $\tau$ is random between $0.01 \space Nm$ and $-0.01 \space Nm$ with mean of $0$, sampled every $0.1 \space s$).

- Frequency: $f = 100 \space Hz$.

- No meaningful difference in control ability after discretization.

- After playing with all 3 gains, no substantially better tuning pattern was found, leading me to conclude, for this scenario, that the current gains are suitable.

## Test 2: Sampling Frequency Study

Keeping the same gains and initial conditions, tests were conducted reducing the sampling frequency to find when instability would occur.

#### $50 \space Hz$

![](C:\Users\C27Derek.Weissinger\OneDrive%20-%20USAFA%20(AFAcademy.AF.edu)\Documents\Classes\Summer%2026\Astro%20499\Derek-Weissinger-GNC-Methods-2026\Deliverables\Day%207\files\50Hz.png)

#### $25 \space Hz$

![](C:\Users\C27Derek.Weissinger\OneDrive%20-%20USAFA%20(AFAcademy.AF.edu)\Documents\Classes\Summer%2026\Astro%20499\Derek-Weissinger-GNC-Methods-2026\Deliverables\Day%207\files\25Hz.png)

#### $15 \space Hz$

![](C:\Users\C27Derek.Weissinger\OneDrive%20-%20USAFA%20(AFAcademy.AF.edu)\Documents\Classes\Summer%2026\Astro%20499\Derek-Weissinger-GNC-Methods-2026\Deliverables\Day%207\files\15Hz.png)

#### $10 \space Hz$

![](C:\Users\C27Derek.Weissinger\OneDrive%20-%20USAFA%20(AFAcademy.AF.edu)\Documents\Classes\Summer%2026\Astro%20499\Derek-Weissinger-GNC-Methods-2026\Deliverables\Day%207\files\10Hz.png)

- The system's stability steadily decreases, with divergence happening soon after $15 \space Hz$

## Test 3: Windup Clampdown Study

Initial condtions changed to $\theta_0 = 45 \degree$, no disturbance torque.

#### No Windup Protection

![](C:\Users\C27Derek.Weissinger\OneDrive%20-%20USAFA%20(AFAcademy.AF.edu)\Documents\Classes\Summer%2026\Astro%20499\Derek-Weissinger-GNC-Methods-2026\Deliverables\Day%207\files\Windup%20No%20Clamping.png)

- The integrator term quickly looses control of $\theta$, causing massive, destabilizing oscillations.

#### Windup Clamping Protection

![](C:\Users\C27Derek.Weissinger\OneDrive%20-%20USAFA%20(AFAcademy.AF.edu)\Documents\Classes\Summer%2026\Astro%20499\Derek-Weissinger-GNC-Methods-2026\Deliverables\Day%207\files\Windup%20Clamping%20Demo.png)

- The controller is able to right itself and bring $\theta \approx 0 \degree$ before the motor burns out, proving the importance of making sure the I term has windup protection.

- A simple clamping algorithm was used, checking both if the maximum gimbal angle was reached ($\delta > 5 \degree$) *and* if the I term and $\delta$ have the same sign. If that is the case, the I term ceases to change until one of the conditions become false.

## Test 4: Actuator Lag / Rate Limits

- Using data provided at: [Micro Servo - Blue Bird Model](https://www.blue-bird-model.com/products_detail/73.htm)

- Servo lag was modeled at $0.01 \space s$.

- Servo maximum rate was modeled as $60 \degree / \space 0.08 \space s$.

- Servo saturation was already modeled from Day 5.

- No noticable difference in the controller was observed.



Documentation: No outside help was received.



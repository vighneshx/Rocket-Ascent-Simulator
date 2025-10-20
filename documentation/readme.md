# Classical Rocket Ascent Simulator (C)

This is my **1D rocket ascent simulator** written entirely in **pure C**, with **no external libraries**. It models a rocket ascending vertically under **thrust, drag, gravity, and decreasing mass** due to fuel consumption.

I built this project to **learn and master numerical integration**, and I implemented the Runge–Kutta 4 (RK4)** method for updating the rocket's motion.

---

## **Features**

* Simulates **vertical rocket ascent**.
* Models real physics:

  * **Thrust**: engine force pushing the rocket.
  * **Drag**: air resistance slowing it down.
  * **Gravity**: pulling the rocket down.
  * **Mass decrease**: rocket burns fuel over time.
* Calculates **Mach number** as velocity / speed of sound.
* Uses **RK4 integration** for accurate results.
* Outputs **time, mass, altitude, velocity, Mach** to both **console** and **CSV file** (`rocket_data.csv`).
* Easy to modify: thrust, drag, mass, and simulation parameters are fully customizable.

---

## **How it Works**

1. **Rocket Struct:**
   I defined a `Rocket` struct to store mass, fuel burn rate, thrust, drag coefficient, and reference area.

2. **Force Calculations:**
   The code calculates **drag**, **gravity**, and **net acceleration** at each time step.

3. **RK4 Integration:**
   The rocket’s **velocity** and **altitude** are updated using **Runge–Kutta 4**, which is more accurate than simple Euler integration.

4. **Mach Number:**
   Each time step computes Mach number using a constant **speed of sound** (`340.29 m/s`).

5. **Data Output:**
   The simulator prints each step to the console and saves it in a CSV file for easy plotting.

---

## **Simulation Parameters**

* `dt` → time step (s)
* `t_max` → total simulation time (s)
* `rho` → air density (kg/m³)
* `a_sound` → speed of sound (m/s)
* Rocket parameters: `mass`, `mdot`, `thrust`, `Cd`, `A`

All of these can be easily adjusted in the `main()` function.

---

## **How to Run**

1. Compile the code:

```bash
gcc ras.c -o ras
```

2. Run the simulation:

```bash
./ras
```

3. Check the console output and `rocket_data.csv` for the rocket’s trajectory data.

---

## **Next Steps**

* Add **variable air density with altitude**.
* Add **gravity variation** with altitude.
* Implement **2D/3D trajectories**.
* Visualize the rocket trajectory with **advanced plots**

---

This project is a **learning tool** I made to understand the fundamentals of **rocket physics** and **numerical integration** in C — it’s perfect for anyone interested in aerospace engineering or simulations.



## **Rocket Ascent Simulator (C)**

### **1. Objective**

The goal of this project is to simulate the ascent phase of a rocket launched vertically from rest, considering the effects of:

* Thrust
* Drag
* Gravity
* Changing mass due to fuel consumption

The simulator must implement both the **Euler** and **Runge–Kutta 4 (RK4)** integration methods and output:

* Altitude
* Velocity
* Mach number
* Time history of the above (for plotting in an external tool such as Python or Excel)

All calculations must be implemented in **pure C** without using any external libraries.

---

### **2. System Definition**

#### a. **Governing Equations**

1. Net force:
   [
   F_{net} = T - D - m g
   ]

2. Acceleration:
   [
   a = \frac{F_{net}}{m}
   ]

3. Velocity and altitude:
   [
   \frac{dv}{dt} = a
   ]
   [
   \frac{dh}{dt} = v
   ]

4. Changing mass:
   [
   \frac{dm}{dt} = -\dot{m}_{propellant}
   ]

#### b. **Drag Equation**

[
D = \frac{1}{2} \rho v^2 C_d A
]

#### c. **Atmospheric Density (exponential model)**

[
\rho(h) = \rho_0 e^{-h/H}
]
where (H \approx 8500 , m).

---

### **3. Variables and Parameters**

| Quantity              | Symbol     | Typical value |
| --------------------- | ---------- | ------------- |
| Initial mass          | (m_0)      | 50 kg         |
| Dry mass              | (m_f)      | 30 kg         |
| Thrust                | (T)        | 1000 N        |
| Mass flow rate        | (\dot{m})  | 1 kg/s        |
| Drag coefficient      | (C_d)      | 0.5           |
| Cross-sectional area  | (A)        | 0.02 m²       |
| Sea-level air density | (\rho_0)   | 1.225 kg/m³   |
| Gravity               | (g)        | 9.81 m/s²     |
| Time step             | (\Delta t) | 0.01 s        |

---

### **4. Implementation Steps**

#### **Step 1 – Program Structure**

Set up a clean program with modular functions and a clear data structure.

```c
typedef struct {
    double h;   // altitude
    double v;   // velocity
    double m;   // mass
} State;

double thrust(double t);
double drag(double v, double h);
double density(double h);
double mass_flow(double t);
```

---

#### **Step 2 – Physical Models**

Implement the basic functions:

1. `density(h)`
   Returns ( \rho_0 e^{-h/H} )

2. `drag(v, h)`
   Returns ( 0.5 * density(h) * v^2 * Cd * A )

3. `mass_flow(t)`
   Returns a constant negative rate (-\dot{m}) while fuel remains, otherwise 0.

4. `thrust(t)`
   Returns constant (T) while fuel remains, otherwise 0.

---

#### **Step 3 – Integration Methods**

##### **Euler Integration**

```c
state.h += state.v * dt;
state.v += a * dt;
state.m += mdot * dt;
```

##### **Runge–Kutta 4 Integration**

Implement an `rk4_step()` function that computes the derivative at four stages:
[
k_1 = f(t, y)
]
[
k_2 = f(t + dt/2, y + k_1 dt/2)
]
[
k_3 = f(t + dt/2, y + k_2 dt/2)
]
[
k_4 = f(t + dt, y + k_3 dt)
]
and combine them as:
[
y_{next} = y + \frac{dt}{6}(k_1 + 2k_2 + 2k_3 + k_4)
]

---

#### **Step 4 – Data Logging**

Output raw data to a `.csv` file for post-processing.

```c
fprintf(file, "%f,%f,%f,%f\n", t, h, v, a);
```

Each line should include time, altitude, velocity, and acceleration.

---

#### **Step 5 – Mach Number Calculation**

Compute the Mach number using:
[
Mach = \frac{v}{a_{sound}}
]
Approximate the speed of sound as:
[
a_{sound} = 340 - 0.003h
]

---

#### **Step 6 – External Plotting**

Plot the generated CSV data using any external tool (Python, Excel, MATLAB):

* Altitude vs Time
* Velocity vs Time
* Mach number vs Altitude

---

### **5. Validation**

Ensure that:

* Mass decreases linearly until fuel burnout.
* Velocity increases realistically until drag balances thrust.
* Altitude peaks after engine cutoff (ballistic coast phase).

Compare Euler and RK4 results for accuracy and stability.

---

### **6. Possible Extensions**

* More detailed atmospheric model (ISA)
* Variable thrust profile
* Multi-stage rocket
* 2D trajectory (pitch angle and gravity turn)

---


 #include <stdio.h>

 // -----------------------------
 // Rocket Structure
 // -----------------------------
 
 struct Rocket {
  double mass; // total mass (kg);
  double mdot; // fuel burn rate (kg/s)
  double thrust; // thrust (N)
  double Cd; // drag coefficient
  double A; // reference area (m^2)
 };

 // ------------------
 // Compute drag force
 // ------------------
 double compute_drag(double rho, double v, double Cd, double A) {
   return 0.5 * rho * v * v * Cd * A;
 }


 // ------------------------
 // Compute net acceleration
 // ------------------------
 double compute_acceleration(struct Rocket r, double v, double rho) {
   double g = 9.90665; // gravity
   double D = compute_drag(rho, v, r.Cd, r.A);
   double T = r.thrust;
   double a = (T - D - r.mass * g) / r.mass;
   return a;
 }

 // ---------------
 // RK4 Method
 // ---------------
 
 void rk4_step(struct Rocket *r, double *v, double *h, double dt, double rho) {
   double v0 = *v;
   double h0 = *h;


   // k1 
   double a1 = compute_acceleration(*r, v0, rho);
   double kv1 = a1 * dt;
   double kh1 = v0 * dt;

   // k2 
   double a2 = compute_acceleration(*r, v0 + kv1/2, rho);
   double kv2 = a2 * dt;
   double kh2 = (v0 + kv1/2) * dt;
   

   // k3
   double a3 = compute_acceleration(*r, v0 + kv2/2, rho);
   double kv3 = a3 * dt;
   double kh3 = (v0 + kv2/2) * dt;

   // k4
   double a4 = compute_acceleration(*r, v0 + kv3, rho);
   double kv4 = a4 * dt;
   double kh4 = (v0 + kv3) * dt;

   r->mass -= r->mdot * dt;
   if(r->mass < 0.0) r->mass = 0.0;
 }



 // ---------------
 // Main Simulation
 // ---------------
 int main() {

   // Simulation parameters
   double dt = 0.01; // time step (s)
   double t_max = 10.0; // total simulation time (s)
   double rho = 1.225; // air density (kg/m^3)
   double a_sound = 340.29; // speed of sound (m/s)

   // Initialize rocket
   struct Rocket rocket;
   rocket.mass = 50.0; // kg
   rocket.mdot = 0.5; // kg/s
   rocket.thrust = 500; // N
   rocket.Cd = 0.5; // drag coefficient
   rocket.A = 0.05; // m^2


   // Initial conditions
   double h = 0.0; // altitude (m)
   double v = 0.0; // velocity (m/s)
   
   // Open CSV file
   FILE *fp = fopen("rocket_data.csv", "w");
   if(fp == NULL) {
     printf("Error opening file!\n");
     return 1;
   }

   // Write CSV header
   fprintf(fp, "time, mass, altitude, velocity, Mach\n");
   
   // Simulation loop
   for(double t = 0.0; t <= t_max; t += dt) {
    rk4_step(&rocket, &v, &h, dt, rho);
    double Mach = v / a_sound;

    // Print to console
    printf("time = %.2f s, mass = %.2f kg, altitude = %.2f m, velocity = %.2f m/s, Mach = %.2f\n",
           t, rocket.mass, h, v, Mach);

     // Write to file 
     fprintf(fp, "%.2f, %.2f, %.2f, %.2f, %.2f\n",
             t, rocket.mass, h, v, Mach);

   }

   fclose(fp);
   printf("Simulation data saved to rocket_data.csv\n");

   return 0;
  
 }

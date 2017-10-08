#include "projectile.hpp"
#include <math.h>

const double m = 1; // mass of bob
const double g = 9.8066; // gravity
const double dt = 0.001; // change in time
const double q = 1; // charge
const double e0 = 1; // electric field
const double k = 0.5; // constant 
const double w = 1; // period 


double electricForceXComponent (TState s){
  return q * e0 * cos(k * s.position.z - w * s.t) / sqrt(2);   
}

double electricForceYComponent (TState s){
  return q * e0 * sin(k * s.position.z - w * s.t) / sqrt(2);   
}

double electricForceZComponent (TState s){
  return q * 0;   
}

auto force(TState s) {
  return VecR3<double>{electricForceXComponent(s), electricForceYComponent (s), electricForceZComponent (s)};
 }

auto euler_step(TState s, VecR3<double> accel) {
  TState next;
  next.t = s.t + dt;
  next.position = s.position + (s.velocity * dt);
  next.velocity = s.velocity + (accel * dt);
  return next;
}

void n_steps(unsigned n, TState state0) {
  print_tstate(state0);
  if (n == 0)
    return;
  else {
    auto state = state0;
    for (unsigned k = 0; k < n; ++k) {
      state = euler_step(state, force(state) / m);
      print_tstate(state);
    }
  }
}

int main() {
  n_steps(12000, TState{0., {-e0 / (w * w * sqrt(2)), 0, 0}, {0, e0 / (w * sqrt(2)), -0.25}});
  return 0;
}

#include "projectile.hpp"

const double m = 1; // mass of bob
const double g = 9.8066; // gravity
const double dt = 0.001; // change in time
const double q = 1; // charge
const double e0 = 1; // electric field
const double k = 0.5; // constant 
const double w = 1; // period 

auto force(TState s) { return VecR2<double>{0, -m * g}; }

auto electricForceXComponent (TState s){
  return q * (e0/sqrt(2)) * cos(k*s.position.z - w*s.t);   
}

auto electricForceYComponent (TState s){
  return q * (e0/sqrt(2)) * sin(k*s.position.z - w*s.t);   
}

auto electricForceZComponent (TState s){
  return 0;   
}

auto electricForce (TState s){
  return VecR3<double>{electricForceXComponent(s), electricForceYComponent(s), electricForceZComponent(s)};
}

auto euler_step(TState s, VecR2<double> accel) {
  TState next;
  next.t = s.t + dt;
  next.position = s.position + (s.velocity * dt);
  next.velocity = s.velocity + (accel * dt);
  return next;
}

auto acceleration (TState state){
  return electricForce(state) / m;
}

void n_steps(unsigned n, TState state0) {
  print_tstate(state0);
  if (n == 0)
    return;
  else {
    auto state = state0;
    for (unsigned k = 0; k < n; ++k) {
      // created a function for acceleration line 37, replace it with force(state) / m
      state = euler_step(state, force(state) / m);
      print_tstate(state);
    }
  }
}

int main() {
  n_steps(1200, TState{0., {0, 0.1}, {5, 5}});
  return 0;
}

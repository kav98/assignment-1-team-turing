#include "projectile.hpp"
#include <math.h>

const double m = 1; // mass of bob
const double g = 9.8066; // gravity
const double dt = 0.001; // change in time
const double q = 1; // charge
const double e0 = 1; // electric field
const double k = 0.5; // constant 
const double w = 2; // period 

auto force(TState s) {
  return VecR3<double>{e0 * std::cos(k * s.position.z - w * s.t) / sqrt(2),
    e0 * std::sin(k * s.position.z - w * s.t) / sqrt(2),
    0} * q;
 }

auto verlet_step(TState currentState, VecR3<double> accel) {
  TState next;
  next.t = currentState.t + dt;
  next.position = currentState.position + (currentState.velocity)*dt + 0.5*accel*dt*dt;
  VecR3<double> nextAccel = force(next)/m;
  next.velocity = currentState.velocity + 0.5*(accel + nextAccel)*dt;
  return next;
}

void n_steps(unsigned n, TState state0) {
  print_tstate(state0);
  if (n == 0)
    return;
  else {
    auto state = state0;
    for (unsigned k = 0; k < n; ++k) {
      state = verlet_step(state, force(state) / m);
      print_tstate(state);
    }
  }
}

int main() {
  n_steps(12000, TState{0.,
    {-e0 / (w * w * sqrt(2)), 0, 0},
    {0, e0 / (w * sqrt(2)), -.25}});
  return 0;
}

# `livecode-chargedParticle`
---
![](https://travis-ci.org/timtro/livecode-projectile.svg?branch=master)

A simple implementation of an Euler integrator for projectile motion. This program was written (mostly) live, in lecture for SOFE-2850U in Fall 2017.

An implementation of the Verlet Integrator to plot the motion of a charged particle in an electric field.

## Compilation

Compile with
```bash
clang++ -std=c++14 -o projectile projectile.cpp
```
or
```bash
g++ -std=c++14 -o projectile projectile.cpp
```
and run as
```bash
./projectile
```
and watch your terminal fill with numbers.

## Graphing with GGNUPlot
run as 
```bash
./projectile > mydata.dat

gnuplot

splot 'mydata.dat' u 2:3:4'
```
So we only print out columns 3 to 5, giving only the positions!
## Output

The output will be six columns of numbers with the following order:
```
time [s], x-position [m], y-position [m], z-position[m], x-speed [m/s], y-speed [m/s], z-speed[m/s]
```
Example output:   
![](example-output.png)

### Questions:

## 2:
The Euler integration calculates the velocity of the particle at time t + dt by using the acceleration at time t.  This does not account for the fact that the acceleration is also changing based on the position of the particle!  The Verlet integration method derives a more accurate velocity by averaging the acceleration before and after the position change, and also derives the position at time t + dt using the acceleration at time t.

Overall, the Verlet integration takes into account the changing acceleration for the velocity, as well as the particle’s acceleration for the position, two things that Euler’s method did not do.

How does this affect the plotted positions?

As the particle follows a circular path (in the x and y directions), the acceleration is constantly changing (is centripetal).  Because the euler algorithm is less accurate at modelling the velocity and position based on changes in acceleration, we can expect that it will have a larger radius of travel.  This is verified by plotting the x and y coordinates in against each other for each method and comparing them:
![](euler-vs-verlet.png)

Furthermore, as the electric field does not affect motion in the z direction, both methods have the same z position at any given time.

Difference made:

Without much math, it can be seen that the smaller the step size, the lower the difference in the results.  For this particular application, the Euler algorithm yields close results to the Verlet algorithm, both because the step size is sufficiently small and because the motion is circular in the impacted directions (x-y plane).  For more complicated (non-circular) paths with the acceleration impacted only by the position, the Euler algorithm would be less accurate.

## 3: 
A vector constitutes a vector is closed under addition and scalar multiplication. In our case VecR2 is an integer type which does constitutes a vector space because it is closed under addition and scalar multiplication. 
For the two vectors be closed under addition, its sum must be inside of the Vector space.
Let u, v and z be integer type vectors in a 2D Vector Space (VecR2)
Let x, y be the components of vector u and are integer type.
Let x, y be the components of vector v and are integer type.
To add two vectors we must add its components together. 
z = u + v  
u + v = (x, y) + (x, y) ∈ VecR2
u + v = (x+x, y+y)  ∈ VecR2
z = (2x + 2y) ∈ VecR2
Since u and v are vectors in VecR2 type the sum of u and v (vector z) must also be vector inside of VecR2. The sum of u and v (a+c, b+d) is an integer type since all of its components are integers. Hence it is closed under addition. 

Let u be a vector inside a 2D Vector Space (VecR2).
Let x, y be the components of vector u and are integer type.
Let c be an integer type scalar. 
c*u = c * (x, y) ∈ VecR2
c*u = (c * x, c * y) ∈ VecR2
The result of two integers being multiplied(c and u) always results in an integer type. Since the result of scalar multiplication is an integer it can be concluded that u is closed under scalar multiplication.

## 4:

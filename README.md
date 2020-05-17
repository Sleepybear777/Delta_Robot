# DRC - Delta robot controller:
A robot controller that computes the necessary degrees for each joint to reach a 3D coordinate in a cartesian space.
DRC can be used for any custom 3 DOF delta robot that is controlled by servo motors and Arduino framework based microprocessors.
DRC is written in C++, uses the PlatformIO IDE and Arduino framework.
## Freatures:
* Library for converting cartesian coordinates to joint degrees.
* Test pattern - Circle.
## Todo:
* Implement post processor for RoboDK
* Commands trough terminal.
* Trajectory planning
## References:
Computations are based on inverse kinematics from:
R.L. Williams II, “The Delta Parallel Robot: Kinematics Solutions”, Internet Publication,
www.ohio.edu/people/williar4/html/pdf/DeltaKin.pdf, January 2016. 

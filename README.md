# DRC - Delta robot controller:
A robot controller that computes the necessary degrees for each joint to reach a 3D coordinate in a cartesian space.
DRC can be used for any custom 3 DOF delta robot that is controlled by servo motors, esp32 microprocessor and Adafruits 16-Channel 12-bit PWM/Servo Driver.
DRC is written in C++, uses the PlatformIO IDE and Arduino framework.
## Freatures:
* Library for converting cartesian coordinates to joint degrees.
* Local hosted HTML inteface.
* Test pattern - Circle.
* Test pattern - Square.
## Todo:
* HTML interface commands.
* Teach linear point to point.
* Teach circular point to point.
* Trajectory planning
## References:
Computations are based on inverse kinematics from:
R.L. Williams II, “The Delta Parallel Robot: Kinematics Solutions”, Internet Publication,
www.ohio.edu/people/williar4/html/pdf/DeltaKin.pdf, January 2016.
## Required libraries:
* ESPAsyncWebServer - https://github.com/me-no-dev/ESPAsyncWebServer
* AsyncTCP - https://github.com/me-no-dev/AsyncTCP
* Adafruit-PWM-Servo-Driver-Library - https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library

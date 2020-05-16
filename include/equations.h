#include <Arduino.h>
class equations
{
private:
    double Wp=11.671, Sp=40.431, Ub=90.505, Wb=44.904, Up=23.343, LL=59.21, ll=141.427;
    double a=Wb-Up;
    double b=(Sp/2)-(sqrt(3)/2)*Wb;
    double c=Wp-0.5*Wb;
    double theta1=0, theta2=0, theta3=0;
public:
    double getTheta (int thetaNr, double x, double y, double z);

};

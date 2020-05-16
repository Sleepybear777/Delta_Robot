#include "equations.h"

double equations::getTheta(int thetaNr, double x, double y, double z)
{
    switch (thetaNr)
    {
    case 1:
        {
            double E_1=2*LL*(y+a);
            double F_1=2*z*LL;
            double G_1=pow(x,2)+pow(y,2)+pow(z,2)+pow(a,2)+pow(LL,2)+2*y*a-pow(ll,2);
            double t_1M=(-F_1-sqrt(pow(E_1,2)+pow(F_1,2)-pow(G_1,2)))/(G_1-E_1);
            //double t_1P=(-F_1+sqrt(pow(E_1,2)+(F_1,2)-(G_1,2)))/(G_1-E_1);
            //double theta1_1=2*atan(t_1P)*180/PI;
            theta1=-(2*atan(t_1M))*180/PI;
            return theta1;
            break;
        }
    case 2:
        {
            double E_2=-LL*(sqrt(3)*(x+b)+y+c);
            double F_2=2*z*LL;
            double G_2=pow(x,2)+pow(y,2)+pow(z,2)+pow(b,2)+pow(c,2)+pow(LL,2)+2*(x*b+y*c)-pow(ll,2);
            double t_2M=(-F_2-sqrt(pow(E_2,2)+pow(F_2,2)-pow(G_2,2)))/(G_2-E_2);
            //double t_2P=(-F_2+sqrt(pow(E_2,2)+(F_2,2)-(G_2,2)))/(G_2-E_2);
            theta2=-(2*atan(t_2M))*180/PI;
            return theta2;
            break;
        }
    case 3:
        {
            double E_3=LL*(sqrt(3)*(x-b)-y-c);
            double F_3=2*z*LL;
            double G_3=pow(x,2)+pow(y,2)+pow(z,2)+pow(b,2)+pow(c,2)+pow(LL,2)+2*(-x*b+y*c)-pow(ll,2);
            double t_3M=(-F_3-sqrt(pow(E_3,2)+pow(F_3,2)-pow(G_3,2)))/(G_3-E_3);
            //double t_3P=(-F_3+sqrt(pow(E_3,2)+pow(F_3,2)-pow(G_3,2)))/(G_3-E_3);
            theta3 = -(2*atan(t_3M))*180/PI;
            return theta3;
        }
    default:
        return 1;
        break;
    }
}

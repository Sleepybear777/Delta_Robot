#include <Arduino.h>
class commands
{
private:
    double x=0, y=0, z=0;
public:
    void setx(); //K001
    void sety(); //K002
    void setz(); //K003

    double getx(){ return x;}
    double gety(){ return y;}
    double getz(){ return z;}
};



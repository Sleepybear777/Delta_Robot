#include <Arduino.h>
#include "equations.h"
#include "commands.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
double x = 0;
double y = 0;
double z = -148;
double theta1=0, theta2=0, theta3=0;
equations my_equations;
commands my_commands;
uint8_t servonum = 0;
//X-min = -44.9, X-max = 44.9;
//Z-min = -44.9, Z-max = 44.9;
//Z-min =
#define SERVOMIN0   110// This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX0   475// This is the 'maximum' pulse length count (out of 4096) (475)
#define SERVOMIN1   110// This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX1  460 // This is the 'maximum' pulse length count (out of 4096)
#define SERVOMIN2   110// This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX2  460 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

double angleToPulse(int servoNr, double angle)
{
  switch (servoNr)
  {
  //double pulse_sum, pulse_halfsum;
  double angleToPulse;
  case 0:
    /*pulse_sum = SERVOMAX0 - SERVOMIN0; //=365
    pulse_halfsum = pulse_sum / 2; //=182.5
    angleToPulse = SERVOMIN0 + pulse_halfsum + (pulse_halfsum/90)*(angle); /*/
    angleToPulse = 2.0278*angle+292.5;
    //angleToPulse = 1.94*angle+285;
    return angleToPulse;
    break;
  case 1:
    /*pulse_sum = SERVOMAX1 - SERVOMIN1;
    pulse_halfsum = pulse_sum /2;
    angleToPulse = SERVOMIN1 + pulse_halfsum + (pulse_halfsum/90)*(angle);*/
    angleToPulse = 1.94*angle+285;
    return angleToPulse;
    break;
  case 2:
    /*pulse_sum = SERVOMAX2 - SERVOMIN2;
    pulse_halfsum = pulse_sum /2;
    angleToPulse = SERVOMIN2 + pulse_halfsum + (pulse_halfsum/90)*(angle);*/
    angleToPulse = 1.94*angle+285; 
    return angleToPulse;
    break;

  default:
    Serial.println("Servo nr does not exist");
    return 1;
    break;
  }



}
struct Point {
     Point( double X, double Y ): x(X), y(Y) {};
     double x;
     double y;
};//Simple Point structure

Point Center(0,0);
double radius = 30;

void setup() {
  Serial.begin(9600);
  
  Serial.println("8 channel Servo test!");

  pwm.begin();
  // In theory the internal oscillator is 25MHz but it really isn't
  // that precise. You can 'calibrate' by tweaking this number till
  // you get the frequency you're expecting!
  pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz  
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);

  
}

void loop() {

  for (double angle=0; angle<=2*PI; angle+=0.01)
  {//You are using radians so you will have to increase by a very small amount
     //This will have the coordinates  you want to draw a point at
    Point Circle( Center.x + radius*cos( angle ), Center.y + radius*sin( angle ) );
    x= Circle.x;
    y= Circle.y;

    theta1 = my_equations.getTheta(1, x, y, z);
    theta2 = my_equations.getTheta(2, x, y, z);
    theta3 = my_equations.getTheta(3, x, y, z);
    pwm.setPWM(0, 0, angleToPulse(0,theta1));
    pwm.setPWM(1, 0, angleToPulse(1,theta2));
    pwm.setPWM(2, 0, angleToPulse(2,theta3));

  }
  /*int count = 4;
  for (int i = 0; i < count; i++)
    {
      switch (i)
      {
      case 0:
        x=40;
        y=40;
        break;
      case 1:
        x=40;
        y=-40;
        break;
      case 2:
        x=-40;
        y=-40;
        break;
      case 3: 
        x=-40;
        y=40;
        break;
      default:
        i = 0;
        break;
      }
      theta1 = my_equations.getTheta(1, x, y, z);
      theta2 = my_equations.getTheta(2, x, y, z);
      theta3 = my_equations.getTheta(3, x, y, z);
      Serial.println(theta1);
      Serial.println(theta2);
      Serial.println(theta3);
      delay(1000);
      pwm.setPWM(0, 0, angleToPulse(0,theta1));
      pwm.setPWM(1, 0, angleToPulse(1,theta2));
      pwm.setPWM(2, 0, angleToPulse(2,theta3));
    }
  */
}
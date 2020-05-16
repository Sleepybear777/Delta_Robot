#include "commands.h"

void commands::setx()
{
    while(Serial.available() > 0 ){
    String str = Serial.readString();
    x=str.toDouble();
    Serial.println("Received x-coordinate.");
    }
}

void commands::sety()
{
    while(Serial.available() > 0 ){
    String str = Serial.readString();
    y=str.toDouble();
    Serial.println("Received y-coordinate.");
    }
}
void commands::setz()
{
    while(Serial.available() > 0 ){
    String str = Serial.readString();
    z=str.toDouble();
    Serial.println("Received z-coordinate.");
    }
}

#include "equations.h"
#include "commands.h"
#include "WiFi.h"
#include <Adafruit_PWMServoDriver.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "iostream"
//Network setup:

  //Enter network credentials here: 
  const char* ssid     = "";
  const char* password = "";

// Set LED GPIO
  const int ledPin = 2;

// Stores LED state
  String ledState;

// Create AsyncWebServer object on port 80
  AsyncWebServer server(80);
//Servo setup:
  Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
  uint8_t servonum = 0;
  #define SERVOMIN0   110// This is the 'minimum' pulse length count (out of 4096)
  #define SERVOMAX0   475// This is the 'maximum' pulse length count (out of 4096)
  #define SERVOMIN1   110// This is the 'minimum' pulse length count (out of 4096)
  #define SERVOMAX1  460 // This is the 'maximum' pulse length count (out of 4096)
  #define SERVOMIN2   110// This is the 'minimum' pulse length count (out of 4096)
  #define SERVOMAX2  460 // This is the 'maximum' pulse length count (out of 4096)
  #define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

//Joint angle setup:
  double theta1=0, theta2=0, theta3=0;

  bool runCircle = false;
  bool runSquare = false;
//Initializing classes: 
  equations my_equations;
  commands my_commands;

// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if(digitalRead(ledPin)){
      ledState = "ON";
    }
    else{
      ledState = "OFF";
    }
    Serial.print(ledState);
    return ledState;
  }
  return String();
}

double angleToPulse(int servoNr, double angle)
{
  switch (servoNr)
  {
  double angleToPulse;
  case 0:
    angleToPulse = 2.0278*angle+292.5;
    return angleToPulse;
    break;
  case 1:
    angleToPulse = 1.94*angle+285;
    return angleToPulse;
    break;
  case 2:
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
     Point( double X, double Y, double Z ): x(X), y(Y), z(Z) {};
     double x;
     double y;
     double z;
};//Simple Point structure
//Variable setup - circle test
  Point Center(0,0,-120);
  double radius = 30;

void setup() {
  //esp_err_t esp_console_init(const esp_console_config_t *config)
  Serial.begin(115200);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz  
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Route to set GPIO to HIGH
  server.on("/Square", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
    runSquare = true;
    
  });
    // Route to set GPIO to LOW
  server.on("/Circle", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
    runCircle = true;
  });
  // Start server
  server.begin();
}

void loop() {

  if (runCircle)
  {
    for (double angle=0; angle<=2*PI; angle+=0.01)
      {//You are using radians so you will have to increase by a very small amount
          //This will have the coordinates  you want to draw a point at
        Point Circle( Center.x + radius*cos( angle ), Center.y + radius*sin( angle ), -120 );
        theta1 = my_equations.getTheta(1, Circle.x, Circle.y, Circle.z);
        theta2 = my_equations.getTheta(2, Circle.x, Circle.y, Circle.z);
        theta3 = my_equations.getTheta(3, Circle.x, Circle.y, Circle.z);
        pwm.setPWM(0, 0, angleToPulse(0,theta1));
        pwm.setPWM(1, 0, angleToPulse(1,theta2));
        pwm.setPWM(2, 0, angleToPulse(2,theta3));
        Serial.println(Circle.x);
        Serial.println(Circle.y);
        Serial.println(Circle.z);
      }
    runCircle = false;
  }
  if (runSquare)
  {
    int count = 4;
    Point Point(0,0,-120);
    for (int i = 0; i < count; i++)
      {
        switch (i)
        {
        case 0:
          Point.x=40;
          Point.y=40;
          break;
        case 1:
          Point.x=40;
          Point.y=-40;
          break;
        case 2:
          Point.x=-40;
          Point.y=-40;
          break;
        case 3: 
          Point.x=-40;
          Point.y=40;
          break;
        default:
          i = 0;
          break;
        }
        theta1 = my_equations.getTheta(1, Point.x, Point.y, Point.z);
        theta2 = my_equations.getTheta(2, Point.x, Point.y, Point.z);
        theta3 = my_equations.getTheta(3, Point.x, Point.y, Point.z);
        delay(1000);
        pwm.setPWM(0, 0, angleToPulse(0,theta1));
        pwm.setPWM(1, 0, angleToPulse(1,theta2));
        pwm.setPWM(2, 0, angleToPulse(2,theta3));
      }
  runSquare = false;
  }
}
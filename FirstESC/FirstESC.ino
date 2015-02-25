/*
Coded by Marjan Olesch
Sketch from Insctructables.com
Open source - do what you want with this code!
*/
#include <Servo.h>


int value = 0; // set values you need to zero

Servo esc; //Create as much as Servoobject you want. You can controll 2 or more Servos at the same time

void setup() {

  esc.attach(14);    // attached to pin 9 I just do this with 1 Servo
  Serial.begin(9600);    // start serial at 9600 baud
  
}

void loop() {

  //First connect your ESC WITHOUT Arming. Then Open Serial and follo Instructions
  int throttle = analogRead(5);
  throttle = map(throttle, 50, 1023, 0, 179);
  Serial.println(throttle);
  
  esc.write(throttle);
}

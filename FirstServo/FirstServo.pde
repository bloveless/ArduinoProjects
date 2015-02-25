#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(2);
  myServo.write(0);
}

void loop() {
  int i = 0;
  for(i = 0; i < 180; i++) {
    myServo.write(i);
    if(i == 179) {
      i = 0;
    }
    delay(100);
  }
}

int led1Pin = 12;
int led2Pin = 11;
int led3Pin = 10;
int led4Pin = 9;
int led5Pin = 8;
int switchPin = 2;
int lightMode = 0;
int buttonState;
int val;
int val2;

void setup(){
  Serial.begin(9600);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(led5Pin, OUTPUT);
  pinMode(switchPin, INPUT);
}

void checkLightMode() {
  val = digitalRead(switchPin);
  delay(10);
  val2 = digitalRead(switchPin);
  if(val == val2) {
    if(val != buttonState) {
      if(val == LOW) {
        lightMode = ((lightMode + 1) % 4);
        Serial.println(lightMode);
      }
      buttonState = val;
    }
  }
}

void loop(){
  // All off
  if(lightMode == 0) {
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, LOW);
    digitalWrite(led4Pin, LOW);
    digitalWrite(led5Pin, LOW);
    checkLightMode();
  }
  // All on
  if(lightMode == 1) {
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, HIGH);
    digitalWrite(led3Pin, HIGH);
    digitalWrite(led4Pin, HIGH);
    digitalWrite(led5Pin, HIGH);
    checkLightMode();
  }
  // Blinking
  if(lightMode == 2) {
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, HIGH);
    digitalWrite(led3Pin, HIGH);
    digitalWrite(led4Pin, HIGH);
    digitalWrite(led5Pin, HIGH);
    checkLightMode();
    delay(100);
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, LOW);
    digitalWrite(led4Pin, LOW);
    digitalWrite(led5Pin, LOW);
    checkLightMode();
    delay(100);
  }
  if(lightMode == 3) {
    digitalWrite(led1Pin, HIGH);
    checkLightMode();
    delay(100);
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, HIGH);
    checkLightMode();
    delay(100);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, HIGH);
    checkLightMode();
    delay(100);
    digitalWrite(led3Pin, LOW);
    digitalWrite(led4Pin, HIGH);
    checkLightMode();
    delay(100);
    digitalWrite(led4Pin, LOW);
    digitalWrite(led5Pin, HIGH);
    checkLightMode();
    delay(100);
    digitalWrite(led5Pin, LOW);
    digitalWrite(led4Pin, HIGH);
    checkLightMode();
    delay(100);
    digitalWrite(led4Pin, LOW);
    digitalWrite(led3Pin, HIGH);
    checkLightMode();
    delay(100);
    digitalWrite(led3Pin, LOW);
    digitalWrite(led2Pin, HIGH);
    checkLightMode();
    delay(100);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led1Pin, HIGH);
    checkLightMode();
    delay(100);
    digitalWrite(led1Pin, LOW);
  }
  checkLightMode();
}

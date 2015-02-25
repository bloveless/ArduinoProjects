int lrPin = 0;
int udPin = 1;
int lrOffset = 0;
int udOffset = 0;
int lrVal = 0;
int udVal = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(lrPin, INPUT);
  pinMode(udPin, INPUT);
  
  readJoystick();
  lrOffset = lrVal * -1;
  udOffset = udVal * -1;
}

void loop() {
  readJoystick();
  
  Serial.print("LR Pin: ");
  Serial.print(lrVal);
  Serial.print(" - UD Pin: ");
  Serial.println(udVal);
  delay(200);
}

void readJoystick() {
  lrVal = map(analogRead(lrPin), 0, 1023, -100, 100) + lrOffset;
  if(lrVal > 100) lrVal = 100;
  else if(lrVal < -100) lrVal = -100;
  udVal = map(analogRead(udPin), 61, 1023, -100, 100) + udOffset;
  if(udVal > 100) udVal = 100;
  else if(udVal < -100) udVal = -100;  
}

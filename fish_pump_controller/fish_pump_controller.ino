int btnPin = 2;
int relayPin = 3;
int ledPin = 13;

void setup()
{
  // init serial connection
  Serial.begin(9600);
  
  pinMode(btnPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  int buttonState = digitalRead(btnPin);
  if(buttonState == 0)
  {
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, HIGH);
  } else
  {
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, LOW);
  }
  Serial.println(buttonState);
  delay(100);
}

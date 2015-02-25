/*
 * ********* Doorbell Basic BUTTON *****
 * requires pre-paired XBee Radios and teh BELL program on the receiving end
 */
 
 
#define VERSION '1.00a0'

int buttonPin = 14;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial1.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // send a capital D over the serial port if the button is pressed
  if(digitalRead(buttonPin) == HIGH) {
    Serial1.print('D');
    Serial.print('D');
    delay(10); // prevents overwhelming the serial port
  }
}

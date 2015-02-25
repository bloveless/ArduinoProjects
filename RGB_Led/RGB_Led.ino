// Global pin declarations
int redPin = 10;
int greenPin = 9;
int bluePin = 11;
// Global red variables
int oldRedValue = 0;
int newRedValue = 0;
int redIncrement = 0;
// Global green variables
int oldGreenValue = 0;
int newGreenValue = 0;
int greenIncrement = 0;
// Global blue variables
int oldBlueValue = 0;
int newBlueValue = 0;
int blueIncrement = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop()
{
  changeToRandomColor();
//  changeToSpecificColor(255, 0, 0);
//  changeToSpecificColor(0, 255, 0);
//  changeToSpecificColor(0, 0, 255);
}

void changeToRandomColor()
{
  changeToSpecificColor(random(0, 255), random(0, 255), random(0, 255));
}

char tmpString[17];

void changeToSpecificColor(int red, int green, int blue)
{
  newRedValue = red;
  newGreenValue = green;
  newBlueValue = blue;
  
  sprintf(tmpString, "R:%03d G:%03d B:%03d", red, green, blue);
  Serial.println(tmpString);
  
  redIncrement = (newRedValue - oldRedValue) / 10;
  greenIncrement = (newGreenValue - oldGreenValue) / 10;
  blueIncrement = (newBlueValue - oldBlueValue) / 10;
  
  for(int i = 0; i < 10; i++)
  {
    oldRedValue += redIncrement;
    oldGreenValue += greenIncrement;
    oldBlueValue += blueIncrement;
    
    analogWrite(redPin, oldRedValue);
    analogWrite(greenPin, oldGreenValue);
    analogWrite(bluePin, oldBlueValue); 
    
    delay(100);
  }
  
  // in the last write we will set everything to the randomly picked value
  // just incase the value is off by a few due to integer math.
  analogWrite(redPin, newRedValue);
  analogWrite(greenPin, newGreenValue);
  analogWrite(bluePin, newBlueValue); 
  
  // we will also set the oldValue equal to the newValue for the same reason above
  oldRedValue = newRedValue;
  oldGreenValue = newGreenValue;
  oldBlueValue = newBlueValue;
}


#include <SevSeg.h>

// simple array so that pins can be accessed by their names i.e. pin[1] (on bubble) is actually pin 8 (on board)
int pin[] = {0,8,9,10,11,12,14,2,3,4,5,6,7};
int numbers[] =
{
  0b11111100, //0
  0b01100000, //1
  0b11011010, //2
  0b11110010, //3
  0b01100110, //4
  0b10110110, //5
  0b10111110, //6
  0b11100000, //7
  0b11111110, //8
  0b11100110  //9
};

int digit1 = pin[1];
int digit2 = pin[10];
int digit3 = pin[4];
int digit4 = pin[6];

int segA = pin[12];
int segB = pin[11];
int segC = pin[3];
int segD = pin[8];
int segE = pin[2];
int segF = pin[9];
int segG = pin[7];
int segDP = pin[5];

int pingPin = 15;
int ledPin = 13;
int a1Pin = 16;
int a2Pin = 17;

long duration, inches, cm;
int lastTime = 0;

void setup()
{
  // don't forget that we are skipping the first pin everywhere since ther is no pin 0 on the bubble display
  for(int i = 1; i < sizeof(pin); i++)
  {
    pinMode(pin[i], OUTPUT);
  }
  
  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH);
  
  pinMode(a1Pin, OUTPUT);
  pinMode(a2Pin, OUTPUT);
  
  Serial.begin(9600);
  
  lastTime = millis();
}

void loop()
{
  WriteNumber(inches);
  
  if(inches > 10)
  {
    digitalWrite(a1Pin, HIGH);
    digitalWrite(a2Pin, LOW);
  } else
  {
    digitalWrite(a1Pin, LOW);
    digitalWrite(a2Pin, HIGH);
  }
  
  // the distance will update 10 times a second
  if((millis() - lastTime) > 100)
  {
    inches = ReadDistance();
    lastTime = millis();
  }
}

int ReadDistance()
{
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return duration / 74 / 2;
}

void WriteNumber(int number)
{
  if(number >= 1000)
  {
    WriteToDisplay(4, numbers[(number % 10)]);
    number /= 10;
  }
  
  if(number >= 100)
  {
    WriteToDisplay(3, numbers[(number % 10)]);
    number /= 10;
  }
  
  if(number >= 10)
  {
    WriteToDisplay(2, numbers[(number % 10)]);
    number /= 10;
  }
  
  if(number >= 1)
  {
    WriteToDisplay(1, numbers[(number % 10)]);
    number /= 10;
  }
}

void PrintBren()
{
  // write a b to the first digit
  WriteToDisplay(1, 0b11111110);
  
  // write an r to the third digit
  WriteToDisplay(2, 0b00001010);
  
  // write an e to the third digit
  WriteToDisplay(3, 0b10011110);
  
  // write an n to the forth digit
  WriteToDisplay(4, 0b11101100);
}

void PrintSara() {
  // write an s to the first digit
  WriteToDisplay(1, 0b10110110);

  // write an a to the second digit
  WriteToDisplay(2, 0b11101110);
  
  // write a r to the third digit
  WriteToDisplay(3, 0b00001010);
  
  // write an a to the forth digit
  WriteToDisplay(4, 0b11101110);
}

void PrintEryn()
{
  // write an e to the first digit
  WriteToDisplay(1, 0b10011110);

  // write an r to the second digit
  WriteToDisplay(2, 0b00001010);
  
  // write a y to the third digit
  WriteToDisplay(3, 0b01110110);
  
  // write an n to the forth digit
  WriteToDisplay(4, 0b11101100);
}

void WriteToDisplay(int digit, int pattern)
{
  digitalWrite(segA, (pattern & 0b10000000));
  digitalWrite(segB, (pattern & 0b01000000));
  digitalWrite(segC, (pattern & 0b00100000));
  digitalWrite(segD, (pattern & 0b00010000));
  digitalWrite(segE, (pattern & 0b00001000));
  digitalWrite(segF, (pattern & 0b00000100));
  digitalWrite(segG, (pattern & 0b00000010));
  digitalWrite(segDP,(pattern & 0b00000001));
  
  digitalWrite(digit1, HIGH);
  digitalWrite(digit2, HIGH);
  digitalWrite(digit3, HIGH);
  digitalWrite(digit4, HIGH);
  
  if(digit == 1)
    digitalWrite(digit1, LOW);
  else if(digit == 2)
    digitalWrite(digit2, LOW);
  else if(digit == 3)
    digitalWrite(digit3, LOW);
  else if(digit == 4)
    digitalWrite(digit4, LOW);
  
  delay(5);
}


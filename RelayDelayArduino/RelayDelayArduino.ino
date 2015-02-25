#include <SoftwareSerial.h>
// avr-libc library includes
#include <avr/io.h>
#include <avr/interrupt.h>

SoftwareSerial LCD(0,8); // pin 8 = TX, pin 0 = RX (unused)

/*
  Relay Delay
 */

int relayPin = 7;
int potPin = 0;
int redPin = 11;
int greenPin = 10;
int bluePin = 9;
int analogValue = 0;
int incrementValue = 1;

char tempPot[15];

volatile int potToMinutes = 0;

volatile int timerCountDown = 0;
char tempCountDown[10]; // create string arrays

boolean countDownMode = false;

// the setup routine runs once when you press reset:
void setup()
{
  // initialize Timer1
  cli();          // disable global interrupts
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B

  // set compare match register to desired timer count:
  OCR1A = 15624;
  // turn on CTC mode:
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  // enable timer compare interrupt:
  TIMSK1 |= (1 << OCIE1A);
  sei();          // enable global interrupts
  
  pinMode(relayPin, OUTPUT);
  
  attachInterrupt(0, buttonPressed, RISING);
  
  Serial.begin(9600);
  LCD.begin(9600); // set up serial port for 9600 baud
  delay(500); // wait for display to boot up
  clearScreen();
  
  LCD.write(254); // move cursor to beginning of first line
  LCD.write(128);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  digitalWrite(greenPin, HIGH);
  digitalWrite(redPin, LOW);
}

void buttonPressed()
{
  if(!countDownMode)
  {
    clearScreen();
    digitalWrite(relayPin, HIGH);
    countDownMode = true;
    timerCountDown = potToMinutes * 60;
  }
}

ISR(TIMER1_COMPA_vect)
{
  if(timerCountDown > 0)
  {
    timerCountDown--;
  }
}

// the loop routine runs over and over again forever:
void loop()
{
  // Since the actual scale is from 0 to 1024 we will rescale the pot up to 1024
  // The pot has a resistor to keep the potentometer safe
  int potReading = 1024 * (analogRead(potPin)/935.00);
  potToMinutes = (potReading / 51) + 1;

  if(countDownMode)
  {
    LCD.write(254); // move cursor to beginning of first line
    LCD.write(128);
    
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, HIGH);
    
    gotToBeginning();
    sprintf(tempCountDown,"Time Left: %04d", timerCountDown);
    LCD.write(tempCountDown);
    
    if(timerCountDown <= 0)
    {
      clearScreen();
      countDownMode = false;
      digitalWrite(relayPin, LOW);
    }
  } else
  {
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin, LOW);
    
    gotToBeginning();
    sprintf(tempPot, "Minutes: %02d", potToMinutes);
    LCD.write(tempPot);
  }
  
  // give everything a break for 1/4 a second
  delay(250);
}

void clearScreen()
{
  LCD.write("                "); // clear display
  LCD.write("                ");
  
  gotToBeginning();
}

void gotToBeginning()
{
  LCD.write(254); // move cursor to beginning of first line
  LCD.write(128);
}

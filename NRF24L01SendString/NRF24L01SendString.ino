/* YourDuinoStarter Example: nRF24L01 Transmit Joystick values
 - WHAT IT DOES: Reads Analog values on A0, A1 and transmits
   them over a nRF24L01 Radio Link to another transceiver.
 - SEE the comments after "//" on each line below
 - CONNECTIONS: nRF24L01 Modules See:
 http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 9
   4 - CSN to Arduino pin 10
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
   - 
   Analog Joystick or two 10K potentiometers:
   GND to Arduino GND
   VCC to Arduino +5V
   X Pot to Arduino A0
   Y Pot to Arduino A1
   
 - V1.00 11/26/13
   Based on examples at http://www.bajdi.com/
   Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN   9
#define CSN_PIN 10

// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe


/*-----( Declare objects )-----*/
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
/*-----( Declare Variables )-----*/
int character[1];  // 2 element array holding Joystick readings
String message = "";

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}//--(end setup )---

bool serialFinished = false;

void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  while(Serial.available() > 0)
  {
    char curCharacter = Serial.read();
    Serial.print(curCharacter);
    message.concat(curCharacter);
    if(curCharacter == '\r')
    {
      Serial.println("Found newline");
      serialFinished = true;
    }
  }
  
  if(serialFinished)
  {
    Serial.println("Serial Finished");
    Serial.println(message);
    serialFinished = false;
    sendMessage();
    message = "";
  }
  
}//--(end main loop )---

void sendMessage()
{
  for(int i = 0; i < message.length(); i++)
  {
    character[0] = message.charAt(i);
    // Serial.print("Sending ");
    // Serial.print(" (");
    // Serial.print((int) character[0]);
    // Serial.print(") ");
    // Serial.println((char) character[0]);
    radio.write( character, sizeof(character) );
  } 
}

/*-----( Declare User-written Functions )-----*/

//NONE
//*********( THE END )***********


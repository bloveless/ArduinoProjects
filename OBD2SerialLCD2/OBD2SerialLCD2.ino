#include <SoftwareSerial.h>

SoftwareSerial lcd(4,5);
SoftwareSerial obd2(2,3);

//Set up string buffer
char rxData[20];
char rxIndex=0;

void setup()
{
  Serial.begin(9600);
  lcd.begin(9600);
  obd2.begin(9600);
  
  //Clear the old data from the LCD.
  lcd.write(254);
  lcd.write(1);  
  
  //Put the speed header on the first row.
  lcd.print("Speed: ");
  lcd.write(254);
  //Put the RPM header on the second row.
  lcd.write(128+64);
  lcd.print("RPM: ");
  
  delay(1500);
  //Reset the OBD-II-UART
  obd2.print("ATZ\r");
  //Wait for a bit before starting to send commands after the reset.
  delay(2000);
  //Wait for a bit before starting to send commands after the reset.
  OBD_read();
  obd2.print("ATE0\r");
  OBD_read();
  obd2.flush();  
}

void loop() 
{
  //Delete any data that may be in the serial port before we begin.  
  Serial.flush();
  //Set the cursor in the position where we want the speed data.
  lcd.write(254);
  lcd.write(128+7);
  
  //Print the speed data to the lcd
  lcd.print(getMPH());
  // We add the spaces at the end of the mph so it will
  // clear out any left over characters if the mph goes
  // down from say 100 to 50 to 5 so the h isn't
  // duplicated anywhere and so we don't have to ever
  // clear the lcd
  lcd.print(" mph  ");
  
  //Delete any data that may be left over in the serial port.
  Serial.flush();
  //Move the serial cursor to the position where we want the RPM data.
  lcd.write(254);
  lcd.write(128 + 69);
  
  //Print the rpm data to the lcd
  lcd.print(getRPM());
  // spaces added here because... see comment above mph
  lcd.print("  "); 
  
  delay(100);
}

int getRPM(void)
{
  //Query the OBD-II-UART for the Vehicle rpm
  obd2.flush();
  obd2.print("010C\r");
  OBD_read();
  //NOTE: RPM data is two bytes long, and delivered in 1/4 RPM from the OBD-II-UART
  return ((strtol(&rxData[6],0,16)*256)+strtol(&rxData[9],0,16))/4;
}

int getMPH(void)
{
  //Query the OBD-II-UART for the Vehicle speed
  obd2.flush();
  obd2.print("010D\r");
  OBD_read();
  // returns the value in kilometers so we need to change it to MPH
  return (strtol(&rxData[6],0,16)) * .621371;
}

void OBD_read(void)
{
  char c;
  do{
    if(obd2.available() > 0)
    {
      c = obd2.read();
      Serial.print(c);
      if((c!= '>') && (c!='\r') && (c!='\n')) //Keep these out of our buffer
      {
        rxData[rxIndex++] = c; //Add whatever we receive to the buffer
      }  
    }     
  } while(c != '>'); //The ELM327 ends its response with this char so when we get it we exit out.
  rxData[rxIndex++] = '\0';//Converts the array into a string
  rxIndex=0; //Set this to 0 so next time we call the read we get a "clean buffer"
  Serial.println();
}

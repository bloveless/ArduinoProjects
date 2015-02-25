#include <Wire.h>
#include <SoftwareSerial.h>
#define DS1307_I2C_ADDRESS 0x68  // This is the I2C address
SoftwareSerial lcd(0, 4); // RX (unused), TX

// Global Variables
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
int pm = 0;
char timeString[12];
char dateString[17];
char* Day[] = {"","Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
char* Mon[] = {"","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ((val/10*16) + (val%10));
}

// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ((val/16*10) + (val%16));
}

char intToChar(char c)
{
  return (char)(((int)'0')+c);
}

// 1) Sets the date and time on the ds1307
// 2) Starts the clock
// 3) Sets hour mode to 24 hour clock
// Assumes you're passing in valid numbers, Probably need to put in checks for valid numbers.

void setDateDs1307()                
{
  second = (byte) ((Serial.read() - 48) * 10 + (Serial.read() - 48)); // Use of (byte) type casting and ascii math to achieve result.  
  minute = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  hour  = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  dayOfWeek = (byte) (Serial.read() - 48);
  dayOfMonth = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  month = (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));
  year= (byte) ((Serial.read() - 48) *10 +  (Serial.read() - 48));

  second = 0;
  minute = 47;
  hour = 13;
  dayOfWeek = 6;
  dayOfMonth = 4;
  month = 1;
  year = 14;

  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0x00);
  Wire.write(decToBcd(second) & 0x7f);    // 0 to bit 7 starts the clock
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));      // If you want 12 hour am/pm you need to set
  // bit 6 (also need to change readDateDs1307)
  Wire.write(decToBcd(dayOfWeek));
  Wire.write(decToBcd(dayOfMonth));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
}

// Gets the date and time from the ds1307 and prints result
void updateDate()
{
  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);

  // A few of these need masks because certain bits are control bits
  second     = bcdToDec(Wire.read() & 0x7f);
  minute     = bcdToDec(Wire.read());
  hour       = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm
  dayOfWeek  = bcdToDec(Wire.read());
  dayOfMonth = bcdToDec(Wire.read());
  month      = bcdToDec(Wire.read());
  year       = bcdToDec(Wire.read());

  // add hours
  if(hour > 12)
  {
    pm = 1;
    hour = hour - 12;
  }
  timeString[0] = intToChar(hour / 10);
  timeString[1] = intToChar(hour % 10);
  // add minutes
  timeString[2] = ':';
  timeString[3] = intToChar(minute / 10);
  timeString[4] = intToChar(minute % 10);
  // add seconds
  timeString[5] = ':';
  timeString[6] = intToChar(second / 10);
  timeString[7] = intToChar(second % 10);
  // am\pm
  timeString[8] = ' ';
  if(pm)
  {
    timeString[9] = 'p';
  } else
  {
    timeString[9] = 'a';
  }
  timeString[10] = 'm';
  timeString[11] = '\0';
  
  // add day name
  dateString[0] = Day[dayOfWeek][0];
  dateString[1] = Day[dayOfWeek][1];
  dateString[2] = Day[dayOfWeek][2];
  // add month
  dateString[3] = ' ';
  dateString[4] = Mon[month][0];
  dateString[5] = Mon[month][1];
  dateString[6] = Mon[month][2];
  // add day number
  dateString[7] = ' ' ;
  dateString[8] = intToChar(dayOfMonth / 10);
  dateString[9] = intToChar(dayOfMonth % 10);
  // add year
  dateString[10] = ',';
  dateString[11] = ' ';
  dateString[12] = '2';
  dateString[13] = '0';
  dateString[14] = intToChar(year / 10);
  dateString[15] = intToChar(year % 10);
  dateString[16] = '\0';
}

void setup() {
  Wire.begin();
  Serial.begin(57600);
  lcd.begin(9600);
  lcd.write(254);
  lcd.write(1);  // clear the lcd
  lcd.write(254); // move cursor to beginning of first line
  lcd.write(128);
  lcd.print("  Buba's Clock! Love you Bub  -B");
  delay(2000);
  lcd.write(254);
  lcd.write(1);
}

void loop() {
  updateDate();
  lcd.write(254); // move cursor to fourth character of the first line
  lcd.write(130);
  lcd.write(timeString);
  lcd.write(254); // move cursor to beginning of second line
  lcd.write(192);
  lcd.write(dateString);
  delay(1000);
}


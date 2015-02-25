/*
 * Math is fun!
 */

#include "math.h"               // include the Math Library

int i = 3;
int r = 470;
int v;

void setup()
{
  Serial.begin(9600);
  Serial.print("Current = ");
  Serial.println(i);
  
  Serial.print("Resistance = ");
  Serial.println(r);
  
  Serial.print("Voltage = ");
  Serial.println(i*r);
}

void loop()
{
}

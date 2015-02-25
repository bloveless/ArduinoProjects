/*
 Fade
 
 This example shows how to fade an LED on pin 9
 using the analogWrite() function.
 
 This example code is in the public domain.
 
 */
#include "variables.h"
int num = 0;

void setup()  {
  // set all the pins to output
  int i;
  for( i = 0; i < 8; i++ ) {
    pinMode(all[i], OUTPUT);
  }
  pinMode(13, INPUT);
  displayNumber(0);
  Serial.begin(9600);
}

void loop()  {
    int val = analogRead(A0);
    int digit = val / 100;
    Serial.println(val);
    reset();
      displayNumber(digit);
      if(num >= 9) {
        num = -1;
      }
      /* while ( val == 1 ) {
        val = digitalRead(13);
      } */
  // wait for 30 milliseconds to see the dimming effect
}

void displayNumber(int number) {
  if( num == 0 ) {
      displayCharacter( n0 );
    } else if ( num == 1 ) {
      displayCharacter( n1 );
    } else if ( num == 2 ) {
      displayCharacter( n2 );
    } else if ( num == 3 ) {
      displayCharacter( n3 );
    } else if ( num == 4 ) {
      displayCharacter( n4 );
    } else if ( num == 5 ) {
      displayCharacter( n5 );
    } else if ( num == 6 ) {
      displayCharacter( n6 );
    } else if ( num == 7 ) {
      displayCharacter( n7 );
    } else if ( num == 8 ) {
      displayCharacter( n8 );
    } else if ( num == 9 ) {
      displayCharacter( n9 );
    }
}

void displayCharacter(int character[]) {
  // draw the letter
  int i;
  int len = character[0];
  Serial.println(len);
  for( i = 1; i <= len; i++ ) {
    digitalWrite(character[i], HIGH);
  }  
}

// turn off all the segments
void reset() {
  int i;
  for( i = 0; i < 8; i++ ) {
    digitalWrite(all[i], LOW);
  }
}

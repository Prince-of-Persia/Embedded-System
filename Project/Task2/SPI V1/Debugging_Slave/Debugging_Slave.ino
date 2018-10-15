// Written by Nick Gammon
// September 2011

//  #include "pins_arduino.h"
#include "LiquidCrystal_I2C.h"
#include <Wire.h>
char buf [1000];
volatile int inpoint, outpoint;


byte address = 0x27;      // LCD I2C address
int columns = 20;         // number of columns on LCD
int rows = 4;             // number of rows on LCD
LiquidCrystal_I2C lcd(address, columns, rows);  

void setup (void)
{
  Serial.begin (9600);   // debugging
lcd.begin();  

  Serial.println ();
  Serial.println (F("Commencing debugging session ..."));
  Serial.println ();
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  // turn on SPI in slave mode
  SPCR |= bit (SPE);

  // now turn on interrupts
  SPCR |= bit (SPIE);

}  // end of setup


// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR;  // grab byte from SPI Data Register
  int next = inpoint + 1;  // next insert point

  // wrap-around at end of buffer
  if (next >= sizeof buf)
    next = 0;

  if (next == outpoint)  // caught up with removal point?
    return;  // give up

  // insert at insertion point
  buf [inpoint] = c;
  inpoint = next;  // advance to next

}  // end of interrupt routine SPI_STC_vect

void loop (void)
{
  // insertion and removal point the same, nothing there
  noInterrupts ();  // atomic test of a 16-bit variable
  if (outpoint == inpoint)
  {
    interrupts ();
    return;
  }
  interrupts ();

  // display anything found in the circular buffer
  
  // Place Energia in first column, first row


  lcd.print (buf [outpoint]);
  noInterrupts ();
  if (++outpoint >= sizeof buf)
    outpoint = 0;  // wrap around
  interrupts ();

}  // end of loop

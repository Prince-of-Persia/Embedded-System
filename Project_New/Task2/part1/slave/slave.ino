#include <Wire.h> 
#include <SPI.h>
#include "LiquidCrystal_I2C.h"

char buf [100];
volatile byte pos;
volatile bool process_it;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup()
{
	lcd.begin(); // initialize the LCD
	lcd.backlight(); // Turn on the blacklight and print a message.
	Serial.begin (9600);   // debugging
  SPCR |= bit (SPE); // turn on SPI in slave mode
  pinMode (MISO, OUTPUT); // have to send on master in, *slave out*
  // get ready for an interrupt
  pos = 0;   // buffer empty
  process_it = false;
  SPI.attachInterrupt(); // now turn on interrupts
}

void loop()
{
	lcd.setCursor(0, 0);
  //lcd.print("Hello, world!");
  if (process_it)
  {
	  buf [pos] = 0;
	  Serial.println (buf);
	  lcd.clear();
	  lcd.setCursor(0, 0);
	  lcd.print(buf);
	  pos = 0;
	  process_it = false;
  }  // end of flag set	

  delay(1000);
}

// SPI interrupt routine
ISR (SPI_STC_vect)
{
	byte c = SPDR;  // grab byte from SPI Data Register
  // add to buffer if room
  if (pos < sizeof(buf))
  {
    buf[pos++] = c;
    // example: newline means time to process buffer
    if (c == '\n')
    {
    	buf[pos-1] = ' ';
      process_it = true;
    }
  }  // end of room available
}  // end of interrupt routine SPI_STC_vect


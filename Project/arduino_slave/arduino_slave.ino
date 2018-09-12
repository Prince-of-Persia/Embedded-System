#include <Wire.h>
#include <SPI.h>
#include "LiquidCrystal_I2C.h"

char buf [100];
volatile byte pos;
volatile bool process_it;

//Set the LCD address to 0x27 for a 16 chars and 2 line display
//Should we maybe include our address function here instead Amir?
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  lcd.backlight();
  
  Serial.begin(9600);
  //Turn on SPI in slave mode
  SPCR |= bit(SPE);
  //have to sned on master in, *slave out*
  pinMode(MISO, OUTPUT);
  //get ready for an interrupt
  pos = 0; //buffer empty
  process_it = false;
  //now turn on interrupts
  SPI.attachInterrupt();
}

//SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR; //grab byte fro SPI Data Register
  //add to buffer if room
  if (pos < sizeof buf)
  {
    buf[pos++] = c;
    //example: newline means time to process buffer
    if(c == '\n')
      process_it = true;
    
    } //end of room available
} //end of interrupt routine SPI_STC_vect


void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  lcd.print("We be testin");
  delay(2000);
  if (process_it)
  {
    buf[pos] = 0;
    Serial.println(buf);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(buf);
    pos = 0;
    process_it = false;
  } // end of flag set
}

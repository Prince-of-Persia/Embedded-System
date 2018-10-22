#include <SPI.h>
int counter = 0;

void setup()
{
	Serial.begin(9600);
  // Put SCK, MOSI, SS pins into output mode
  pinMode(SCK, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(SS, OUTPUT);
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  digitalWrite(SS, HIGH);  // ensure SS stays high for now
  digitalWrite(SCK, LOW);
  digitalWrite(MOSI, LOW);
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();
  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}


void loop()
{
  char c;
  if (counter == 0)
  {
    digitalWrite(SS, LOW);
    for(const char * p = "Y\n"; c = *p; p++)
    {
      SPI.transfer(c);
      Serial.print(c);
    }
    digitalWrite(SS, HIGH);
    counter = 1;
  }
  else if (counter == 1)
  {
    digitalWrite(SS, LOW);
    for(const char * p = "N\n"; c = *p; p++)
    {
      SPI.transfer(c);
      Serial.print(c);
    }
    digitalWrite(SS, HIGH);
    counter = 0;
  }
	delay(1000);
}
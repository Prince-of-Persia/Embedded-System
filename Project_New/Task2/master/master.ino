#include <SPI.h>

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
	digitalWrite(SS, LOW);
	for(const char * p = "Hello, World!\n"; c = *p; p++)
	{
		SPI.transfer(c);
		Serial.print(c);
	}
	digitalWrite(SS, HIGH);
	delay(1000);
}
#include <SPI.h>
int toggle = 0;
void setup (void)
{

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

}  // end of setup


void loop (void)
{

  char c;

  // enable Slave Select
  digitalWrite(SS, LOW);    // SS is pin 10

if(toggle)
{
  // send test string
  for (const char * p = "FirstName\n" ; c = *p; p++)
    SPI.transfer (c);
     toggle = 0;
}
else
{
  // send test string
  for (const char * p = "SecondName\n" ; c = *p; p++)
    SPI.transfer (c);
     toggle = 1;
}


  // disable Slave Select
  digitalWrite(SS, HIGH);

  delay (2000);  // 2 seconds delay
}  // end of loop

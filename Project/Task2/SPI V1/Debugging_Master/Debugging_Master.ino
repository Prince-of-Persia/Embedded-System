// make true to debug, false to not
#define DEBUG true
#include <SPI.h>
#include "SPI_Debugging.h"

long counter;
unsigned long start;

void setup() 
{

  beginDebug ();

}  // end of setup

void loop() 
{
   counter++;
  if (counter == 100000)
  {
    Trace("TEST  ");
   
    counter = 0;
  }  // end of if
  
}  // end of loop

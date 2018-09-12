/*
    Copyright (C) 2018  Amir Raajbifar

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <SPI.h>
int toggle = 0;

void setup()
{
  //SCK, MOSI and SS pins in output mode
  pinMode(SCK, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(SS, OUTPUT);

  //SCK and MOSI in LOW state, SS in HIGH state
  digitalWrite(SS, HIGH); //needs to stay HIGH for now
  digitalWrite(SCK, LOW);
  digitalWrite(MOSI, LOW);

  //Puts SPI hardware into Master mode and turn SPI on
  SPI.begin();
  //Slow down Master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}

void loop()
{
  char c;
  //enable Slave Select
  digitalWrite(SS, LOW); // SS is pin 10 for some reason????

  if(toggle)
  {
    //send test string
    for (const char * p = "FirstName\n" ; c = *p; p++)
    {
      SPI.transfer (c);
      toggle = 0;
    }
  }
  else
  {
    //send test string
    for (const char * p = "SecondName\n" ; c = *p; p++)
    {
      SPI.transfer (c);
      toggle = 1;    
    }
  }
  
 //disable Slave Select
 digitalWrite(SS, HIGH);
 delay(2000);
}

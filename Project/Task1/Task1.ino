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

#include "Task1.h"

#define MAX_PROCESSES 3 //Maximum number of processes

//#define DEBUG

volatile int btnFlag = LOW;
int counter = 1; // A counter for number of processes
int32_t temperature; //raw temp readings
int32_t threshold = 23; // temperature threshold

LiquidCrystal_I2C lcd(16, 2); //Create a LCD instance
NTC_FR myNTC; //Create a temp sens instance
Servo myservo; //Create servo object to control a servo
int pos = 0; //variable to store the servo position

void setup()
{
	pinMode(PUSH2, INPUT_PULLUP); //set the push button 2 as input with the pull up resistor
	attachInterrupt(PUSH2, count, FALLING); //Interrupt id fired whenever button is pressed	
	Serial.begin(9600);
	Serial.println("Initialized");
	Wire.begin();
	lcd.init(); 		//Initialize LCD
	lcd.backlight();	//Turn ICD backlight on
	myNTC.begin();		//Initialize Temp Sensor
  myservo.attach(9) //attaches the servo on pin 9 to the servo object, CHECK

}

void loop()
{
	lcd.clear(); //Clear everyting on LCD
	if (btnFlag)
	{
		if (counter == MAX_PROCESSES) counter = 1;
		else counter++;
		btnFlag = LOW;
	}
	switch (counter) 
	{
	    case 1:
		// Name -> LCE
		#ifdef DEBUG
			Serial.print(counter);
			Serial.print('\t');
			Serial.println("Mode 1");
		#else
			lcd.setCursor(0,0);
			lcd.print("Amir Nafisa");
			lcd.setCursor(0,1);
			lcd.print("Elvira");
		#endif
		break;
	    case 2:
		// Temp -> LCD
		// Temp (trigger) -> servo
		#ifdef DEBUG
			Serial.print(counter);
			Serial.print('\t');
			Serial.println("Mode 2");
		#else
			myNTC.get();
			myNTC.celsiusX10(temperature);
			myNTC.lcdPrint(temperature, lcd, 'C');
			myNTC.fahrenheitX10(temperature);
			myNTC.lcdPrint(temperature, lcd, 'F');
          
          //SERVOSWIPE//
      while(temperature > threshold)
      {
        for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
        {                                  // in steps of 1 degree 
          myservo.write(pos);              // tell servo to go to position in variable 'pos' 
          delay(15);                       // waits 15ms for the servo to reach the position 
        } 
        for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
        {                                
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
        }
      } //end of while loop
       
		#endif
		break;
	    case 3:
		// acce -> LCD
		// acce -> LEDs
		#ifdef DEBUG
			Serial.print(counter);
			Serial.print('\t');
			Serial.println("Mode 3");
		#else

		#endif
    	break;
	    default:
		// ERROR
		break;
	}
	delay(1250);
}

void count()
{
	static unsigned long last_int_time = 0;
	unsigned long int_time = millis();
	if (int_time - last_int_time > 200)
	{
		btnFlag = HIGH;
	}
	last_int_time = int_time;
}

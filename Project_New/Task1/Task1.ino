// Core library - MCU-based
#if defined(__MSP430FR5739__) // FraunchPad only
#include "Energia.h"
#else // error
#error Platform not supported. FraunchPad only.
#endif

// Include application, user and local libraries
#include <Wire.h>
#include <Servo.h>
#include "FraunchPad_NTC.h"
#include "Accelerometer.h"
#include "LiquidCrystal_I2C.h"

#define MAX_PROCESSES 4 				// Maximum number of processes

volatile int btnFlag = LOW;

//Object instance
LiquidCrystal_I2C myLcd(16,2);	// LCD Display
NTC_FR myNTC;										// Temp sensor
Accelerometer myAcc;						// Accelerometer sensor 
Servo myServo;									// Servo Thingy 

int counter = 1;								// A counter for number of processes
uint32_t temperature;						// Actual Temperature
uint32_t tempThreshold = 200;			// Temprature Threshold

void setup()
{
	pinMode(PUSH2, INPUT_PULLUP);						// Set push button2 as input with pull up resistor
	attachInterrupt(PUSH2, count, RISING);	// Interrupt is fired whenever button is pressed

	// Initialize attached objects
	Wire.begin();
	myLcd.init();
	myLcd.backlight();
	myNTC.begin();
	myAcc.begin();
	myServo.attach(22);
	Serial.begin(9600);
}

void loop()
{
	myLcd.clear();
	if(btnFlag)
	{
		if(counter == MAX_PROCESSES) counter = 1;
		else counter++;
		btnFlag = LOW;
	}
	switch(counter)
	{
		case 1:
			myLcd.setCursor(0,0);
			myLcd.print("Amir Nafisa");
			myLcd.setCursor(0,1);
			myLcd.print("Elvira");
		break;
		case 2:
			//myLcd.print("Case 2");
			myNTC.get();
			myNTC.celsiusX10(temperature);
			myLcd.setCursor(0,0);
			myLcd.print(temperature);
			temperature=(temperature*(9/5)+32);
			myLcd.setCursor(0,1);
			myLcd.print(temperature);
			while(temperature > tempThreshold)
      
			{
        if(btnFlag)
        {
          counter++
          btnFlag=LOW
          break
         }
				for (int pos = 0; pos < 180; ++pos)
				{
					myServo.write(pos);
					delay(15);
				}
				for (int pos = 180; pos >= 1; --pos)
				{
					myServo.write(pos);
					delay(15);
				}
			}
		break;
		case 3:
			myLcd.setCursor(0,0);
			//myLcd.print("Case 3");
			myAcc.read();
			myAcc.lcdPrint(myLcd);
		break;
		case 4:
			myLcd.print("Case 4");
			myLcd.setCursor(0,0);
     if (Serial.available() > 0)
     {
      pos = Serial.parseInt();
      myServo.write(pos);
      Serial.println(pos);
      delay(1000);
      }
     
		break;
	}
	delay(50);
}

void count()
{
	static unsigned long lastIntTime = 0;
	unsigned long intTime = millis();
	if(intTime - lastIntTime > 200) btnFlag = HIGH;
	lastIntTime = intTime;
}

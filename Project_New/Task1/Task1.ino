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

int counter = 3;								// A counter for number of processes
uint32_t temperature;						// Actual Temperature
uint32_t tempThreshold = 200;			// Temprature Threshold

uint8_t LED[] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};
uint8_t accY = 0;

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
	for (int i = 0; i < sizeof(LED); ++i)
	{
		pinMode(LED[i], OUTPUT);
		digitalWrite(LED[i], LOW);
	}

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
			Serial.println("Case 1");
			myLcd.setCursor(0,0);
			myLcd.print("Amir Nafisa");
			myLcd.setCursor(0,1);
			myLcd.print("Elvira");
		break;
		case 2:
			//myLcd.print("Case 2");
			Serial.println("Case 2");
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
          counter++;
          btnFlag=LOW;
          break;
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
			//Serial.println("Case 3");
			myLcd.setCursor(0,0);
			//myLcd.print("Case 3");
			myAcc.read();
			myAcc.lcdPrint(myLcd);
			/*
			for (int i = 0; i < sizeof(LED)+2; ++i)
			{
				digitalWrite(LED[i], HIGH);
				delay(50);
				digitalWrite(LED[i-2], LOW);
				delay(50);
			}
			*/
			accY = myAcc.getY();
			accY = map(accY, -300, 300, -4, 4);
			Serial.print("accY: ");
			Serial.println(accY);
			if (accY >= 2)
			{
				digitalWrite(LED[3], HIGH);
				delay(50);
				digitalWrite(LED[4], HIGH);
				delay(50);
				digitalWrite(LED[5], HIGH);
				delay(50);
				digitalWrite(LED[6], HIGH);
				delay(50);
				digitalWrite(LED[7], HIGH);
				delay(50);
				digitalWrite(LED[4], LOW);
				delay(50);
				digitalWrite(LED[3], LOW);
				delay(50);
				digitalWrite(LED[2], LOW);
				delay(50);
				digitalWrite(LED[1], LOW);
				delay(50);
				digitalWrite(LED[0], LOW);
			}if (accY < 2)
			{
				digitalWrite(LED[3], HIGH);
				delay(50);
				digitalWrite(LED[4], HIGH);
				delay(50);
				digitalWrite(LED[5], HIGH);
				delay(50);
				digitalWrite(LED[6], HIGH);
				delay(50);
				digitalWrite(LED[7], HIGH);
				delay(50);
				digitalWrite(LED[4], LOW);
				delay(50);
				digitalWrite(LED[3], LOW);
				delay(50);
				digitalWrite(LED[2], LOW);
				delay(50);
				digitalWrite(LED[1], LOW);
				delay(50);
				digitalWrite(LED[0], LOW);
			}
			/*
			for (int i = accY; i < sizeof(LED); ++i)
			{
				if (i <= 4)
				{
					digitalWrite(LED[i+4], HIGH);
					digitalWrite(LED[i], LOW);
				}
				if (i >= 4)
				{
					digitalWrite(LED[i+4], LOW);
					digitalWrite(LED[i], HIGH);
				}
			}
			*/
		break;
		case 4:
			Serial.println("Case 4");
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
	delay(150);
}

void count()
{
	static unsigned long lastIntTime = 0;
	unsigned long intTime = millis();
	if(intTime - lastIntTime > 200) btnFlag = HIGH;
	lastIntTime = intTime;
}

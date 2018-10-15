// Core library - MCU-based
#if defined(__MSP430FR5739__) // FraunchPad only
#include "Energia.h"
#else // error
#error Platform not supported. FraunchPad only.
#endif

// Include application, user and local libraries
#include <Wire.h>
#include <Servo.h>
#include "Accelerometer.h"
#include "LiquidCrystal_I2C.h"

#define MAX_PROCESSES 4 				// Maximum number of processes
#define tempPin A1

volatile int btnFlag = LOW;

//Object instance
LiquidCrystal_I2C myLcd(16,2);	// LCD Display
Accelerometer myAcc;						// Accelerometer sensor 
Servo myServo;									// Servo Thingy 

int counter = 1;								// A counter for number of processes
int tempRead;										// Actual Temperature
float tempThreshold = 20.0;			// Temprature Threshold
float tempC;
float tempF;
int vRef = 3000;
int rDiv = 470000000;

int tempTable[15][2] = {
 // {-25, 1344300},
 // {-20,  998530},
 // {-15,  748670},
 // {-10,  566360},
 // { -5,  432120},
 // {  0,  332400},
  {  5,  257690},
  { 10,  201270},
  { 15,  158340},
  { 20,  125420},
  { 25,  100000},
  { 30,   80239},
  { 35,   64776},
  { 40,   52598},
  { 45,   42950},
  { 50,   35262},
  { 55,   29100},
  { 60,   24136},
  { 65,   20114},
  { 70,   16841},
  { 75,   14164}
};

void setup()
{
	pinMode(PUSH2, INPUT_PULLUP);						// Set push button2 as input with pull up resistor
	attachInterrupt(PUSH2, count, RISING);	// Interrupt is fired whenever button is pressed

	// Initialize attached objects
	Wire.begin();
	myLcd.init();
	myLcd.backlight();
	myAcc.begin();
	myServo.attach(22);
	Serial.begin(9600);

	pinMode(NTC_ENABLE, OUTPUT);
  pinMode(tempPin, INPUT);
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
			tempRead = analogRead(tempPin);
			tempRead = (tempRead * vRef) / 1024;
			tempRead = (tempRead * rDiv) / (vRef - tempRead) / 1000;

			for (int i=1; i<15; i++) 
			{
				if (tempTable[i][1] < tempRead)
				{
					tempC = map(tempRead, tempTable[i-1][1], tempTable[i][1], 100*tempTable[i-1][0], 100*tempTable[i][0]);
					tempC /= 100;
					break;
				}
			}
			//tempC = (tempRead - 0.5) * 100.0;
			tempF = tempC * 9.0 / 5.0 + 32.0;
			myLcd.setCursor(0,0);
			myLcd.print("tempC ");
			myLcd.print(tempC);
			myLcd.setCursor(0,1);
			myLcd.print("tempF ");
			myLcd.print(tempF);

			while(tempC > tempThreshold)
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
			myLcd.setCursor(0,0);
			//myLcd.print("Case 3");
			myAcc.read();
			myAcc.lcdPrint(myLcd);
		break;
		case 4:
			myLcd.print("Case 4");
			myLcd.setCursor(0,0);
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

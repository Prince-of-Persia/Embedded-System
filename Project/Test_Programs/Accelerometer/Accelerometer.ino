#include "Accelerometer.h"
#include <Wire.h>
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C myLcd(16, 2); //Create a LCD instance
Accelerometer myACC;

void setup()
{
	Serial.begin(9600);
	Wire.begin();
	myACC.begin();    //Initialize acc
  myLcd.init();     //Initialize LCD
  myLcd.backlight();  //Turn ICD backlight on

}

void loop()
{
	myACC.read();
	myACC.lcdPrint(myLcd);

	delay(200);
}
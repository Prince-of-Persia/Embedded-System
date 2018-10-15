#include "FraunchPad_NTC.h"
#include <Servo.h>
#include "LiquidCrystal_I2C.h"
#include <Wire.h>

int32_t temperature;       // actual temp
int32_t threshold = 280  ;       // temperature threshold

LiquidCrystal_I2C myLcd(16, 2); //Create a LCD instance
NTC_FR myNTC;
Servo myServo;          //Create servo object to control a servo
int pos = 0;          //variable to store the servo position


void setup()
{
  Wire.begin();
  myLcd.init();     //Initialize LCD
  myLcd.backlight();  //Turn ICD backlight on
  myNTC.begin();    //Initialize Temp Sensor
  myServo.attach(22); //attaches the servo on pin 9 to the servo object, CHECK
  //Serial.begin(9600);
}

void loop()
{
	myNTC.get();
	myNTC.fahrenheitX10(temperature);
	myNTC.lcdPrint(temperature, myLcd, 'F');
	//Serial.print("F: ");
	//Serial.print(temperature);
	myNTC.celsiusX10(temperature);
	myNTC.lcdPrint(temperature, myLcd, 'C');
	//Serial.print("\tC: ");
	//Serial.print(temperature);
	//Serial.print("\n");
	if(temperature > threshold)
	{
	  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
	  {                                  // in steps of 1 degree 
	    myServo.write(pos);            // tell servo to go to position in variable 'pos' 
	    delay(15);                     // waits 15ms for the servo to reach the position 
	  } 
	  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
	  {                                
	    myServo.write(pos);            // tell servo to go to position in variable 'pos' 
	    delay(15);                     // waits 15ms for the servo to reach the position 
	  }
	}
	else
	{
		//myServo.write(0);
	}
	
  delay(50);
}
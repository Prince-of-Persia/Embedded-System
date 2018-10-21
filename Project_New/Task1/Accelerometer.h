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

// Core library - MCU-based
#if defined(__MSP430FR5739__) // FraunchPad specific
#include "Energia.h"
#else // error
#error Platform not defined
#endif

#ifndef Accelerometer_h
#define Accelerometer_h 

#include "LiquidCrystal_I2C.h"

class Accelerometer
{
public:
  Accelerometer();
  void begin();
  void read();
  void lcdPrint(LiquidCrystal_I2C lcd);
private:
  int8_t _Z, _Y, _X; 
  int8_t _vRef;
  int8_t _rDiv;
  void readAccZ();
  void readAccY();
  void readAccX();
};

#endif


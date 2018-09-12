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

#ifndef Task1_h
#define Task1_h

// Core library - MCU-based
#if defined(__MSP430FR5739__) // FraunchPad only
#include "Energia.h"
#else // error
#error Platform not supported. FraunchPad only.
#endif
//Other Core Libraries
#include <Wire.h>


// Include application, user and local libraries
#include "LiquidCrystal_I2C.h"
#include "Temp_NTC.h"
#include "Accelerometer.h"
/*
#include "led.h"
*/

#endif
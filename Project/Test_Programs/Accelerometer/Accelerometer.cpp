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
#include "Accelerometer.h"

Accelerometer::Accelerometer()
{
  pinMode(NTC_ENABLE, OUTPUT);
  pinMode(ACC_Z, INPUT);
  pinMode(ACC_Y, INPUT);
  pinMode(ACC_X, INPUT);
}

void Accelerometer::begin()
{
  digitalWrite(ACC_ENABLE, HIGH);
  _vRef = 3000;
  _rDiv = 470000000;
}

void Accelerometer::read()
{
  readAccX();
  readAccY();
  readAccZ();
}

void Accelerometer::readAccZ()
{
  _Z = analogRead(ACC_Z);
  _Z = (_Z * _vRef) / 1024;
  _Z = (_Z * _rDiv) / (_vRef - _Z) / 1000;
  Serial.print("Z: ");
  Serial.print(_Z);
  Serial.print('\t');
}

void Accelerometer::readAccY()
{
  _Y = analogRead(ACC_Y);
  _Y = (_Y * _vRef) / 1024;
  _Y = (_Y * _rDiv) / (_vRef - _Y) / 1000;
  Serial.print("Y: ");
  Serial.print(_Y);
  Serial.print('\t');
}

void Accelerometer::readAccX()
{
  _X = analogRead(ACC_X);
  _X = (_X * _vRef) / 1024;
  _X = (_X * _rDiv) / (_vRef - _X) / 1000;
  Serial.print("X: ");
  Serial.print(_X);
  Serial.print('\n');
}

void Accelerometer::lcdPrint(LiquidCrystal_I2C lcd)
{
  lcd.setCursor(0,0);
  lcd.print("X: ");
  lcd.print(_X);
  lcd.print(" Y: ");
  lcd.print(_Y);
  lcd.setCursor(0,1);
  lcd.print("Z: ");
  lcd.print(_Z);
}

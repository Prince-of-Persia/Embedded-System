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
#define ACC_Z A4
#define ACC_Y A5
#define ACC_X A6


accelerometer::accelerometer()
{
    pinMode(NTC_ENABLE, OUTPUT);
    pinMode(ACC_Z, INPUT);
    pinMode(ACC_Y, INPUT);
    pinMode(ACC_X, INPUT);
}

void accelerometer::begin()
{
    digitalWrite(NTC_ENABLE, HIGH);
    _vRef = 3000;
    _eDiv = 470000000;
}

void accelerometer::get()
{
    readAccZ();
    readAccY();
    readAccX();
}

void accelerometer::readAccZ()
{
    _Z = analogRead(ACC_Z);
    _Z = (_Z * _vRef) / 1024;
    _Z = (_Z * _rDiv) / (_vRef - _Z) / 1000;
}

void accelerometer::readAccY()
{
    _Y = analogRead(ACC_Y);
    _Y = (_Y * _vRef) / 1024;
    _Y = (_Y * _rDiv) / (_vRef - _Y) / 1000;
}

void accelerometer::readAccX()
{
    _X = analogRead(ACC_X);
    _X = (_X * _vRef) / 1024;
    _X = (_X * _rDiv) / (_vRef - _X) / 1000;
}

void accelerometer::lcdPrint(LiquidCrystal_I2C lcd)
{
    lcd.setCursor(0,0);
    lcd.print("X: ");
    lcd.print(_X);
}

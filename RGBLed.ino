#include "RGBLed.h"

RGBLed::RGBLed(uint8_t pinRed, uint8_t, uint8_t pinGreen, uint8_t pinBlue)
{
    this->pinColor[Red] = pinRed;
    this->pinColor[Green] = pinGreen;
    this->pinColor[Blue] = pinBlue;
}
void RGBLed::On(Color color)
{
    for (int i = 0; i < 3; i++)
        if (color == i)

            pinMode(pinColor[i], HIGH);
        else
            pinMode(pinColor[i], LOW);
}
void RGBLed::Off()
{
    for (int i = 0; i < 3; i++)
        pinMode(pinColor[i], LOW); 
}
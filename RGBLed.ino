#include "RGBLed.h"

RGBLed::RGBLed(uint8_t pinRed, uint8_t pinGreen, uint8_t pinBlue)
{
    this->pinsColor[Red] = pinRed;
    this->pinsColor[Green] = pinGreen;
    this->pinsColor[Blue] = pinBlue;

    for (int i = 0; i < 3; i++)
        pinMode(pinsColor[i], OUTPUT);
}
void RGBLed::On(int color)
{
    for (int i = 0; i < 3; i++)
        if (color == i)

            digitalWrite(pinsColor[i], HIGH);
        else
            digitalWrite(pinsColor[i], LOW);
}
void RGBLed::Off()
{
    for (int i = 0; i < 3; i++)
        digitalWrite(pinsColor[i], LOW);
}
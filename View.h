#ifndef View_h
#define View_h

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h>

class View
{
public:
    View();
    void Message(String message);
    void MessageLCD(String message1);
    void MessageLCD(String message1, String message2);
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
    enum RGBLED
    {
        Red,
        Green,
        Blue
    };
    void RGBled(int color);
private:
    WidgetTerminal terminal = WidgetTerminal(V0);
};
#endif
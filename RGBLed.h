#ifndef RGBLed_h
#define RGBLed_h
class RGBLed
{
    enum Color
    {
        Red,
        Green,
        Blue
    };
public:
    RGBLed(uint8_t pinRed, uint8_t, uint8_t pinGreen, uint8_t pinBlue);
    void On(Color);
    void Off();
private:
    uint8_t pinColor[3];
};
#endif
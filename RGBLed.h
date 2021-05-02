#ifndef RGBLed_h
#define RGBLed_h
enum Color
{
    Red,
    Green,
    Blue
};
class RGBLed
{
public:
    // Initialize the RGB-LED that defining its color pins
    RGBLed(uint8_t pinRed, uint8_t pinGreen, uint8_t pinBlue);
    void On(int color); // Turn of the RGB-LED
    void Off(); // Turn on the RGB-LED with a given specific color
private:
    uint8_t pinsColor[3]; // Store the RGB-LED pinsColor
};
#endif
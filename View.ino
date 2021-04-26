#include "View.h"

View::View()
{
	lcd.init();
	lcd.backlight();
	lcd.autoscroll();
}
void View::Message(String message)
{
	Serial.println(message);
	terminal.println(message);
	terminal.flush();
}
void View::MessageLCD(String message)
{
	lcd.println(message);
}

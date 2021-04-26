#include "View.h"

View::View()
{
	lcd.init();
	lcd.backlight();
}
void View::Message(String message)
{
	Serial.println(message);
	terminal.println(message);
	terminal.flush();
}
void View::MessageLCD(String message)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(message);
}
void View::MessageLCD(String message1, String message2)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(message1);
	lcd.setCursor(0, 1);
	lcd.print(message2);
}

#include "View.h"

View::View()
{
	lcd.init();
	lcd.backlight();
	terminal.clear();
	terminal.flush();
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
void View::RGBled(int color)
{
	switch (color)
	{
	case Red:
		digitalWrite(D8, HIGH);
		digitalWrite(D7, LOW);
		digitalWrite(D6, LOW);
		break;
	case Green:
		digitalWrite(D8, LOW);
		digitalWrite(D7, HIGH);
		digitalWrite(D6, LOW);
		break;
	case Blue:
		digitalWrite(D8, LOW);
		digitalWrite(D7, LOW);
		digitalWrite(D6, HIGH);
		break;

	default:
		break;
	}
}

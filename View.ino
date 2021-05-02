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
void View::UpdateAuthPanel(int authNums[])
{
	Blynk.setProperty(AuthenticatingPanelPin, "labels", "Auth Nums: ", authNums[0], authNums[1], authNums[2]);
	Blynk.virtualWrite(AuthenticatingPanelPin, 0);
}
void View::ResetAuthPanel()
{
	Blynk.setProperty(AuthenticatingPanelPin, "labels", "No need Authentication");
	Blynk.virtualWrite(AuthenticatingPanelPin, 0);
}
void View::UpdateLockState(String value)
{
	Blynk.virtualWrite(LockStateValuePin, value);
}
void View::BtnControlForUnlock()
{
	Blynk.setProperty(BtnControlPin, "offLabel", "Unlock");
	Blynk.setProperty(BtnControlPin, "onLabel", "Unlocking");
	Blynk.setProperty(BtnControlPin, "onBackColor", "#FFFF00");
	Blynk.setProperty(BtnControlPin, "offBackColor", "#FF0000");
	Blynk.virtualWrite(BtnControlPin, 0);
}
void View::BtnControlForLock()
{
	Blynk.setProperty(BtnControlPin, "offLabel", "Lock");
	Blynk.setProperty(BtnControlPin, "onLabel", "Locking");
	Blynk.setProperty(BtnControlPin, "onBackColor", "#FFFF00");
	Blynk.setProperty(BtnControlPin, "offBackColor", "#00FF00");
	Blynk.virtualWrite(BtnControlPin, 0);
}

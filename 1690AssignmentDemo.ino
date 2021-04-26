#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "SecureLock.h"
#include "View.h"

//char auth[] = "TwCg6uFlHUNnz-yRJLxW-tfUWfP9Bclc";
char auth[] = "iE7NulbKfx6ZgO4gBgAS4T5ZYjGcA1Ot";
char ssid[] = "HostpotTP";
char pass[] = "12345678";

SecureLock lock;
View view;

WidgetTerminal terminal(V0);

void setup()
{
	Serial.begin(9600);

	Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 137, 1), 8080);

	lock = SecureLock();
	view = View();

	terminal.clear();
	view.Message("Starting... Done!");

	Blynk.virtualWrite(V1, 0);
}

void loop()
{
	Blynk.run();
}

BLYNK_WRITE(V1)
{
	// read button state
	int btnState = param.asInt();

	// If button is pushed
	if (btnState == 1)
	{
		switch (lock.State())
		{
		case Locked:
			break;
		case Unlocked:
			break;
		case Authenticated:
			break;
		}
		if (lock.State() == Locked)
		{
			// If authorizing sucess
			if (lock.Authenticate() == true)
			{
				view.Message("Authenticated successful!");
				view.MessageLCD("Authenticated!");
				// Unlocking
				if (lock.Unlock() == true)
				{
					view.Message("The lock is unlocked.");
					view.MessageLCD("The lock is unlocked.");
				}
				else
				{
					view.Message("Unlooking is failed");
					view.Message("Problems: Unknown");
				}
			}
			else
			{
				view.Message("Authenticated failed!");
				view.Message("Cannot unlocking the lock.");
			}
		}
		else if (lock.State() == Unlocked)
		{
			if (lock.Lock() == true)
			{
				view.Message("Locking is successful!");
				view.Message("The lock is locked.");
			}
		}
		Blynk.virtualWrite(V1, 0);
	}
	switch (lock.State())
	{
	case Locked:
		Blynk.setProperty(V1, "offLabel", "Unlock");
		Blynk.setProperty(V1, "onLabel", "Unlocking");
		Blynk.setProperty(V1, "onBackColor", "#FFFF00");
		Blynk.setProperty(V1, "offBackColor", "#FF0000");
		break;
	case Unlocked:
		Blynk.setProperty(V1, "offLabel", "Lock");
		Blynk.setProperty(V1, "onLabel", "Locking");
		Blynk.setProperty(V1, "onBackColor", "#FFFF00");
		Blynk.setProperty(V1, "offBackColor", "#00FF00");
		break;
	default:
		Blynk.setProperty(V1, "offLabel", "NaN");
		Blynk.setProperty(V1, "onLabel", "NaN");
		Blynk.setProperty(V1, "onBackColor", "#FFFF00");
		Blynk.setProperty(V1, "offBackColor", "#808080");
	}
}
#include <Arduino.h>
#line 1 "e:\\wsArduino\\1690AssignmentDemo\\1690AssignmentDemo.ino"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include "SecureLock.h"

//char auth[] = "TwCg6uFlHUNnz-yRJLxW-tfUWfP9Bclc";
char auth[] = "iE7NulbKfx6ZgO4gBgAS4T5ZYjGcA1Ot";
char ssid[] = "HostpotTP";
char pass[] = "12345678";

class View
{
public:
	View()
	{
	}
	void Message(String message)
	{
		Serial.println(message);
		terminal.println(message);
	}

private:
	WidgetTerminal terminal = WidgetTerminal(V0);
};

SecureLock lock;
View view;

WidgetTerminal terminal(V0);

#line 34 "e:\\wsArduino\\1690AssignmentDemo\\1690AssignmentDemo.ino"
void setup();
#line 43 "e:\\wsArduino\\1690AssignmentDemo\\1690AssignmentDemo.ino"
void loop();
#line 48 "e:\\wsArduino\\1690AssignmentDemo\\1690AssignmentDemo.ino"
void BlynkWidgetWrite1(BlynkReq __attribute__((__unused__)) &request, const BlynkParam __attribute__((__unused__)) &param);
#line 34 "e:\\wsArduino\\1690AssignmentDemo\\1690AssignmentDemo.ino"
void setup()
{
	Serial.begin(9600);
	Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 137, 1), 8080);

	lock = SecureLock();
	view = View();
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
		// If button is locked
		if (lock.State() == Locked)
		{
			// If authorizing sucess
			if (lock.Authenticate() == true)
			{
				view.Message("Authenticated successfully!");
				// Unlocking
				if (lock.Lock() == true)
				{
					view.Message("Unlooking is successful! The lock is unlocked.");
				}
				else
				{
					view.Message("Unlooking is failed because of unknown reason.");
				}
			}
			else
			{
				view.Message("Authenticated failed! Cannot unlocking the lock.");
			}
		}
		if (lock.State() == Unlocked)
		{
			if (lock.Unlock() == true)
			{
				view.Message("Locking is successful! The lock is locked.");
			}
		}
		Blynk.virtualWrite(V1, 0);
	}
	else
		switch (lock.State())
		{
		case Locked:
			Blynk.setProperty(V1, "offLable", "Unlock");
			Blynk.setProperty(V1, "onLable", "Unlocking");
			break;
		case Unlocked:
			Blynk.setProperty(V1, "offLable", "Lock");
			Blynk.setProperty(V1, "onLable", "Locking");
			break;
		default:
			Blynk.setProperty(V1, "offLable", "NaN");
			Blynk.setProperty(V1, "onLable", "NaN");
		}
}

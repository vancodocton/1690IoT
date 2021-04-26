#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include "SecureLock.h"

char auth[] = "iE7NulbKfx6ZgO4gBgAS4T5ZYjGcA1Ot";
char ssid[] = "HostpotTP";
char pass[] = "12345678";

SecureLock lock;

void setup()
{
	Serial.begin(9600);

	pinMode(D6, OUTPUT);
	pinMode(D8, OUTPUT);
	pinMode(D7, OUTPUT);	

	Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 137, 1), 8080);

	lock = SecureLock();
}

void loop()
{
	Blynk.run();

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
	}
	Blynk.virtualWrite(V3, lock.State());
}

BLYNK_WRITE(V1)
{
	// read button state
	int btnState = param.asInt();

	if (btnState == 1)
	{
		switch (lock.State())
		{
		case Locked:
			lock.InitAuthNums();
			break;
		case Unlocked:
			lock.Lock();
			Blynk.virtualWrite(V1, 0);
			break;
		}
		return;
	}
}

BLYNK_WRITE(V2)
{
	if (param.asInt() == 1)
	{
		Blynk.virtualWrite(V2, 0);
		return;
	}
	if (lock.State() == Authenticating)
	{
		int authKey = param.asInt() - 2;

		if (lock.Authenticate(authKey) == true)
		{
			lock.Unlock();
		}

		Blynk.setProperty(V2, "labels", "No need Authentication");
		Blynk.virtualWrite(V1, 0);
	}
	else
	{
		Blynk.virtualWrite(V2, 0);
	}
}
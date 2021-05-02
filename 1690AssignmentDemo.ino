#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include "SecureLock.h"
#include "View.h"
#include "Authentication.h"

char auth[] = "iE7NulbKfx6ZgO4gBgAS4T5ZYjGcA1Ot";
char ssid[] = "HostpotTP";
char pass[] = "12345678";

SecureLock lock;
View view;
Authentication lockAuth;

void setup()
{
	Serial.begin(9600);

	Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 137, 1), 8080);

	lock = SecureLock();
	view = View();
	lockAuth = Authentication();

	lock.Lock();
	view.BtnControlForUnlock();
	view.ResetAuthPanel();
}
BLYNK_CONNECTED()
{
	Blynk.syncAll();
}
void loop()
{
	Blynk.run();
}

BLYNK_WRITE(BtnControlPin)
{
	// read btnControl state
	int btnState = param.asInt();

	// if btnControl is pressed
	if (btnState == 1)
	{
		// perform based on the secure-lock's state
		switch (lock.State())
		{
			// Unlocking if the secure-lock is locked
		case LockState::Locked:
			view.Message("Unloking the lock");
			view.MessageLCD("Unlocking");

			// Starting Authenticate if authorized person is standing in front of the secure-lock
			lockAuth.Initialize();

			view.Message("Authenticating");
			view.UpdateAuthPanel(lockAuth.AuthNums);
			view.MessageLCD("Auth number:", lockAuth.AuthKey);
			break;
			// Locking if the secure-lock is unlocked
		case LockState::Unlocked:
			view.Message("Locking the lock");
			view.MessageLCD("Locking");

			lock.Lock();
			view.BtnControlForUnlock();

			view.Message("The secure-lock is locked");
			view.MessageLCD("Locked");
			break;
		}
		return;
	}
}

BLYNK_WRITE(AuthenticatingPanelPin)
{
	if (param.asInt() == 1)
	{
		Blynk.virtualWrite(AuthenticatingPanelPin, 0);
		return;
	}

	if (lockAuth.State() == AuthState::Authenticating)
	{
		int authKeyIndex = param.asInt() - 2;

		lockAuth.Authenticate(authKeyIndex);

		if (lockAuth.State() == AuthState::Success)
		{
			view.Message("Authentication success");
			view.MessageLCD("Auth success");

			lock.Unlock();
			view.BtnControlForLock();
			view.Message("The secure-lock is unlocked");
			view.MessageLCD("Unlocked");
		}
		else if (lockAuth.State() == AuthState::Failed)
		{
			view.Message("Authentication failed");
			view.MessageLCD("Auth failed", "Cannot unlock");
		}

		lockAuth.Finish();
		view.ResetAuthPanel();
	}
}
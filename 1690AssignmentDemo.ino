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
	view.Message("The secure-lock is locked");
	view.MessageLCD("Locked");
}
BLYNK_CONNECTED()
{
	Blynk.syncAll();
}
void loop()
{
	Blynk.run();
}
// Run if the controlling-button is pressed by the user
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

			// Starting to authenticate if authorized person is standing in front of the secure-lock
			lockAuth.Initialize();

			view.Message("Authenticating");
			view.UpdateAuthPanel(lockAuth.AuthNums);
			view.MessageLCD("Auth number:", lockAuth.AuthKey);
			// The authentication process will be continuing if the user chooses the truth auth number
			// that is displayed on the 16x2 LCD in the set of three number of the authenticating- panel
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
// Run if the user had chosen the auth number in the set of three number of the authenticating-panel
BLYNK_WRITE(AuthenticatingPanelPin)
{
	// If the option one that is used to show the status of the panel, ignore it
	if (param.asInt() == 1)
	{
		Blynk.virtualWrite(AuthenticatingPanelPin, 0);
		return;
	}
	// If the user choose auth number
	if (lockAuth.State() == AuthState::Authenticating)
	{
		// Read the auth number index
		int authKeyIndex = param.asInt() - 2;

		// Authenticate by the user-selected auth num
		lockAuth.Authenticate(authKeyIndex);

		if (lockAuth.State() == AuthState::Success) // check authentication status
		{
			// unlock the secure-lock if succees
			view.Message("Authentication success");
			view.MessageLCD("Auth success");

			lock.Unlock();
			view.BtnControlForLock();
			view.Message("The secure-lock is unlocked");
			view.MessageLCD("Unlocked");
		}
		else if (lockAuth.State() == AuthState::Failed)
		{
			// prompt messagse for failed authentication
			view.Message("Authentication failed");
			view.MessageLCD("Auth failed", "Cannot unlock");
		}
		//Finish authentication and reset Authenticating-panel
		lockAuth.Finish();
		view.ResetAuthPanel();
	}
}
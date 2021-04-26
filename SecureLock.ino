#include <Arduino.h>

#include "SecureLock.h"
#include <BlynkSimpleEsp8266.h>

SecureLock::SecureLock()
{
    servo = Servo();
    servo.attach(D0);
    Serial.println("The lock is initialized");
    Lock();
    Blynk.virtualWrite(V1, 0);
    Blynk.setProperty(V2, "labels", "NaN");
    Blynk.virtualWrite(V2, 0);
}
bool SecureLock::Lock()
{
    Serial.println("Locking");
    servo.write(0);
    state = Locked;
    return true;
}
bool SecureLock::Unlock()
{
    AuthKey = -1;
    AuthNum = -1;
    Serial.println("Unlocking");
    servo.write(90);
    state = Unlocked;
    return true;
}
bool SecureLock::Authenticate(int authKey)
{
    Serial.println("Authenticating");

    if (authKey == AuthKey)
    {
        state = Authenticated;
        return true;
    }
    else
    {
        state = Locked;
        return false;
    }
}
int SecureLock::State()
{
    return state;
}
void SecureLock::InitAuthNums()
{
    state = Authenticating;

    int AuthNums[3];

    AuthNums[0] = random(11, 100);
    for (int i = 1; i < 3; i++)
    {
        int tmp = random(11, 100);
        if (tmp != AuthNums[i - 1])
        {
            AuthNums[i] = tmp;
        }
    }
    AuthKey = random(LONG_MAX) % 3;
    AuthNum = AuthNums[AuthKey];

    Blynk.virtualWrite(V2, 1);
    Blynk.setProperty(V2, "labels", "Auth Nums: ", AuthNums[0], AuthNums[1], AuthNums[2]);
}
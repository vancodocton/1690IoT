#include <Arduino.h>

#include "SecureLock.h"
#include <Blynk.h>

SecureLock::SecureLock()
{
    state = Locked;
    Serial.println("The lock is initialized");
}
bool SecureLock::Lock()
{
    Serial.println("Locking");
    state = Locked;
    return true;
}
bool SecureLock::Unlock()
{
    Serial.println("Unlocking");
    state = Unlocked;
    return true;
}
bool SecureLock::Authenticate()
{
    Serial.println("Authenticating");
    state = Authenticated;
    return true;
}
int SecureLock::State()
{
    return state;
}
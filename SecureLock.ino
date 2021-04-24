#include <Arduino.h>

#include "SecureLock.h"
#include <Blynk.h>

SecureLock::SecureLock()
{
    state = Locked;
}
bool SecureLock::Lock()
{
    Serial.println("Locking");
    return true;
}
bool SecureLock::Unlock()
{
    Serial.println("Unlocking");
    return true;
}
bool SecureLock::Authenticate()
{
    Serial.println("Authorizing");
    return true;
}
int SecureLock::State()
{
    return state;
}
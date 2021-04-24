#include <Arduino.h>

#include "SecureLock.h"
#include <Blynk.h>

class SecureLock
{
public:
    SecureLock()
    {
        state = Locked;
    }
    bool Lock()
    {
        Serial.println("Locking");
        return true;
    }
    bool Unlock()
    {
        Serial.println("Unlocking");
        return true;
    }
    bool Authenticate()
    {
        Serial.println("Authorizing");
        return true;
    }
    int LockState()
    {
        return state;
    }
private:
    int state;
};
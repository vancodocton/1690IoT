#include <Arduino.h>

#include "SecureLock.h"
#include <Blynk.h>



SecureLock::SecureLock()
{
    state = Locked;
    servo = Servo();
    servo.attach(D0);
    
    Serial.println("The lock is initialized");
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
    Serial.println("Unlocking");
    servo.write(90);
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

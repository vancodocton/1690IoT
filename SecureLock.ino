#include "SecureLock.h"

SecureLock::SecureLock()
{
    servo.attach(pinServo);
}
bool SecureLock::Lock()
{
    servo.write(0);
    
    state = Locked;
    led.On(Color::Red);

    return true;
}
bool SecureLock::Unlock()
{
    servo.write(90);

    state = Unlocked;
    led.On(Color::Green);

    return true;
}
int SecureLock::State()
{
    return state;
}
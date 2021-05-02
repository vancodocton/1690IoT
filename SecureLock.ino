#include <Arduino.h>

#include "SecureLock.h"
#include "View.h"
#include <BlynkSimpleEsp8266.h>

SecureLock::SecureLock()
{
    servo.attach(pinServo);
}
bool SecureLock::Lock()
{
    led.On(Color::Blue);

    servo.write(0);

    
    while (servo.read() != 0);

    state = Locked;
    led.On(Color::Red);

    return true;
}
bool SecureLock::Unlock()
{
    servo.write(90);

    //while (servo.read() != 90);

    state = Unlocked;
    led.On(Color::Green);

    return true;
}
int SecureLock::State()
{
    return state;
}
#ifndef SecureLock_h
#define SecureLock_h

#include <Servo.h>

#include "RGBLed.h"

#define pinRed D8
#define pinGreen D7
#define pinBlue D6
#define pinServo D4
class SecureLock
{
public:
    SecureLock();
    bool Lock();
    bool Unlock();
    int State();

private:
    int state;
    Servo servo = Servo();
    RGBLed led = RGBLed(pinRed, pinGreen, pinBlue);
};
enum LockState
{
    Locked,
    Unlocked,
    Unknown
};
#endif
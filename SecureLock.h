#ifndef SecureLock_h
#define SecureLock_h

#include<Servo.h>

class SecureLock
{
    
public:
    SecureLock();
    bool Lock();
    bool Unlock();
    bool Authenticate();
    int State();
private:
    int state;
    Servo servo;    
};
enum LockState
{
    Locked,
    Locking,
    Unlocked,
    Unlocking,
    Authenticated,
    Authenticating,
};
#endif
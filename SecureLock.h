#ifndef SecureLock_h
#define SecureLock_h

#include<Servo.h>

#include "View.h"

class SecureLock
{    
public:
    SecureLock();
    bool Lock();
    bool Unlock();
    bool Authenticate(int authKey);
    int State();
    void InitAuthNums();   
private:
    int AuthNum;
    int AuthKey;
    int state;
    Servo servo;
    View view;
};
enum LockState
{
    Locked,
    Unlocked,
    Authenticated,
    Authenticating,
};
#endif
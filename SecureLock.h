#ifndef SecureLock_h
#define SecureLock_h

#include<Servo.h>

class SecureLock
{    
public:
    SecureLock();
    bool Lock();
    bool Unlock();
    bool Authenticate(int authKey);
    int State();
    void InitAuthNums();   
    int AuthNum;
private:
    int AuthKey;
    int state;
    Servo servo; 
};
enum LockState
{
    Locked,
    Unlocked,
    Authenticated,
    Authenticating,
};
#endif
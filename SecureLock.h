#ifndef SecureLock_h
#define SecureLock_h

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
    
};
enum LockState
    {
        Locked,
        Unlocked,
        Authorized
    };
#endif
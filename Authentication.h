#ifndef Authentication_h
#define Authentication_h

class Authentication
{
public:
    Authentication();
    int State();
    void Initialize();
    bool Authenticate(int authNumIndex);
    void Finish();
    int AuthNums[3];
    String AuthKey;
private:
    int authKeyIndex;
    int state;
};
enum AuthState
{
    NoNeed,
    Authenticating,
    Success,
    Failed,
};
#endif
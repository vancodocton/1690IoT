#include "Authentication.h"

Authentication::Authentication()
{
    state = AuthState::NoNeed;
    
}
int Authentication::State()
{
    return state;
}
void Authentication::Initialize()
{
    state = AuthState::Authenticating;

    AuthNums[0] = random(11, 100);

    for (int i = 1; i < 3; i++)
    {
        AuthNums[i] = (AuthNums[i - 1] + random(11, 100)) % 100;
    }

    authKeyIndex = random(100) % 3;
    AuthKey = (String) AuthNums[authKeyIndex];
}
bool Authentication::Authenticate(int index)
{
    if (authKeyIndex == index)
    {
        state = AuthState::Success;
        return true;
    }
    else
    {
        state = AuthState::Failed;
        return false;
    }
}
void Authentication::Finish()
{
    state = AuthState::NoNeed;
    memset(AuthNums, 0, sizeof(AuthNums));
    AuthKey = "";
    authKeyIndex = 0;
}
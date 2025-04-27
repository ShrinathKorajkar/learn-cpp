#include "authenticator.h"

using namespace std;

bool SystemAuthenticator::authenticate(const string& username, const string& password) const
{
    return false;
}

bool SystemAuthenticator::usernameIsWellFormed(const string& username) const
{
    auto length = username.size();
    return length >= 3 && length <= 12;
}

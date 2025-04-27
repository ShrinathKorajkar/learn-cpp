#pragma once

#include <authenticator.h>
#include <string>

class UserSession
{
public:
    UserSession(const Authenticator& auth);

    void signIn(const std::string& username, const std::string& password);
    bool isSignedIn() const;

private:
    const Authenticator& m_auth;
    bool m_signedIn = false;
};

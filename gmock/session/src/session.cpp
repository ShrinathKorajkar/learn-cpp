#include "session.h"
#include <logger.h>

using namespace std;

UserSession::UserSession(const Authenticator& auth)
  : m_auth(auth)
{
}

void UserSession::signIn(const string& username, const string& password)
{
    m_auth.usernameIsWellFormed(username);
    m_signedIn = m_auth.authenticate(username, password);
    if (!m_signedIn) {
        logMessage("Failed to authenticate user " + username);
    }
}

bool UserSession::isSignedIn() const
{
    return m_signedIn;
}

#include "authenticator.h"
#include <gmock/gmock.h>

using namespace std;
using namespace testing;

TEST(AuthenticatorUsername, EmptyNameIsNotValid)
{
    SystemAuthenticator auth;
    EXPECT_THAT(auth.usernameIsWellFormed(""), Eq(false));
}

TEST(AuthenticatorUsername, ShortNameIsNotValid)
{
    SystemAuthenticator auth;
    EXPECT_THAT(auth.usernameIsWellFormed("ab"), Eq(false));
}

TEST(AuthenticatorUsername, ThreeLetterUsernameIsValid)
{
    SystemAuthenticator auth;
    EXPECT_THAT(auth.usernameIsWellFormed("abc"), Eq(true));
}

TEST(AuthenticatorUsername, LongUsernameIsNotValid)
{
    SystemAuthenticator auth;
    EXPECT_THAT(auth.usernameIsWellFormed("abcdefghijklm"), Eq(false));
}

TEST(AuthenticatorAuth, EmptyPasswordRejected)
{
    SystemAuthenticator auth;
    EXPECT_THAT(auth.authenticate("somebody", ""), Eq(false));
}

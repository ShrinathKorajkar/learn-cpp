#include <gmock/gmock.h>
#include <mockauthenticator.h>
#include <mocklogger.h>
#include <session.h>

using namespace std;
using namespace testing;

TEST(Session, CredentialsChecked)
{
    NiceMock<MockAuthenticator> auth;
    UserSession sess(auth);

    const string username = "bob";
    const string password = "secret";

    EXPECT_CALL(auth, authenticate(StrEq(username), StrEq(password)));

    sess.signIn(username, password);
}

TEST(Session, UsernameChecked)
{
    NiceMock<MockAuthenticator> auth;
    UserSession sess(auth);

    const string username = "bob";

    EXPECT_CALL(auth, usernameIsWellFormed(StrEq(username))).Times(AtLeast(1));

    sess.signIn(username, "secret");
}

TEST(Session, StatusUpdated)
{
    NiceMock<MockAuthenticator> auth;
    UserSession sess(auth);

    EXPECT_THAT(sess.isSignedIn(), Eq(false));
    sess.signIn("bob", "secret");
    EXPECT_THAT(sess.isSignedIn(), Eq(true));
}

TEST(Session, FailedAuthentication)
{
    NiceMock<MockAuthenticator> auth;
    UserSession sess(auth);

    // For this test we want authentication to fail
    ON_CALL(auth, authenticate(_, _)).WillByDefault(Return(false));

    sess.signIn("bob", "secret");
    EXPECT_THAT(sess.isSignedIn(), Eq(false));
}

class SessionAuthentication : public Test
{
public:
    SessionAuthentication()
      : m_sess(m_auth)
    {
    }

protected:
    NiceMock<MockLogger> m_logger;
    NiceMock<MockAuthenticator> m_auth;
    UserSession m_sess;
};

TEST_F(SessionAuthentication, FailedAuthentication)
{
    // For this test we want authentication to fail
    ON_CALL(m_auth, authenticate(_, _)).WillByDefault(Return(false));

    m_sess.signIn("bob", "secret");
    EXPECT_THAT(m_sess.isSignedIn(), Eq(false));
}

TEST_F(SessionAuthentication, FailedAuthLogMessage)
{
    // LogParser from ACME, Inc. watches for this string in the logs
    EXPECT_CALL(m_logger, logMessage(HasSubstr("Failed to authenticate")));

    ON_CALL(m_auth, authenticate(_, _)).WillByDefault(Return(false));
    m_sess.signIn("bob", "secret");
}
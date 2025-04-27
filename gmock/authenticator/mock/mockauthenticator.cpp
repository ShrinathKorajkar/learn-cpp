#include "mockauthenticator.h"

using namespace testing;

MockAuthenticator::MockAuthenticator()
{
    ON_CALL(*this, authenticate(_, _)).WillByDefault(Return(true));
    ON_CALL(*this, usernameIsWellFormed(_)).WillByDefault(Return(true));
}

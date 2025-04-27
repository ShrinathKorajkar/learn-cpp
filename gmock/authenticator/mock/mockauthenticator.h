#pragma once

#include "authenticator.h"
#include "gmock/gmock.h"

class MockAuthenticator : public Authenticator
{
public:
    MockAuthenticator();

    MOCK_CONST_METHOD2(authenticate, bool(const std::string&, const std::string&));
    MOCK_CONST_METHOD1(usernameIsWellFormed, bool(const std::string&));
};

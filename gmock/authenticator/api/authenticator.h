#pragma once

#include <string>

class Authenticator
{
public:
    Authenticator() = default;
    virtual ~Authenticator() = default;

    virtual bool authenticate(const std::string& username, const std::string& password) const = 0;
    virtual bool usernameIsWellFormed(const std::string& username) const = 0;
};

class SystemAuthenticator : public Authenticator
{
public:
    SystemAuthenticator() = default;
    ~SystemAuthenticator() override = default;

    bool authenticate(const std::string& username, const std::string& password) const override;
    bool usernameIsWellFormed(const std::string& username) const override;
};

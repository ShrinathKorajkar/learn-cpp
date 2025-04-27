#include <iostream>

// violation of SRP
/*
    dial, hangup -> connection mgmt
    send, recv   -> data mgmt

    Note: If application is not changing in ways that cause the the two responsibilities to
    change at different times, then there is no need to separate them.
*/
class Modem
{
    virtual void dial(std::string pno) = 0;
    virtual void hangup() = 0;
    virtual void send(char c) = 0;
    virtual char recv() = 0;

    virtual ~Modem() = default;
};

// follows SRP

class Dialer
{
public:
    virtual void dial(std::string pno) = 0;
    virtual void hangup() = 0;
    virtual ~Dialer() {}
};

class DataTransmitter
{
public:
    virtual void send(char c) = 0;
    virtual char recv() = 0;
    virtual ~DataTransmitter() {}
};

// Combined interface for modem functionality
class Modem : public Dialer, public DataTransmitter
{
public:
    virtual ~Modem() {}
};

class MyModem : public Modem
{
public:
    void dial(std::string pno) override {}
    void hangup() override {}
    void send(char c) override {}
    char recv() override { return '\0'; }
};

/*
    here if both methods are only used by one actor then it follows SRP else not
    as changing somethings required by cfo will impact something used by hr
*/
class Employee
{
    int getRegularHours() {}

public:
    int calculateSalary() // used by CFO
    {
        getRegularHours();
    }
    int calculateHours() // used by HR
    {
        getRegularHours();
    }
};

#include <gmock/gmock.h>

class MockLogger
{
public:
    MockLogger();
    ~MockLogger();

    MOCK_CONST_METHOD1(logMessage, void(const std::string&));
};
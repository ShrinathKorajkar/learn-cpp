#include "mocklogger.h"
#include "logger.h"
#include <stdexcept>

using namespace std;

namespace
{
MockLogger* g_mockLogger = nullptr;  // Raw pointer - this does not own the object
}  // end anonymous namespace

MockLogger::MockLogger()
{
    if (g_mockLogger) {
        throw runtime_error("Cannot have more than one MockLogger at the same time.");
    }
    g_mockLogger = this;
}
MockLogger::~MockLogger()
{
    g_mockLogger = nullptr;
}

void logMessage(const std::string& msg)
{
    if (g_mockLogger) {
        g_mockLogger->logMessage(msg);  // Full mock/fake powers
    }
    // else the best we can get is a stub.  Good enough for happy path if the test
    // didn't care to create a MockLogger.
}
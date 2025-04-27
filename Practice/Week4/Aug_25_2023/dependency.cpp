#include <iostream>
#include <string>

class Logger
{
public:
    void log(const std::string &message)
    {
        std::cout << "Logging: " << message << std::endl;
    }
};

class UserManager
{
private:
    Logger &logger; // Dependency: UserManager depends on Logger for logging
public:
    UserManager(Logger &_logger) : logger(_logger) {}

    void createUser(const std::string &username)
    {
        logger.log("User '" + username + "' created."); // Dependency: UserManager uses Logger for logging
        // Other user creation logic...
    }
};

int main()
{
    Logger logger;
    UserManager userManager(logger);

    userManager.createUser("john_doe");

    return 0;
}

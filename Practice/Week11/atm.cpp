#include <iostream>
#include <chrono>
#include <thread>
#include <stdexcept>

class AuthenticationException : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Invalid PIN";
    }
};

class ATM
{
public:
    void authenticate(const std::string &pin)
    {
        if (pin != "1234")
        {
            throw AuthenticationException();
        }
    }

    void authenticatePin()
    {
        const int maxAttempts = 3;
        const int waitTimeSeconds = 5;

        int attempts = 0;
        bool authenticated = false;

        while (attempts < maxAttempts && !authenticated)
        {
            std::string pin;
            std::cout << "Enter your PIN: ";
            std::cin >> pin;
            try
            {
                authenticate(pin);
                std::cout << "PIN authenticated successfully" << std::endl;
                authenticated = true;
            }
            catch (const AuthenticationException &e)
            {
                ++attempts;
                std::cout << "Authentication failed: " << e.what() << std::endl;
                if (attempts < maxAttempts)
                {
                    std::cout << "You have " << maxAttempts - attempts << " attempts left." << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(waitTimeSeconds));
                }
                else
                {
                    std::cout << "Your ATM card has been blocked. Please contact customer support." << std::endl;
                }
            }
        }
    }
};

int main()
{
    ATM atm;
    atm.authenticatePin();
    return 0;
}

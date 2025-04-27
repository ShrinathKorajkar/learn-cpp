#include <iostream>
#include <chrono>
#include <thread>
#include <string>

class ATM
{
public:
    bool authenticate(const std::string &pin)
    {
        return pin == "1234";
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

            authenticated = authenticate(pin);

            if (authenticated)
            {
                std::cout << "PIN authenticated successfully" << std::endl;
            }
            else
            {
                ++attempts;
                std::cout << "Authentication failed: Invalid PIN" << std::endl;
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

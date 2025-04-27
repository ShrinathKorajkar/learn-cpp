#include <iostream>

class CustomExcep : public std::exception
{
    const char *message;

public:
    CustomExcep(const char *message) : message(message) {}
    const char *what() const noexcept override
    {
        return message;
    }
};

int main()
{
    try
    {
        throw CustomExcep("Custom Error Occurred");
    }
    catch (const CustomExcep &e)
    {
        std::cerr << e.what() << std::endl;
        throw;
    }

    try
    {
        throw 42;
    }
    catch (int)
    {
        std::cerr << "Caught an integer exception." << std::endl;
    }

    return 0;
}
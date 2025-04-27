#include <iostream>
#include <stdexcept>

void innerFunction()
{
    try
    {
        throw std::runtime_error("Inner exception occurred");
    }
    catch (const std::exception &e)
    {
        std::throw_with_nested(std::logic_error("Nested exception in innerFunction"));
    }
}

void middleFunction()
{
    try
    {
        innerFunction();
    }
    catch (const std::exception &e)
    {
        std::throw_with_nested(std::runtime_error("Nested exception in middleFunction"));
    }
}

void outerFunction()
{
    try
    {
        middleFunction();
    }
    catch (const std::exception &e)
    {
        try
        {
            std::rethrow_if_nested(e);
        }
        catch (const std::exception &nested)
        {
            std::cerr << "Caught nested exception: " << nested.what() << std::endl;
        }

        std::cerr << "Caught original exception: " << e.what() << std::endl;
    }
}

int main()
{
    try
    {
        outerFunction();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
    }

    return 0;
}

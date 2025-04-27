#include <iostream>
#include <exception>

void riskyFunction()
{
    throw std::runtime_error("An error occurred in riskyFunction.");
}

void rethrowException(std::exception_ptr exPtr)
{
    try
    {
        std::rethrow_exception(exPtr);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Rethrown exception: " << e.what() << std::endl;
    }
}

int main()
{
    std::exception_ptr exPtr;

    try
    {
        riskyFunction();
    }
    catch (...)
    {
        exPtr = std::current_exception(); // Capture the exception
    }

    if (exPtr)
    {
        rethrowException(exPtr);
    }

    return 0;
}

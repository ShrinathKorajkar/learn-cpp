#include <iostream>

void customTerminateHandler()
{
    std::cerr << "Custom termination handler called." << std::endl;
    std::abort();
}

void customUnexpectedHandler()
{
    std::cerr << "Custom unexpected handler called." << std::endl;
    std::terminate();
}

int main()
{
    std::set_terminate(customTerminateHandler);
    std::set_unexpected(customUnexpectedHandler);

    std::terminate_handler currentTerminateHandler = std::get_terminate();
    std::cout << "Current termination handler: " << currentTerminateHandler << std::endl;

    std::unexpected_handler currentUnexpectedHandler = std::get_unexpected();
    std::cout << "Current unexpected handler: " << currentUnexpectedHandler << std::endl;

    currentUnexpectedHandler();
    currentTerminateHandler();

    throw 42; // This is an unexpected exception

    if (std::uncaught_exceptions())
    {
        std::cerr << "There are uncaught exceptions." << std::endl;
    }
    else
    {
        std::cerr << "No uncaught exceptions." << std::endl;
    }

    return 0;
}
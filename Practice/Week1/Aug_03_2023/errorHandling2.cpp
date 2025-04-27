#include <iostream>
#include <fstream>
// #define NDEBUG
#include <cassert>
using namespace std;
/*
    Exception :- runtime error
*/

// Exception Handling
void exception_handler()
{
    try
    {
        int x = -1;
        if (x < 0)
        {
            throw std::runtime_error("Invalid value: x should be non-negative");
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    catch (const std::logic_error &e)
    {
        // Handle logic_error
    }
    catch (const std::exception &e)
    {
        // Handle other exceptions
    }
}

// Assestion
void assertion()
{
    int x = -1;
    assert(x >= 0);
    static_assert(0 <= 1, "Assertion"); // compile time assertion
    cout << x << endl;
}

// custom error handling
void customLog(string message)
{
    cout << "Custom log : " << message << endl;
}

void customErrorHandling()
{
    cerr << "Error: Cannot divide by zero" << endl;
    clog << "This is a log message" << endl;

    ofstream logFile("logfile.txt");
    logFile << "This is a log message." << endl;
    logFile.close();

    customLog("This is a custom log message.");
}

int main()
{
    // exception_handler();
    // exception_handler();
    // assertion();

    return 0;
}
#include <iostream>
#include "bank.h"

int main()
{
    BankDatabase database;
    Bank bank(database);

    try
    {
        bank.serveRequest();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
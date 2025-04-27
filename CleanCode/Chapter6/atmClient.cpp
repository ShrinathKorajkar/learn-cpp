#include <iostream>
#include "atm.h"

int main()
{
    ATM atm;
    Card card(123456, {15, 12, 2024});
    double amountToWithdraw = 100;
    int pin = 1234;

    try
    {
        atm.start();
        atm.authenticateCard(&card, pin);
        atm.withdrawCash(amountToWithdraw);

        std::cout << "Withdraw Successful wait for cash" << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
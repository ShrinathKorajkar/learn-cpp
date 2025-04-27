#include <iostream>
#include <cstring>
#include <iomanip>
#include "bank.hpp"

void printError(const char *message)
{
    std::cout << "\n\n"
              << message
              << "\n\n";
    std::cin.clear();
    std::cin.ignore();
}

void performUserAction(Bank &bank, int &accountNumber)
{
    int choice{};
    double amount{};
    do
    {
        std::cout << "\nEnter User Action" << std::endl;
        std::cout << "1. Deposit     2. Withdraw     3. View Balance" << std::endl;
        std::cout << "4. Mini Statement     5. Bank Statement     6. Any Other to exit"
                  << std::endl;
        std::cin >> choice;
        if (std::cin.fail())
        {
            printError("INVALID INPUT!... Enter Numbers");
            continue;
        }
        switch (choice)
        {
        case 1:
            std::cout << "Enter Amount to Deposit : ";
            std::cin >> amount;
            bank.depositAmount(accountNumber, amount);
            break;
        case 2:
            std::cout << "Enter Amount to Withdraw : ";
            std::cin >> amount;
            bank.withdrawAmount(accountNumber, amount);
            break;
        case 3:
            bank.viewBalance(accountNumber);
            break;
        case 4:
            bank.miniStatement(accountNumber);
            break;
        case 5:
            bank.bankStatement(accountNumber);
            break;
        }

    } while (choice > 0 && choice < 6);
}

void performOperation(Bank &bank, const int &choice)
{
    std::string userName;
    int accountNumber{};
    switch (choice)
    {
    case 1:
        std::cout << "\nEnter User Name : ";
        std::cin >> userName;
        accountNumber = bank.createUser(userName);
        std::cout << "New User Created with Account Number : " << accountNumber << std::endl;
        break;
    case 2:
        bank.listAllUsers();
        break;
    case 3:
        std::cout << "Enter Account Number of User : ";
        std::cin >> accountNumber;
        if (bank.validateAccountNumber(accountNumber))
        {
            performUserAction(bank, accountNumber);
        }
        else
        {
            std::cout << "Invalid Account Number : " << std::endl;
        }
        break;
    case 4:
        break;
    default:
        std::cout << "Invalid Choice !.. Please Type 1, 2, 3, or 4";
    }
}

int main()
{
    Bank SBI;
    int choice;
    do
    {
        std::cout << "\nChoose the operation given below" << std::endl;
        std::cout << "1. Create User      2. List All Users     3. Select User     4. Exit\n:" << std::endl;
        std::cin >> choice;
        if (std::cin.fail())
        {
            printError("INVALID INPUT!... Enter Numbers");
            continue;
        }
        performOperation(SBI, choice);
    } while (choice != 4);
    return 0;
}
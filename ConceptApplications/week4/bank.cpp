#include <iostream>
#include <cstring>
#include <iomanip>
#include "bank.hpp"

void User::reallocateIfFull()
{
    if (transactionIndex >= transactionSize)
    {
        double *newTransactions = new double[static_cast<int>(transactionSize * 1.5)];
        std::memcpy(newTransactions, transactions, transactionSize * sizeof(double));
        transactionSize *= 1.5;
        delete[] transactions;
        transactions = newTransactions;
    }
}

void User::addInfo(std::string name, const int &accountNo)
{
    userName = name;
    accountNumber = accountNo;
}

void User::addAmount(const double &amount)
{
    balance += amount;
    transactions[transactionIndex++] = amount;
    reallocateIfFull();
    std::cout << "Deposit Successfull" << std::endl;
}

void User::removeAmount(const double &amount)
{
    if (balance > amount)
    {
        balance -= amount;
        transactions[transactionIndex++] = (-1 * amount);
        reallocateIfFull();
        std::cout << "Withdraw Successfull" << std::endl;
    }
    else
    {
        std::cout << "Insufficient Balance" << std::endl;
    }
}

void Bank::reallocateUsers()
{
    if (currentUserIndex >= totalUsers)
    {
        User *newUserList = new User[static_cast<int>(totalUsers * 1.5)];
        for (int i = 0; i < totalUsers; ++i)
        {
            newUserList[i] = userList[i];
        }
        totalUsers = static_cast<int>(totalUsers * 1.5);
        delete[] userList;
        userList = newUserList;
    }
}

void Bank::displayStatement(double *transactions, const int &start, const int &end)
{
    int sno = 1;
    std::cout << "Record No    Type \tAmount" << std::endl;
    for (int record = start; record < end; record++)
    {
        std::string type;
        double amount = transactions[record];
        if (transactions[record] < 0)
        {
            type = "Withdraw";
            amount *= -1;
        }
        else
        {
            type = "Deposit";
        }
        std::cout << std::setw(5) << sno++ << std::setw(14) << type << std::setw(10) << amount << std::endl;
    }
    std::cout << std::endl;
}

int Bank::createUser(std::string userName)
{
    userList[currentUserIndex++].addInfo(userName, accountNumberGenerator++);
    reallocateUsers();
    return accountNumberGenerator - 1;
}

void Bank::depositAmount(const int &accountNumber, const double &amount)
{
    userList[accountNumber - 1].addAmount(amount);
}

void Bank::withdrawAmount(const int &accountNumber, const double &amount)
{
    userList[accountNumber - 1].removeAmount(amount);
}

void Bank::viewBalance(const int &accountNumber)
{
    std::cout << "\nRemaining Balance : " << userList[accountNumber - 1].getBalance() << std::endl;
}

void Bank::miniStatement(const int &accountNumber)
{
    double *transactions = userList[accountNumber - 1].getTransactions();
    int transactionIndex = userList[accountNumber - 1].getTransactionIndex();
    std::cout << "\nMini Statement : " << std::endl;
    std::cout << transactionIndex << std::endl;
    int start = (transactionIndex - 10) < 0 ? 0 : (transactionIndex - 10);
    displayStatement(transactions, start, transactionIndex);
}

void Bank::bankStatement(const int &accountNumber)
{
    double *transactions = userList[accountNumber - 1].getTransactions();
    int transactionIndex = userList[accountNumber - 1].getTransactionIndex();
    std::cout << "\nBank Statement : " << std::endl;
    displayStatement(transactions, 0, transactionIndex);
}

void Bank::listAllUsers()
{
    std::cout << "\n***** List Of All Users ****** \n";
    std::cout << "Account Number     Name      Balance" << std::endl;
    for (int index = 0; index < currentUserIndex; index++)
    {
        User &user = userList[index];
        std::cout << std::setw(8) << user.getAccountNumber() << std::setw(14) << user.getName() << std::setw(11) << user.getBalance() << std::endl;
    }
}

int Bank::accountNumberGenerator = 1;

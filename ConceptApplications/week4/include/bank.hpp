#ifndef BANK_H
#define BANK_H
#include <iostream>

class User
{
    std::string userName;
    int accountNumber = 1;
    double balance = 0;
    double *transactions;
    int transactionSize = 2;
    int transactionIndex = 0;

    void reallocateIfFull();

public:
    User() : transactions(new double[transactionSize]){};

    void addInfo(std::string name, const int &accountNo);

    void addAmount(const double &amount);

    void removeAmount(const double &amount);

    double getBalance() { return balance; }

    double *getTransactions() { return transactions; }

    int getTransactionIndex() { return transactionIndex; }

    std::string getName() { return userName; }

    int getAccountNumber() { return accountNumber; }

    ~User() { delete[] transactions; }
};

class Bank
{
    static int accountNumberGenerator;
    int totalUsers = 2;
    int currentUserIndex = 0;
    User *userList;

    void reallocateUsers();

    void displayStatement(double *transactions, const int &start, const int &end);

public:
    Bank() : userList(new User[totalUsers]) {}

    int createUser(std::string userName);

    void depositAmount(const int &accountNumber, const double &amount);

    void withdrawAmount(const int &accountNumber, const double &amount);

    void viewBalance(const int &accountNumber);

    void miniStatement(const int &accountNumber);

    void bankStatement(const int &accountNumber);

    void listAllUsers();

    bool validateAccountNumber(const int &accountNumber) { return accountNumber > 0 && accountNumber <= currentUserIndex; }

    ~Bank() { delete[] userList; }
};

#endif // BANK_H

#include <iostream>

class BankAccount;

class BankManager
{

public:
    void resetBalance(BankAccount &account);
};

class BankAccount
{
private:
    double balance;
    long accountNumber;

    friend void BankManager::resetBalance(BankAccount &account);

public:
    BankAccount(double initialBalance, long accountNo)
        : balance(initialBalance), accountNumber(accountNo) {}

    double getBalance() const
    {
        return balance;
    }
};

void BankManager::resetBalance(BankAccount &account)
{
    account.balance = 0;
}

int main()
{
    BankAccount account(1000, 12345);
    BankManager manager;

    std::cout << "Initial Balance: " << account.getBalance() << std::endl;
    manager.resetBalance(account);
    std::cout << "Updated Balance: " << account.getBalance() << std::endl;

    return 0;
}

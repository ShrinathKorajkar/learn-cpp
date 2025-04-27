#include <iostream>
#include <vector>

using namespace std;

class Wallet;

class Money
{
private:
    int amount;

public:
    Money(int amount) : amount(amount) {}

    int getAmount() const
    {
        return amount;
    }

    // Violation 1: Method chaining
    Money &add(const Money &money)
    {
        amount += money.getAmount();
        return *this;
    }
};

class Wallet
{
private:
    Money money;

public:
    Wallet() : money(100) {}

    const Money &getMoney() const
    {
        return money;
    }

    // Violation 2: Making changes in multiple places
    // We decide to store Money as a vector
    vector<Money> moneyList;

    void addMoney(const Money &money)
    {
        moneyList.push_back(money);
    }

    // Violation 3: Making changes in multiple places
    // Changed the way Money is added
    void multiplyFirstMoney(int multiplier)
    {
        moneyList.front().add(Money(moneyList.front().getAmount() * multiplier));
    }
};

int main()
{
    Wallet wallet;
    Money money(50);

    // Violation 1: Method chaining
    wallet.getMoney().add(money);

    // Later, if we decide to change the implementation of Wallet
    // Violation 2: Making changes in multiple places
    // We decide to store Money as a vector
    wallet.addMoney(Money(30));

    // And later decide to change the way Money is added
    // Violation 3: Making changes in multiple places
    wallet.multiplyFirstMoney(2);

    // Now, if we change the Money class or how it is stored in Wallet,
    // this code will break in multiple places.
    return 0;
}

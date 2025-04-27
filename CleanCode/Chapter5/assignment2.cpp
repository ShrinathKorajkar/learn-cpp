#include <iostream>
#include <string>

class Wallet
{
private:
    float totalMoney = 0;

public:
    Wallet(const float &initialMoney = 0) : totalMoney(initialMoney) {}

    float getTotalMoney() const { return totalMoney; }

    void addMoney(float deposit)
    {
        totalMoney += deposit;
    }

    bool subtractMoney(float debit)
    {
        if (totalMoney >= debit)
        {
            totalMoney -= debit;
            return true;
        }
        return false;
    }
};

class Customer
{
private:
    std::string firstName;
    std::string lastName;
    Wallet myWallet;

public:
    Customer(const std::string &first, const std::string &last, const float &initialMoney = 0)
        : firstName(first), lastName(last), myWallet(initialMoney) {}

    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    float getTotalMoneyInWallet() const { return myWallet.getTotalMoney(); }

    // Operations
    void addMoneyToWallet(float deposit)
    {
        myWallet.addMoney(deposit);
    }

    bool makePayment(float amount)
    {
        return myWallet.subtractMoney(amount);
    }
};

int main()
{
    Customer myCustomer("John", "Doe", 100);

    double payment = 50.00;
    bool paymentSuccess = myCustomer.makePayment(payment);

    if (paymentSuccess)
    {
        std::cout << "Payment of ₹" << payment << " successful." << std::endl;
    }
    else
    {
        std::cout << "Insufficient funds in the wallet." << std::endl;
    }

    return 0;
}

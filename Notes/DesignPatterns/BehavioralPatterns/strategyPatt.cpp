/*
    Strategy Pattern:  ->  Defines a family of algorithms, encapsulates each one, and makes them interchangeable.
    Strategy lets the algorithm vary independently from clients that use it.
*/

#include <iostream>

// Strategy interface
class PaymentStrategy
{
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentStrategy() {}
};

// ConcreteStrategy 1: Credit Card Payment
class CreditCardPayment : public PaymentStrategy
{
public:
    CreditCardPayment(const std::string &cardNumber, const std::string &name)
        : cardNumber_(cardNumber), name_(name) {}

    void pay(int amount) override
    {
        std::cout << "Paid $" << amount << " using Credit Card: " << cardNumber_ << " (Name: " << name_ << ")" << std::endl;
    }

private:
    std::string cardNumber_;
    std::string name_;
};

// ConcreteStrategy 2: PayPal Payment
class PayPalPayment : public PaymentStrategy
{
public:
    PayPalPayment(const std::string &email)
        : email_(email) {}

    void pay(int amount) override
    {
        std::cout << "Paid $" << amount << " using PayPal: " << email_ << std::endl;
    }

private:
    std::string email_;
};

// Context
class ShoppingCart
{
public:
    void addItem(const std::string &item, int price)
    {
        total_ += price;
    }

    void checkout(PaymentStrategy *paymentStrategy)
    {
        paymentStrategy->pay(total_);
    }

private:
    int total_ = 0;
};

int main()
{
    // Create a shopping cart
    ShoppingCart cart;

    // Add items to the cart
    cart.addItem("Item 1", 50);
    cart.addItem("Item 2", 30);

    // Pay using a Credit Card
    PaymentStrategy *creditCard = new CreditCardPayment("1234-5678-9012-3456", "John Doe");
    cart.checkout(creditCard);

    // Pay using PayPal
    PaymentStrategy *paypal = new PayPalPayment("john.doe@example.com");
    cart.checkout(paypal);

    // Clean up resources
    delete creditCard;
    delete paypal;

    return 0;
}

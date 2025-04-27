#include <iostream>
#include <string>

class Product;
class OrderCalculator;

class Product
{
private:
    std::string name;
    double price;

public:
    Product(const std::string &name, double price) : name(name), price(price) {}
    double getPrice() const { return price; }
};

// OrderCalculator interface
class OrderCalculator
{
public:
    virtual double calculateTotal(const Product &product, int quantity, double discount) const = 0;
    virtual ~OrderCalculator() = default;
};

// BasicOrderCalculator class implementing OrderCalculator interface
class BasicOrderCalculator : public OrderCalculator
{
public:
    double calculateTotal(const Product &product, int quantity, double discount) const override
    {
        return (product.getPrice() * quantity) * (1 - discount);
    }
};

// Order class
class Order
{
private:
    const Product &product;
    int quantity;
    double discount;
    const OrderCalculator &calculator;

public:
    Order(const Product &product, int quantity, double discount, const OrderCalculator &calculator)
        : product(product), quantity(quantity), discount(discount), calculator(calculator) {}

    double getTotal() const
    {
        return calculator.calculateTotal(product, quantity, discount);
    }
};

// OrderProcessor class
class OrderProcessor
{
private:
    const OrderCalculator &calculator;

public:
    OrderProcessor(const OrderCalculator &calculator) : calculator(calculator) {}

    void processOrder(const Product &product, int quantity, double discount) const
    {
        Order order(product, quantity, discount, calculator);
        std::cout << "Order processed with total: $" << order.getTotal() << std::endl;
    }
};

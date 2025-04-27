#include <iostream>
#include <string>

class Product
{
private:
    std::string name;
    double price;

public:
    Product(const std::string &name, double price) : name(name), price(price) {}
    double getPrice() const { return price; }
};

class Order
{
private:
    Product product;
    int quantity;
    double discount; // New field

public:
    // Order(const Product &product, int quantity) : product(product), quantity(quantity) {}
    Order(const Product &product, int quantity, double discount) : product(product), quantity(quantity), discount(discount) {}

    // double getTotal() const
    // {
    //     return product.getPrice() * quantity;
    // }

    double getTotal() const
    {
        return (product.getPrice() * quantity) * (1 - discount); // Apply discount
    }
};

class OrderProcessor
{
public:
    void processOrder(const Product &product, int quantity)
    {
        double discount = calculateDiscount(product); // New logic to calculate discount
        Order order(product, quantity, discount);     // Update to include discount

        std::cout << "Order processed with total after discount: $" << order.getTotal() << std::endl;
    }

private:
    double calculateDiscount(const Product &product)
    {
        // New logic to calculate discount based on product attributes
        return 0.1; // Example discount value
    }
};

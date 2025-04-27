/*
    Decorator Pattern  ->  Attaches additional responsibilities to an object dynamically.
    Decorators provide a flexible alternative to subclassing for extending functionality.
*/

#include <iostream>
#include <string>

// Component interface (the base class for objects to be decorated)
class Coffee
{
public:
    virtual std::string getDescription() const = 0;
    virtual double cost() const = 0;
    virtual ~Coffee() {}
};

// Concrete Component (the base coffee)
class SimpleCoffee : public Coffee
{
public:
    std::string getDescription() const override { return "Simple Coffee"; }
    double cost() const override { return 2.0; }
};

// Decorator base class (abstract decorator)
class CoffeeDecorator : public Coffee
{
protected:
    Coffee *coffee_;

public:
    CoffeeDecorator(Coffee *coffee) : coffee_(coffee) {}

    std::string getDescription() const override { return coffee_->getDescription(); }
    double cost() const override { return coffee_->cost(); }
};

// Concrete Decorator (adds milk to coffee)
class MilkDecorator : public CoffeeDecorator
{
public:
    MilkDecorator(Coffee *coffee) : CoffeeDecorator(coffee) {}

    std::string getDescription() const override { return coffee_->getDescription() + ", Milk"; }
    double cost() const override { return coffee_->cost() + 1.0; }
};

// Concrete Decorator (adds sugar to coffee)
class SugarDecorator : public CoffeeDecorator
{
public:
    SugarDecorator(Coffee *coffee) : CoffeeDecorator(coffee) {}

    std::string getDescription() const override { return coffee_->getDescription() + ", Sugar"; }
    double cost() const override { return coffee_->cost() + 0.5; }
};

int main()
{
    Coffee *simpleCoffee = new SimpleCoffee();
    std::cout << "Simple Coffee - Description: " << simpleCoffee->getDescription()
              << ", Cost: $" << simpleCoffee->cost() << std::endl;

    Coffee *milkCoffee = new MilkDecorator(simpleCoffee);
    std::cout << "Milk Coffee - Description: " << milkCoffee->getDescription()
              << ", Cost: $" << milkCoffee->cost() << std::endl;

    Coffee *sugarMilkCoffee = new SugarDecorator(milkCoffee);
    std::cout << "Sugar Milk Coffee - Description: " << sugarMilkCoffee->getDescription()
              << ", Cost: $" << sugarMilkCoffee->cost() << std::endl;

    delete simpleCoffee;
    delete milkCoffee;
    delete sugarMilkCoffee;

    return 0;
}

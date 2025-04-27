#include <iostream>
#include <string>
#include <vector>

class Coffee
{
public:
    std::string type;
    int quantity;
    bool brewed;
    std::string customization;
    double price;
};

class CoffeeShop
{
public:
    void attendCustomer();

    Coffee receiveCoffeeOrder();
    Coffee prepareCoffee(const Coffee &order);
    void serveCoffee(const Coffee &coffee);
    void generateBill(const Coffee &coffee);
    void acceptPayment();

    std::string inquireCoffeeType();
    int inquireQuantity();
    std::string inquireSugarPreference();
    void gatherMaterials(Coffee &coffee);
    void grindCoffeeBeans(Coffee &coffee);
    void prepareCoffeeMaker(Coffee &coffee);
    void brewCoffee(Coffee &coffee);
    void waitForBrewingToComplete();
    void pourCoffeeIntoMug(Coffee &coffee);
    void customizeCoffee(Coffee &coffee);
    void listEachItemOrdered(const Coffee &coffee);
    double calculateTotal(const Coffee &coffee);
    double applyTaxes(double total);
    double addServiceCharge(double total);
    void printBill(double total);
    void listPaymentOptions();
    void processPayment();
    void provideReceipt();

    void gatherCoffeeBeans();
    void gatherCoffeeMaker();
    void collectWater();
    void gatherCoffeeMug();
    void gatherCoffeeGrinder();
    void measureCoffeeBeans();
    void setCoffeeGrinder();
    void startGrinding();
    void insertFilter();
    void addCoffeeGrounds();
    void addWater();
    void addMilk();
    void addSugar();
};

void CoffeeShop::attendCustomer()
{
    Coffee order = receiveCoffeeOrder();
    Coffee coffee = prepareCoffee(order);
    serveCoffee(coffee);
    generateBill(coffee);
    acceptPayment();
}

Coffee CoffeeShop::receiveCoffeeOrder()
{
    Coffee order;
    order.type = inquireCoffeeType();
    order.quantity = inquireQuantity();
    order.customization = inquireSugarPreference();
    return order;
}

std::string CoffeeShop::inquireCoffeeType()
{
    return "Latte";
}

int CoffeeShop::inquireQuantity()
{
    return 1;
}

std::string CoffeeShop::inquireSugarPreference()
{
    return "No sugar";
}

Coffee CoffeeShop::prepareCoffee(const Coffee &order)
{
    Coffee coffee;
    coffee.type = order.type;
    coffee.quantity = order.quantity;

    gatherMaterials(coffee);
    grindCoffeeBeans(coffee);
    prepareCoffeeMaker(coffee);
    brewCoffee(coffee);
    waitForBrewingToComplete();
    pourCoffeeIntoMug(coffee);
    customizeCoffee(coffee);
    return coffee;
}

void CoffeeShop::gatherMaterials(Coffee &coffee)
{
    gatherCoffeeBeans();
    gatherCoffeeMaker();
    collectWater();
    gatherCoffeeMug();
    gatherCoffeeGrinder();
}

void CoffeeShop::gatherCoffeeBeans() {}

void CoffeeShop::gatherCoffeeMaker() {}

void CoffeeShop::collectWater() {}

void CoffeeShop::gatherCoffeeMug() {}

void CoffeeShop::gatherCoffeeGrinder() {}

void CoffeeShop::grindCoffeeBeans(Coffee &coffee)
{
    measureCoffeeBeans();
    setCoffeeGrinder();
    startGrinding();
}

void CoffeeShop::measureCoffeeBeans() {}

void CoffeeShop::setCoffeeGrinder() {}

void CoffeeShop::startGrinding() {}

void CoffeeShop::prepareCoffeeMaker(Coffee &coffee)
{
    insertFilter();
    addCoffeeGrounds();
    addWater();
}

void CoffeeShop::insertFilter() {}

void CoffeeShop::addCoffeeGrounds() {}

void CoffeeShop::addWater() {}

void CoffeeShop::brewCoffee(Coffee &coffee)
{
    prepareCoffeeMaker(coffee);
}

void CoffeeShop::waitForBrewingToComplete() {}

void CoffeeShop::pourCoffeeIntoMug(Coffee &coffee) {}

void CoffeeShop::customizeCoffee(Coffee &coffee)
{
    addMilk();
    addSugar();
}

void CoffeeShop::addMilk() {}

void CoffeeShop::addSugar() {}

void CoffeeShop::serveCoffee(const Coffee &coffee)
{
    std::cout << "Enjoy your " << coffee.type << "!" << std::endl;
}

void CoffeeShop::generateBill(const Coffee &coffee)
{
    listEachItemOrdered(coffee);
    double total = calculateTotal(coffee);
    total = applyTaxes(total);
    total = addServiceCharge(total);
    printBill(total);
}

void CoffeeShop::listEachItemOrdered(const Coffee &coffee)
{
    std::cout << "Item: " << coffee.quantity << " " << coffee.type << " - $" << coffee.price << " each" << std::endl;
}

double CoffeeShop::calculateTotal(const Coffee &coffee)
{
    return coffee.quantity * coffee.price;
}

double CoffeeShop::applyTaxes(double total)
{
    return total * 1.1;
}

double CoffeeShop::addServiceCharge(double total)
{
    return total * 1.05;
}

void CoffeeShop::printBill(double total)
{
    std::cout << "Total: $" << total << std::endl;
}

void CoffeeShop::acceptPayment()
{
    listPaymentOptions();
    processPayment();
    provideReceipt();
}

void CoffeeShop::listPaymentOptions()
{
    std::cout << "Payment Options: Cash, Credit Card, Mobile Payment" << std::endl;
}

void CoffeeShop::processPayment()
{
    std::cout << "Processing payment" << std::endl;
}

void CoffeeShop::provideReceipt()
{
    std::cout << "Receipt provided. Thank you for your purchase!" << std::endl;
}

int main()
{
    CoffeeShop coffeeShop;
    coffeeShop.attendCustomer();
    return 0;
}

class CoffeeShop
{
public:
    void serveCustomer()
    {
        takeOrder();
        prepareCoffee();
        serveCoffee();
        generateBill();
        acceptPayment();
    }

private:
    void takeOrder() {}

    void prepareCoffee()
    {
        grindCoffeeBeans();
        brewCoffee();
        customizeCoffee();
    }

    void grindCoffeeBeans() {}
    void brewCoffee() {}
    void customizeCoffee() {}

    void serveCoffee() {}

    void generateBill()
    {
        listItemsOrdered();
        calculateTotal();
        applyTaxes();
        addServiceCharge();
        printBill();
    }

    void listItemsOrdered() {}
    void calculateTotal() {}
    void applyTaxes() {}
    void addServiceCharge() {}
    void printBill() {}

    void acceptPayment()
    {
        listPaymentOptions();
        processPayment();
        provideReceipt();
    }

    void listPaymentOptions() {}
    void processPayment() {}
    void provideReceipt() {}
};

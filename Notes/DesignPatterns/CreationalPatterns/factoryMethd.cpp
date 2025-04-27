#include <iostream>
#include <string>

/*
    Factory Method Pattern  ->  Defines an interface for creating an object but allows subclasses to alter the type
    of objects that will be created. It provides an interface for creating an object but leaves the choice of its
    type to the subclasses.
*/

class Product
{
public:
    virtual std::string getDescription() = 0;
    virtual ~Product() {}
};

class ProductA : public Product
{
public:
    std::string getDescription() override { return "Product A"; }
    ~ProductA() override { std::cout << "Destructor of ProductA" << std::endl; }
};

class ProductB : public Product
{
public:
    std::string getDescription() override { return "Product B"; }
    ~ProductB() override { std::cout << "Destructor of ProductB" << std::endl; }
};

class Creator
{
public:
    virtual Product *createProduct() = 0;
    void someOperation()
    {
        Product *product = createProduct();
        std::cout << "Created " << product->getDescription() << std::endl;
        delete product;
    }

    virtual ~Creator() {}
};

class CreatorA : public Creator
{
public:
    Product *createProduct() override { return new ProductA(); }
    ~CreatorA() override { std::cout << "Destructor of CreatorA" << std::endl; }
};

class CreatorB : public Creator
{
public:
    Product *createProduct() override { return new ProductB(); }
    ~CreatorB() override { std::cout << "Destructor of CreatorB" << std::endl; }
};

int main()
{
    Creator *creatorA = new CreatorA();
    Creator *creatorB = new CreatorB();

    creatorA->someOperation();
    creatorB->someOperation();

    delete creatorA;
    delete creatorB;

    return 0;
}

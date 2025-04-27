#include <iostream>

class Base
{
    int a;

public:
    Base() { std::cout << "Constr Base" << std::endl; }
    void name()
    {
        std::cout << "Base" << std::endl;
    }
    void hello(int a)
    {
        std::cout << "hello" << a << std::endl;
    }
    void hello()
    {
        std::cout << "Hello" << std::endl;
    }
    // virtual ~Base() {}
    virtual ~Base() { std::cout << "Destr Base" << std::endl; }
};

class Derived : public Base
{
    int b;

public:
    Derived() { std::cout << "Constr Derived" << std::endl; }
    void name()
    {
        std::cout << "Derived" << std::endl;
    }
    void hello() // cannot access hello(int) also
    {
        std::cout << "Hello" << std::endl;
    }
    virtual ~Derived() { std::cout << "Destr Derived" << std::endl; }
};

int main()
{
    // static binding

    Derived der;
    Derived &der1 = der;
    Derived *der2 = &der;
    der.name();
    der1.name();
    der2->name();

    Base b;
    Base &b1 = b;
    Base *b2 = &b;
    b.name();
    b1.name();
    b2->name();

    Base base = der; // object slicings
    Base &base1 = der;
    Base *base2 = &der;
    base.name();
    base1.name();
    base2->name();

    Base *derived = new Derived();
    derived->name();

    // Derived *derived2 = dynamic_cast<Derived *>(derived);
    // derived2->name();
    delete derived;

    return 0;
}
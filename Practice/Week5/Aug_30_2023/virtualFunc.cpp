#include <iostream>

class Base
{
    int a{};

public:
    Base() { std::cout << "Base Constr" << std::endl; }
    void hello(int a) { std::cout << "hello a" << a << std::endl; }
    virtual void hello() { std::cout << "Hello base" << std::endl; }
    virtual ~Base() { std::cout << "Base Destructor" << std::endl; }
};

class Derived : public Base
{
    int b{};

public:
    Derived() { std::cout << "Derived Constr" << std::endl; }
    void hello() override { std::cout << "Hello der" << std::endl; }
    ~Derived() { std::cout << "Derived Destructor" << std::endl; }
};

int main()
{
    Derived d;
    Base b2 = d;
    b2.hello();
    // Derived der;
    // Base *ptr = &der;
    Base *ptr = new Derived();
    ptr->hello();
    ptr->hello(1);
    delete ptr;

    std::cout << sizeof(Derived) << std::endl;
    std::cout << sizeof(Base) << std::endl;

    Base b;
    int *p = (int *)&b;
    std::cout << sizeof(*p) << std::endl;

    return 0;
}
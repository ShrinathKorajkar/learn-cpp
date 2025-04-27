#include <iostream>
class Base
{
    int a;

public:
    Base() { std::cout << "Base C" << std::endl; }
    virtual void hello() = 0;
    virtual ~Base() { std::cout << "Base D" << std::endl; }
};

class Derived : public Base
{
    void hello()
    {
        std::cout << "Hello " << std::endl;
    }

public:
    Derived() { std::cout << "Derived C" << std::endl; }
    ~Derived() { std::cout << "Derived D" << std::endl; }
};

class Derived2 : public Base
{
};

int main()
{
    // Derived d;
    Base *b = new Derived();
    // Base b;
    b->hello();
    std::cout << sizeof(Base) << std::endl;
    std::cout << sizeof(Derived) << std::endl;
    delete b;

    // Derived2 d;

    return 0;
}
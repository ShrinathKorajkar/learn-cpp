#include <iostream>

class Base
{
public:
    int a; // padding before this for virtual ptr
    virtual void base()
    {
        std::cout << "Base" << std::endl;
    }
    virtual ~Base() {}
};

class Derived : public Base
{
public:
    int b;
    int c;
    void derived()
    {
        std::cout << "Derived" << std::endl;
    }
    virtual ~Derived() {}
};

int main()
{
    Derived derived;
    Base *basePtr = &derived; // Upcast
    basePtr->base();
    // basePtr->derived(); // error
    std::cout << sizeof(*basePtr) << std::endl;
    std::cout << sizeof(derived) << std::endl;

    Base base;
    // Derived *ptr = &base;// will fail to alloc dynamic as size is low
    Derived *derPtr = dynamic_cast<Derived *>(basePtr); // downcast , virtual func req
    std::cout << sizeof(base) << std::endl;
    std::cout << sizeof(*derPtr) << std::endl;
    if (derPtr)
    {
        derPtr->derived();
    }
    else
    {
        std::cout << "Dynamic cast failed" << std::endl;
    }
    return 0;
}
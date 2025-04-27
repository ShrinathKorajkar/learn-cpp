#include <iostream>

class Base
{
public:
    int baseValue;

    Base(int value) : baseValue(value) { std::cout << "Base const" << std::endl; }

    void display()
    {
        std::cout << "Base value: " << baseValue << std::endl;
    }
    ~Base() { std::cout << "Base Dest" << std::endl; }
};

class Derived : public Base
{
public:
    int derivedValue;

    Derived(int baseVal, int derivedVal) : Base(baseVal), derivedValue(derivedVal) { std::cout << "Deriv const" << std::endl; }

    void display()
    {
        std::cout << "Derived value: " << derivedValue << std::endl;
    }
    ~Derived() { std::cout << "Derived Dest" << std::endl; }
};

int main()
{
    Derived derivedObj(10, 20);
    Base baseObj = derivedObj; // Object slicing

    derivedObj.display();
    baseObj.display();

    return 0;
}

#include <iostream>

class A
{

public:
    int a;
    A(int a) : a(a) { std::cout << "A Constructor" << std::endl; }
    void hello()
    {
        std::cout << "Hello" << std::endl;
    }
    virtual ~A() { std::cout << "A Destructor" << std::endl; }
    // this will create vptr which is taken as 8 byte data
};

class B : virtual public A
{
public:
    B(int a) : A(a) { std::cout << "B Constructor" << std::endl; }
    virtual ~B() { std::cout << "B Destructor" << std::endl; }
};

class C : virtual public A
{
public:
    C(int a) : A(a) { std::cout << "C Constructor" << std::endl; }
    virtual ~C() { std::cout << "C Destructor" << std::endl; }
};

class D : public B, public C
{
public:
    D(int a) : A(a), B(a), C(a) { std::cout << "D Constructor" << std::endl; }
    virtual ~D() { std::cout << "D Destructor" << std::endl; }
};
int main()
{
    std::cout << sizeof(A) << std::endl;
    std::cout << sizeof(B) << std::endl;
    std::cout << sizeof(C) << std::endl;
    std::cout << sizeof(D) << std::endl;

    D d(1);
    return 0;
}
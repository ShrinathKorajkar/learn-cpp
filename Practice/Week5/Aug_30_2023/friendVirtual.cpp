#include <iostream>
class B;
class A
{
    int a;

public:
    virtual void virtualFunction(B &bb);
};

class B
{
    int b{};

public:
    friend void A::virtualFunction(B &bb);
    friend class C;
};

class C : public A
{
public:
    void virtualFunction(B &bb) override
    {
        std::cout << "B" << bb.b << std::endl;
    }
};

void A::virtualFunction(B &bb)
{
    std::cout << "virtual function" << bb.b << std::endl;
}

int main()
{
    A aObj;
    B bObj;

    aObj.virtualFunction(bObj);

    return 0;
}

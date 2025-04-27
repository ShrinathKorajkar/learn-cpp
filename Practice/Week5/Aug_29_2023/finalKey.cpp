#include <iostream>

class NonInherit final
{
};

class NoOverride
{
public:
    virtual void someFunc() final
    {
        std::cout << "Cannot be Overriden" << std::endl;
    }
};

int main()
{

    return 0;
}
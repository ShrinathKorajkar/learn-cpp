#include <iostream>

class MyClass
{
public:
    int publicMember = 0;

protected:
    int protectedMember = 1;

private:
    int privateMember = 2;
};

int main()
{
    MyClass obj;

    // All members are stored in memory the same way, reason for pointer providing no safety
    // stored in order of declaration
    int *ptr = &obj.publicMember;
    std::cout << *ptr++ << std::endl;
    std::cout << *ptr++ << std::endl;
    std::cout << *ptr << std::endl;

    return 0;
}

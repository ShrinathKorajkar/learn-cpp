#include <iostream>
#include <cstring>
class Copy
{
    int a;
    int *b;

public:
    Copy(int val) : a(val), b(new int(5)) {}
    Copy(Copy *other)
    {
        std::cout << "user constructor\n";
        this->a = (other)->a;
        this->b = (other)->b;
    }
    Copy(const Copy &other)
    {
        std::cout << "copy constructor\n";
        this->a = (other).a;
        this->b = (other).b;
    }
    void printVal()
    {
        std::cout << b << std::endl;
    }
};

class Copy2
{
    int a;
    char *b;

public:
    Copy2(int val) : a(val), b(new char)
    {
        // strcpy(b, "val");
    }
    Copy2(Copy2 *other)
    {
        this->a = (other)->a;
        this->b = (other)->b;
    }
    void printVal()
    {
        std::cout << (int *)b << std::endl;
    }
};

int main()
{
    Copy obj(10);
    Copy obj2 = obj;
    Copy obj3(&obj2);

    obj.printVal();
    obj2.printVal();
    obj3.printVal();

    Copy2 obje(10);
    Copy2 obje2 = obje;
    Copy2 obje3(&obje2);

    obje.printVal();
    obje2.printVal();
    obje3.printVal();

    return 0;
}
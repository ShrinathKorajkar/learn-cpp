#include <iostream>

class myClass
{
private:
    int e;

public:
    myClass(int a, int b, int c) : a(a), b(b), c(c) {}
    int a, b, c;
    void f() { g(); };
    void g() {}

private:
    int d;
};

int main()
{
    myClass obj{1, 2, 3};
    std::cout << obj.a << std::endl;
    return 0;
}
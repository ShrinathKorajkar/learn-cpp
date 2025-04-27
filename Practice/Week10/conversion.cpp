#include <iostream>

int main()
{
    typedef struct
    {
        int a;
        int b;
    } hello;

    hello *a;
    int c = 20;
    a = (hello *)&c;
    a->a = 2;
    // a->b = 3;                               // gives SEGV
    std::cout << a->a << a->b << std::endl; // doesn't gives SEGV
    return 0;
}
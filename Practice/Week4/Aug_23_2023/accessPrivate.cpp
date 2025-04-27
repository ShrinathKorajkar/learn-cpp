#include <iostream>
class ShriClass
{
    int x, y;

public:
    ShriClass(int xx)
    {
        x = ++xx;
    }
    ~ShriClass()
    {
        std::cout << x - 1 << " ";
    }
    void Display()
    {
        std::cout << --x + 1 << " ";
    }
};
int main()
{
    ShriClass objBix(5);
    objBix.Display();
    int *p = (int *)&objBix;
    *p = 40;
    objBix.Display();
    return 0;
}
#include <iostream>

class Shape
{

public:
    double area(int radius)
    {
        return 3.14 * radius * radius;
    }

    double area(int length, int breadth)
    {
        return length * breadth;
    }
};

int main()
{
    Shape circle, rectangle;
    std::cout << circle.area(5) << std::endl;
    std::cout << rectangle.area(5) << std::endl;

    return 0;
}
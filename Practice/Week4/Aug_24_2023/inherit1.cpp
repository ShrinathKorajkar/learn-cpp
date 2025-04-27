#include <iostream>

class Shape
{
private:
    int priv;

protected:
    int protect;

public:
    int radius{};
    // void area();
    Shape(int r) : protect(--r), radius(r) {}
};

class Circle : private Shape
{
    int protect;

public:
    using Shape::radius; // cannot have another radius
    Circle(int r) : Shape(--r), protect(++r) {}
    void area()
    {
        std::cout << Shape::protect << std::endl;
        std::cout << protect << std::endl;
        std::cout << radius << std::endl;
        std::cout << "Perimeter : " << 2 * 3.14 * this->radius << std::endl;
    }
};

int main()
{
    Circle c(5);
    c.area();
    return 0;
}
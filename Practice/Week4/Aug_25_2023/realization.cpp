#include <iostream>
#include <string>

// Abstract class representing a shape
class Shape
{
public:
    virtual void draw() const = 0; // Pure virtual function
};

// Concrete implementation of the Shape interface for a Circle
class Circle : public Shape
{
public:
    void draw() const override
    {
        std::cout << "Drawing a circle" << std::endl;
    }
};

// Concrete implementation of the Shape interface for a Square
class Square : public Shape
{
public:
    void draw() const override
    {
        std::cout << "Drawing a square" << std::endl;
    }
};

int main()
{
    Circle circle;
    Square square;

    circle.draw(); // Output: Drawing a circle
    square.draw(); // Output: Drawing a square

    return 0;
}

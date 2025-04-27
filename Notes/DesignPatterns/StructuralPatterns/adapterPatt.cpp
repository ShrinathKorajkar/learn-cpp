/*
    Structural design patterns are a category of design patterns in software engineering that deal
    with the composition of classes or objects to form larger structures and provide new functionalities.

    Adapter Pattern  ->  Allows the interface of an existing class to be used as another interface.
    It is often used to make existing classes work with others without modifying their source code.
*/

#include <iostream>
#include <string>

// Legacy class with an incompatible interface
class LegacyRectangle
{
    int x1_, y1_, x2_, y2_;

public:
    LegacyRectangle(int x1, int y1, int x2, int y2) : x1_(x1), y1_(y1), x2_(x2), y2_(y2) {}

    void oldDraw()
    {
        std::cout << "LegacyRectangle: oldDraw method called." << std::endl;
        std::cout << "Coordinates: (" << x1_ << ", " << y1_ << ") - (" << x2_ << ", " << y2_ << ")" << std::endl;
    }
};

// Target interface expected by the client code
class Rectangle
{
public:
    virtual void draw() = 0;
    virtual ~Rectangle() {}
};

// Adapter class that adapts LegacyRectangle to the Rectangle interface
class LegacyRectangleAdapter : public Rectangle
{
    LegacyRectangle legacyRectangle_;

public:
    LegacyRectangleAdapter(int x1, int y1, int x2, int y2) : legacyRectangle_(x1, y1, x2, y2) {}

    void draw() override
    {
        std::cout << "LegacyRectangleAdapter: draw method called." << std::endl;
        legacyRectangle_.oldDraw();
    }
};

int main()
{
    Rectangle *rect = new LegacyRectangleAdapter(10, 20, 30, 40);
    rect->draw();

    delete rect;

    return 0;
}

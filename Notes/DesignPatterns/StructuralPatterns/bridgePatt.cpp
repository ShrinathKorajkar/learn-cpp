/*
    Bridge Pattern  ->  The Bridge Pattern separates an object's abstraction from its implementation.
    It allows you to change or extend both independently. This pattern is helpful when you want to avoid
    a permanent binding between an abstraction and its implementation.
*/

#include <iostream>

// Implementor interface (the bridge)
class DrawingAPI
{
public:
    virtual void drawCircle(double x, double y, double radius) = 0;
    virtual ~DrawingAPI() {}
};

// Concrete Implementor 1
class DrawingAPI1 : public DrawingAPI
{
public:
    void drawCircle(double x, double y, double radius) override
    {
        std::cout << "API1.circle at (" << x << ", " << y << ") with radius " << radius << std::endl;
    }
};

// Concrete Implementor 2
class DrawingAPI2 : public DrawingAPI
{
public:
    void drawCircle(double x, double y, double radius) override
    {
        std::cout << "API2.circle at (" << x << ", " << y << ") with radius " << radius << std::endl;
    }
};

// Abstraction
class Shape
{
public:
    Shape(DrawingAPI *drawingAPI) : drawingAPI_(drawingAPI) {}

    virtual void draw() = 0;
    virtual ~Shape() {}

protected:
    DrawingAPI *drawingAPI_;
};

// Refined Abstraction
class Circle : public Shape
{
public:
    Circle(double x, double y, double radius, DrawingAPI *drawingAPI)
        : Shape(drawingAPI), x_(x), y_(y), radius_(radius) {}

    void draw() override
    {
        drawingAPI_->drawCircle(x_, y_, radius_);
    }

private:
    double x_, y_, radius_;
};

int main()
{
    DrawingAPI *api1 = new DrawingAPI1();
    DrawingAPI *api2 = new DrawingAPI2();

    Shape *circle1 = new Circle(1, 2, 3, api1);
    Shape *circle2 = new Circle(4, 5, 6, api2);

    circle1->draw();
    circle2->draw();

    delete api1;
    delete api2;
    delete circle1;
    delete circle2;

    return 0;
}

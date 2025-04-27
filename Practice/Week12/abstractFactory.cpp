#include <iostream>

// Abstract Product
class Shape
{
public:
    virtual void draw() const = 0;
    virtual ~Shape() {}
};

// Concrete Products
class Circle : public Shape
{
public:
    void draw() const override
    {
        std::cout << "Drawing Circle\n";
    }
};

class Square : public Shape
{
public:
    void draw() const override
    {
        std::cout << "Drawing Square\n";
    }
};

// Abstract Factory
class ShapeFactory
{
public:
    virtual Circle *createCircle() const = 0;
    virtual Square *createSquare() const = 0;
    virtual ~ShapeFactory() {}
};

// Concrete Factories
class SimpleShapeFactory : public ShapeFactory
{
public:
    Circle *createCircle() const override
    {
        return new Circle();
    }

    Square *createSquare() const override
    {
        return new Square();
    }
};

// Client Code
void drawShapes(const ShapeFactory &factory)
{
    Circle *circle = factory.createCircle();
    Square *square = factory.createSquare();

    circle->draw();
    square->draw();

    delete circle;
    delete square;
}

int main()
{
    // Using the Abstract Factory pattern
    SimpleShapeFactory simpleFactory;
    drawShapes(simpleFactory);

    return 0;
}

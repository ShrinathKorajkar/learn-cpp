#include <vector>

class Shape
{
public:
    virtual void Draw() const = 0;
};

class Square : public Shape
{
public:
    virtual void Draw() const;
};

class Circle : public Shape
{
public:
    virtual void Draw() const;
};

void DrawAllShapes(std::vector<Shape *> &list)
{
    std::vector<Shape *>::iterator i;
    for (i = list.begin(); i != list.end(); i++)
        (*i)->Draw();
}
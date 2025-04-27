#include <iostream>

class Point
{
public:
    int x, y;

    void display()
    {
        std::cout << "x: " << x << ", y: " << y << std::endl;
    }
    Point(int x, int y) : x(x), y(y) {}
};

Point operator+(const Point &p1, const Point &p2)
{
    return Point(p1.x + p2.x, p1.y + p2.y);
}

Point operator++(Point &p)
{
    ++p.x;
    ++p.y;
    return p;
}

Point operator++(Point &p, int)
{
    Point temp = p;
    ++p.x;
    ++p.y;
    return temp;
}

std::ostream &operator<<(std::ostream &is, Point &p)
{
    is << p.x << p.y;
    return is;
}

int main()
{
    Point p1(1, 2);
    Point p2(3, 4);
    Point result = p1 + p2;
    result.display();

    ++result;
    result++;
    result.display();

    std::cout << result << std::endl;
    return 0;
}

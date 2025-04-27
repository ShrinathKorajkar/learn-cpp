#include <iostream>

class Distance2
{
    int feet;

public:
    explicit Distance2(int f) : feet(f) {}
    void printFeet()
    {
        std::cout << "Distance2: " << feet << std::endl;
    }
};

class Distance
{
    int feet;

public:
    Distance(int f) : feet(f) {}

    void printFeet()
    {
        std::cout << "Distance: " << feet << std::endl;
    }

    operator double() const // conversion operator
    {
        return feet;
    }
};

class Resource
{
    int *data;

public:
    Resource(int size) : data(new int[size]) {}
    Resource(Resource &&other) noexcept : data(other.data) // move constructor
    {
        other.data = nullptr;
    }

    Resource &operator=(const Resource &other) // copy assignment operator
    {
        if (this != &other)
        {
            data = other.data; // shallow copy
        }
        return *this;
    }

    Resource &operator=(Resource &&other) // move assignment operator
    {
        if (this != &other)
        {
            delete[] data;
            data = other.data;
            other.data = NULL;
        }
        return *this;
    }

    ~Resource()
    {
        delete[] data;
    }

    void printValue() const
    {
        std::cout << "Resource : " << data << std::endl;
    }
};

int main()
{
    Distance d1 = 10; // implicit conversion
    d1.printFeet();

    // Distance2 d2 = 10; // Error
    Distance d3(10);
    d3.printFeet();

    double distanceInCm = d1 * 30.48; // conversion op
    std::cout << "Distance in Cm : " << distanceInCm << std::endl;

    Resource res1(10);
    Resource res2 = std::move(res1); // move const
    Resource res3(10);
    res3 = std::move(res3); // move assignment operator
    return 0;
}
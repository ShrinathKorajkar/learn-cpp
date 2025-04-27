#include <iostream>
/*
    explicitly deleting the copy constructor, copy assignment operator
    delete and default can be used for all constructors, destructors and operators
*/
class NoCopy
{
    int value;

public:
    NoCopy(int v) : value(v) {}
    NoCopy() = default;                         // Ask compiler to Generate the default constructor
    NoCopy(const NoCopy &) = delete;            // Prevent copying
    NoCopy &operator=(const NoCopy &) = delete; // Prevent copy assignment
    NoCopy(double value) = delete;              // Prevent conversion from double
    NoCopy(int value, double factor) = delete;  // Prevent this combination of constructor
};

int main()
{
    NoCopy obj;
    return 0;
}
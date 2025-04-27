#include <iostream>

class Resource
{
public:
    Resource() { std::cout << "Resource acquired." << std::endl; }
    ~Resource() { std::cout << "Resource released." << std::endl; }
};

int main()
{
    try
    {
        Resource res; // Resource acquired
        throw std::runtime_error("Exception thrown.");
    }
    catch (const std::exception &e)
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    return 0;
}

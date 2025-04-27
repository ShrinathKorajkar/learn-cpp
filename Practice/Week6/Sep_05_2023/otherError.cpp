#include <iostream>
#include <fstream>

void badAlloc()
{
    int *arr = new int[10000000000];
    delete arr;
}

void iosBaseFailure()
{
    std::ifstream file("nonexistent_file.txt");
    if (!file.is_open())
    {
        throw std::ios_base::failure("Failed to open file: nonexistent_file.txt");
    }
    file.close();
}
int main()
{
    try
    {
        badAlloc();
        iosBaseFailure();
    }
    catch (const std::bad_alloc &e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (const std::ios_base::failure &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
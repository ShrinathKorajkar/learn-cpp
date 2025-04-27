#include <iostream>
using namespace std;
void function(char *str)
{
    if (*str == '\0')
    {
        return;
    }
    function(str++);
    // std::cout << *str;
}
int main()
{
    char ptr[] = "I am";
    // int* nptr = NULL;
    // ptr[0] = 'd';
    int size = sizeof(ptr) / sizeof(char);
    std::cout << size << "\n";
    function(ptr);
    // cout << ptr << "\n ";
    return 0;
}

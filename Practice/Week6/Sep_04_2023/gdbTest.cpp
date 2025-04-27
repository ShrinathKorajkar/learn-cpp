#include <iostream>

void func1()
{
    std::cout << "Inside func1" << std::endl;
    std::cout << "Inside func1" << std::endl;
    std::cout << "Inside func1" << std::endl;
}

void func2()
{
    std::cout << "Inside func2" << std::endl;
    std::cout << "Inside func2" << std::endl;
    std::cout << "Inside func2" << std::endl;
}

void greet(int a)
{
    int b = 0;
    while (b < 5)
    {
        std::cout << b++ << std::endl;
    }
    std::cout << a << std::endl;
    // abort();
}

int main()
{
    std::cout << "Starting the program" << std::endl;

    int x = 5;
    int y = 10;

    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;

    func1();

    x += 2;

    func2();

    y *= 3;

    std::cout << "Updated x = " << x << std::endl;
    std::cout << "Updated y = " << y << std::endl;

    std::cout << "hello" << std::endl;
    int a = 10;
    greet(a);

    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    std::string str = "hello";
    std::cout << arr[2] << std::endl;

    std::cout << "Finishing the program" << std::endl;
    return 0;
}

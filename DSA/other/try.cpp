#include <iostream>

void printWrong(int **arr)
{
    std::cout << "Trying arr[1][2] = " << arr[1][2] << "\n"; // 💣 UB
}

int main()
{
    int a[3][4] = {0};
    a[1][2] = 42;

    std::cout << "a[1][2] = " << a[1][2] << "\n";
    std::cout << "Casting to int** and accessing...\n";

    printWrong((int **)a); // ❌ Will print garbage or crash

    return 0;
}

#include <iostream>
#include <cstring>

struct Node
{
    void *data;
};

struct Point
{
    int x, y;
};

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int add(int x, int y)
{
    return x + y;
}

void modifyPointer(int **p, char **strPtr, std::string *strPtr2)
{
    *p = nullptr;
    *strPtr = "Hello World";
    *strPtr2 = "Hello World";
}

int main()
{
    int a = 2, b = 3;
    swap(&a, &b);
    std::cout << a << " " << b << std::endl;

    Point pt = {4, 5};
    Point *ptr = &pt;
    int coord = ptr->x;
    std::cout << coord << std::endl;

    int (*funcPtr)(int, int) = &add;
    int result = (*funcPtr)(6, 7);
    std::cout << result << std::endl;

    // Multiple indirection
    int *z = &a;
    int **y = &z;
    std::cout << **y << std::endl;

    int *x = new int;
    char *str = "hello";
    std::string str2 = "world";
    modifyPointer(&x, &str, &str2);
    std::cout << str << std::endl;
    std::cout << str2 << std::endl;

    // void pointer
    int value = 42;
    char cvalue = 'A';
    Node *node = new Node{&value};
    Node *node2 = new Node{&cvalue};

    delete x;
    return 0;
}
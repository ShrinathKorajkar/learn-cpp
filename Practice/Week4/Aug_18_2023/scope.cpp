#include <iostream>

/*
    x  of both obj1 and obj2  =>  memory block allocated for the objects.
    y  =>  data segment and is shared among all instances of the class.
    z  =>  read-only data segment.
    print()  =>  code segment.
    obj1  =>  automatic memory (stack)  =>  automatically deallocated when it goes out of scope.
    obj2  =>  dynamic memory (heap)  =>  explicitly deallocated using delete.
*/

class MyClass
{
public:
    int x;
    static int y;
    const int z = 5;

    void print()
    {
        std::cout << "x: " << x << ", y: " << y << ", z: " << z << std::endl;
    }
};

int MyClass::y = 10;

int main()
{
    MyClass obj1; // Object created in automatic memory (stack)
    obj1.x = 20;

    MyClass *obj2 = new MyClass(); // Object created in dynamic memory (heap)
    obj2->x = 30;

    obj1.print();
    obj2->print();

    delete obj2;
    return 0;
}

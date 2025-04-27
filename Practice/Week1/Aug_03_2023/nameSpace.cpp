#include <iostream>
using namespace std;

namespace myNamespace
{
    int a = 10;
    void printShri()
    {
        cout << "hello Shri" << endl;
    }
}

int main()
{
    myNamespace::a = 20;
    myNamespace::printShri();
    cout << myNamespace::a << endl;

    return 0;
}
#include <iostream>
#include <string>
using namespace std;

int main()
{
    // switch (1 < 2)
    switch (1)
    {
    case 0:
        cout << 0 << endl;
        break;
    case 1:
        cout << 1 << endl;
        break;
    default:
        cout << 3 << endl;
    }

    //
    for (int i = 0; i < 5; i++)
    {
        cout << i << " ";
    }
    cout << endl;

    //
    int count = 0;
    while (count++ < 5)
    {
        cout << "Inside While Loop " << endl;
    }
    cout << endl;

    //
    do
    {
        cout << "Inside Do While Loop " << endl;
    } while (count-- > 0);
    cout << endl;

    return 0;
}
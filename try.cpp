#include <iostream>
using namespace std;
#include <stdlib.h>

class myclass
{
public:
    void area(int i)
    {
        cout << "hello";
    }

    int area(int i, int y)
    {
        cout << "hi there!";
        return 2;
    }
};

int main()
{
    myclass mc;
    mc.area(8);
    cout << mc.area(2, 3);
    char c = 'h';
    cout << char(tolower(c)) << endl;
    return 0;
}

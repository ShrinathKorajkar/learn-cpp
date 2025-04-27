/*
    Types :- tradition, scoped enums
    Used to define named constants
*/

#include <iostream>
using namespace std;

enum color
{
    red,    // 0
    yellow, // 1
    green   // 2
};

enum class fruits
{
    apple = 1,
    banana = 2,
    mango = 3,
    orange = 4,
    watermelon = 5
};

enum class Status : char
{
    OK,   // '\0'
    ERROR // '\1'
};

int main()
{
    color mycolor = red;
    if (mycolor == red)
    {
        cout << "mycolor : " << mycolor;
    }

    fruits myfruit = fruits::mango;
    if (myfruit == fruits::mango)
    {
        cout << "\nmyfruit : " << static_cast<int>(myfruit) << endl;
    }

    cout << sizeof(fruits) << endl;
    return 0;
}
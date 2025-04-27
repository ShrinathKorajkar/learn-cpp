#include <iostream>
using namespace std;

#define PRINT_SHRI

int main()
{

#ifdef PRINT_SHRI
    cout << "Shri" << endl;
#endif

#ifdef PRINT_RAM
    cout << "Ram" << endl;
#endif

#ifndef PRINT_RAM
    cout << "Ram" << endl;
#endif

    return 0;
}

/*
    #if, #if defined()
*/
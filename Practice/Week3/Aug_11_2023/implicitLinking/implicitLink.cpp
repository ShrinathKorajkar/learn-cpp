#include <iostream>
#include "greetuser.hpp"
/*
    - g++  -shared  -Iinclude  -fPIC  greet.cpp  -o lib/libgreetLib.so
      g++  -Iinclude  implicitLink.cpp  -Llib  -lgreetLib  -o  ./output/implicitLink  -Wl,-rpath,lib
      ./myprogram
*/

int main()
{
    greet();
    return 0;
}
#include <iostream>       // implicit dynamic linking
#include "customMath.hpp" // static linking

/*
    g++ -o staticExample  main.cpp  staticfile.cpp
    ldd staticExample -> dynamic shared libraries

    # user defined .a static files
  - g++  -Iinclude  -c  customMath.cpp  -o  ./output/customMath.o
    ar  rcs  lib/libMathFuncs.a  ./output/customMath.o
    g++  -Iinclude staticLink.cpp  -Llib  -lMathFuncs  -o  ./output/staticLink
    ./staticLink

  - ar  :-  archive command
    rcs :-  r -> replace or add file to archive
            c -> create archive if doesn't exist
            s -> write index (symbol table) to archive to speed up archive
    *.o :-  precompiled files added to library
    libmath_functions.a  :-  name of output static library archive
*/

int main()
{
  std::cout << "Addition : " << add(1, 3) << std::endl;
  return 0;
}
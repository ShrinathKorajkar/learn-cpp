#include <iostream>
#include <dlfcn.h>
// #include "passwdGen.hpp"

/*
    g++  -shared  -fPIC  greet.cpp -o libmylib.so
    g++  -o   myprogram   main.cpp  -ldl
    ./myprogram

    g++ -shared -fPIC passwdGen.cpp -o lib/libmylib.so
    g++ -o ./output/explicitLink explicitLink.cpp -ldl
    ./output/explicitLink
*/

int main()
{
    std::string name = "Shrinath";
    // std::cout << "Static Linking Password : " << getPasswd(name) << std::endl;

    void *libHandler = dlopen("./lib/libmylib.so", RTLD_LAZY);
    if (!libHandler)
    {
        std::cout << "Could not open library " << dlerror() << std::endl;
        return 1;
    }

    using funcPointer = std::string (*)(std::string);
    // typedef int (*SquareFunction)(int);   // OR
    funcPointer getPassword = reinterpret_cast<funcPointer>(dlsym(libHandler, "getPasswd"));

    // int *variablePtr = reinterpret_cast<int *>(dlsym(libHandler, "myVariable"));

    if (!getPassword)
    {
        std::cerr << "Error Fetching Function " << dlerror() << std::endl;
        dlclose(libHandler);
        return 1;
    }

    std::cout << "Using Explicit Linking Password : " << getPassword(name) << std::endl;
    dlclose(libHandler);

    return 0;
}
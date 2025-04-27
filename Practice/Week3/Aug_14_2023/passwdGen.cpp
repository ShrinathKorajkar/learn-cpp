#include <iostream>
#include <cctype>
// #include "passwdGen.hpp"

/*
        extern "C" {
            int square(int x) {
                return x * x;
            }
        }
*/
// extern "C" int myVariable = 10;

extern "C" std::string getPasswd(std::string name)
{
    std::string passwd;
    for (int i = 0; i < name.length(); i++)
    {
        char c = tolower(name[i]);
        if (c == 'a')
        {
            passwd.push_back('@');
        }
        else if (c == 'i')
        {
            passwd.push_back('!');
        }
        else if (c == 's')
        {
            passwd.push_back('$');
        }
        else if (c == 'h')
        {
            passwd.push_back('#');
        }
        else if (c == 'b')
        {
            passwd.push_back('2');
        }
        else if (c == 'e')
        {
            passwd.push_back('3');
        }
        else if (c == 'o')
        {
            passwd.push_back('0');
        }
        else if (c == 'g')
        {
            passwd.push_back('4');
        }
        else
        {

            passwd += name[i];
        }
    }
    return passwd;
}
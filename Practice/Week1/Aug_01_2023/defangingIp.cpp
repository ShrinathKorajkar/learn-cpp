/*
    Q: Given Ip address, return defanged version of it
    input  :-  "255.100.50.0"
    output :-  "255[.]100[.]50[.]0"
*/

#include <iostream>
#include <string>
using namespace std;

string defangIPaddr(string address)
{
    string defangingString;
    for (char c : address)
    {
        if (c == '.')
        {
            defangingString.append("[.]");
        }
        else
        {
            defangingString.push_back(c);
        }
    }
    return defangingString;
}

int main()
{
    string ipAddr = "255.100.50.0";
    string defangedIp = defangIPaddr(ipAddr);
    cout << defangedIp << endl;
    return 0;
}
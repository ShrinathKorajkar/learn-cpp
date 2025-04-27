#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

int main()
{
    std::stringstream ss;

    int intValue = 42;
    double doubleValue = 3.14;

    ss << intValue << " " << doubleValue;

    int readIntValue;
    double readDoubleValue;

    ss >> readIntValue >> readDoubleValue;

    std::cout << "Read Integer: " << readIntValue << std::endl;
    std::cout << "Read Double: " << readDoubleValue << std::endl;

    std::string input = "42 3.14 shri";
    std::stringstream strstream(input);
    std::string data;
    while (std::getline(strstream, data, ' '))
    {
        std::cout << data << " ";
    }
    std::cout << std::endl;
    return 0;
}

#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
    std::fstream file("../files/example.txt");
    if (file.is_open())
    {
        std::string old = "shri";
        std::string replace = "rama";

        std::string lineAsString;
        while (std::getline(file, lineAsString))
        {
            size_t index;
            if ((index = lineAsString.find(old)) != std::string::npos)
            {
                file.seekp(-lineAsString.length() - 1, std::ios::cur);
                lineAsString.replace(index, old.length(), replace);
                file << lineAsString;
            }
        }
        file.close();
    }
    return 0;
}
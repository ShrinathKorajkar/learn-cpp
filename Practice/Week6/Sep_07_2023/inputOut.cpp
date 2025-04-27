#include <iostream>
#include <fstream>
#include <cstring>

int main()
{
    std::ofstream outputFile("../files/example.txt", std::ios::out);
    if (outputFile.is_open())
    {
        char ch = 'A';
        const char *line = "hello Shri, How are you?\n";

        outputFile << ch << std::endl;

        outputFile.put(ch);
        outputFile.put('\n');

        outputFile << line << std::endl;

        outputFile.write(line, strlen(line));
        outputFile.write(line, strlen(line));
        outputFile.close();
    }

    std::ifstream inputFile;
    inputFile.open("../files/example.txt", std::ios::in);
    if (inputFile.is_open())
    {
        char ch;
        inputFile.get(ch);
        std::cout << ch << std::endl;
        inputFile >> ch;
        std::cout << ch << std::endl;

        std::cout << inputFile.bad() << std::endl;
        std::cout << inputFile.good() << std::endl;
        std::cout << inputFile.fail() << std::endl;
        inputFile.clear();

        std::string line;
        while (std::getline(inputFile, line))
        {
            std::cout << line << std::endl;
        }

        inputFile.close();
    }
    return 0;
}
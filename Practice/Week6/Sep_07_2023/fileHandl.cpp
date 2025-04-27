#include <iostream>
#include <fstream>
#include <cstring>

int main()
{
    std::ofstream outputFile;

    outputFile.open("../files/example.txt", std::ios::out | std::ios::binary | std::ios::app);

    if (!outputFile.is_open())
    {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return 1;
    }

    const char *dataToWrite = "Hello, world!";
    outputFile.write(dataToWrite, strlen(dataToWrite));

    outputFile.seekp(0, std::ios::beg);

    const char *additionalData = "This is additional data.";
    outputFile << additionalData << std::endl;

    outputFile.flush();

    outputFile.close();

    std::ifstream inputFile;

    inputFile.open("../files/example.txt", std::ios::in | std::ios::binary);

    if (!inputFile.is_open())
    {
        std::cerr << "Failed to open the file for reading." << std::endl;
        return 1;
    }

    char buffer[256];
    inputFile.read(buffer, sizeof(buffer));

    std::cout << "Read data from the file:" << std::endl;
    std::cout.write(buffer, inputFile.gcount()) << std::endl;

    std::streampos currentPosition = inputFile.tellg();
    std::cout << "Current file position: " << currentPosition << std::endl;

    inputFile.close();

    return 0;
}

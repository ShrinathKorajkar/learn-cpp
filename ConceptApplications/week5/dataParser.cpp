#include <iostream>
#include <fstream>
#include "parser.hpp"

void printError(const std::string &message)
{
    std::cout << message << std::endl;
    std::cin.ignore();
    std::cin.clear();
}

void startParsing(const int &choice)
{
    Parser *parser;
    switch (choice)
    {
    case 1:
        parser = new CsvParser();
        break;
    case 2:
        parser = new JsonParser();
        break;
    case 3:
        parser = new XmlParser();
        break;
    default:
        printError("\nInvalid Choice!... Please choose from given options.\n");
        return;
    }
    parser->parseFile();
    delete parser;
}

int main()
{
    int choice{};
    do
    {
        std::cout << "\nEnter Your Choice : " << std::endl;
        std::cout << "1. Parse CSV          2. Parse JSON          3. Parse XML           4. Exit" << std::endl;
        std::cin >> choice;
        if (std::cin.fail())
        {
            printError("\nInvalid Choice!... Please Enter valid choice\n");
            continue;
        }
        startParsing(choice);
    } while (choice != 4);
    return 0;
}

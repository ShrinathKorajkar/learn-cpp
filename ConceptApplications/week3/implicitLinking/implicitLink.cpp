#include <iostream>
#include "mathHeader.hpp"

void printError()
{
    std::cout << "\nInvalid Choice!.... Try again" << std::endl;
    std::cin.clear();
    std::cin.ignore();
}

void takeInput(int &value1, int &value2)
{
    std::cout << "\nEnter Two Numbers : ";
    std::cin >> value1 >> value2;
    if (std::cin.fail())
    {
        printError();
        takeInput(value1, value2);
    }
}

void addNumbers(const int &value1, const int &value2)
{
    int result = math::add(value1, value2);
    std::cout << "Addition of " << value1 << " and " << value2 << " : " << result << std::endl;
}

void subtractNumbers(const int &value1, const int &value2)
{
    int result = math::subtract(value1, value2);
    std::cout << "Subtraction of " << value1 << " and " << value2 << " : " << result << std::endl;
}

void multiplyNumbers(const int &value1, const int &value2)
{
    int result = math::multiply(value1, value2);
    std::cout << "Multiplication of " << value1 << " and " << value2 << " : " << result << std::endl;
}

void divideNumbers(const int &value1, const int &value2)
{
    int result = math::divide(value1, value2);
    std::cout << "Division of " << value1 << " and " << value2 << " : " << result << std::endl;
}

int main()
{
    int choice = 0;
    int value1 = 0, value2 = 0;
    do
    {
        std::cout << "\n1. Add        2. Subtract         3. Multiply        4. Divide        5. Exit" << std::endl;
        std::cout << "Enter your Choice : " << std::endl;
        std::cin >> choice;
        if (std::cin.fail())
        {
            printError();
            continue;
        }

        switch (choice)
        {
        case 1:
            takeInput(value1, value2);
            addNumbers(value1, value2);
            break;
        case 2:
            takeInput(value1, value2);
            subtractNumbers(value1, value2);
            break;
        case 3:
            takeInput(value1, value2);
            multiplyNumbers(value1, value2);
            break;
        case 4:
            takeInput(value1, value2);
            divideNumbers(value1, value2);
            break;
        case 5:
            break;
        default:
            printError();
        }

    } while (choice != 5);

    return 0;
}
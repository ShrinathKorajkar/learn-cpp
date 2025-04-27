#include <iostream>
#include <dlfcn.h>

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

void addNumbers(void *libHandle, const int &value1, const int &value2)
{
    typedef int (*AddFunc)(const int &, const int &);
    AddFunc add = reinterpret_cast<AddFunc>(dlsym(libHandle, "add"));
    int result = add(value1, value2);
    std::cout << "Addition of " << value1 << " and " << value2 << " : " << result << std::endl;
}

void subtractNumbers(void *libHandle, const int &value1, const int &value2)
{
    typedef int (*SubFunc)(const int &, const int &);
    SubFunc sub = reinterpret_cast<SubFunc>(dlsym(libHandle, "subtract"));
    int result = sub(value1, value2);
    std::cout << "Subtraction of " << value1 << " and " << value2 << " : " << result << std::endl;
}

void multiplyNumbers(void *libHandle, const int &value1, const int &value2)
{
    typedef int (*MultFunc)(const int &, const int &);
    MultFunc multiply = reinterpret_cast<MultFunc>(dlsym(libHandle, "multiply"));
    int result = multiply(value1, value2);
    std::cout << "Multiplication of " << value1 << " and " << value2 << " : " << result << std::endl;
}

void divideNumbers(void *libHandle, const int &value1, const int &value2)
{
    using DivideFunc = int (*)(const int &, const int &);
    DivideFunc divide = reinterpret_cast<DivideFunc>(dlsym(libHandle, "divide"));
    int result = divide(value1, value2);
    std::cout << "Division of " << value1 << " and " << value2 << " : " << result << std::endl;
}

int main()
{
    int choice = 0;
    int value1 = 0, value2 = 0;

    void *libHandle = dlopen("./lib/libcustomMath.so", RTLD_LAZY);
    if (!libHandle)
    {
        std::cout << "Erroe : could not open library" << std::endl;
        return 1;
    }

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
            addNumbers(libHandle, value1, value2);
            break;
        case 2:
            takeInput(value1, value2);
            subtractNumbers(libHandle, value1, value2);
            break;
        case 3:
            takeInput(value1, value2);
            multiplyNumbers(libHandle, value1, value2);
            break;
        case 4:
            takeInput(value1, value2);
            divideNumbers(libHandle, value1, value2);
            break;
        case 5:
            break;
        default:
            printError();
        }

    } while (choice != 5);

    dlclose(libHandle);
    return 0;
}
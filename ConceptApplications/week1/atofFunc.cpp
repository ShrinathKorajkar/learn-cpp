#include <iostream>

/*
    Q: User defined function for atof()
    input: "12.23"
    output: 12.23
*/

bool isValidChar(const char c)
{
    return (c >= '0' && c <= '9' && c != '\0') || (c == '.');
}

float atofunc(const char *input)
{
    int index = 0;
    int sign = 1;
    if (input[index] == '-' && isValidChar(input[index + 1]))
    {
        sign = -1;
        index++;
    }
    else if (input[index] == '+')
    {
        index++;
    }

    float number = 0.0;
    while (isValidChar(input[index]))
    {
        if (input[index] == '.')
        {
            index++;
            break;
        }
        number = number * 10 + (input[index] - '0');
        input++;
    }

    float fraction = 0.1;
    for (; isValidChar(input[index]); index++)
    {
        if (input[index] == '.')
        {
            break;
        }
        number += (fraction * (input[index] - '0'));
        fraction = fraction * 0.1;
    }

    number *= sign;
    return number;
}

int main()
{
    char input[100];
    std::cout << "Enter the Input : ";
    std::cin >> input;

    std::cout << "User Defined    : " << atofunc(input) << std::endl;

    std::cout << "BuiltIn atof()  : " << atof(input) << std::endl;

    return 0;
}
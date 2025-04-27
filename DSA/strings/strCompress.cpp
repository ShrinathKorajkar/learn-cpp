#include <iostream>
#include <vector>

int compress(std::vector<char> &chars)
{
    int firstPtr = 0;
    int secondPtr = 1;
    char currentChar = chars[0];
    int currentCharCount = 1;
    for (; secondPtr < chars.size(); secondPtr++)
    {
        if (chars[secondPtr] == currentChar)
        {
            currentCharCount++;
        }
        else
        {
            chars[firstPtr++] = currentChar;
            if (currentCharCount != 1)
            {
                std::string countStr = std::to_string(currentCharCount);
                for (char c : countStr)
                {
                    chars[firstPtr++] = c;
                }
            }
            currentChar = chars[secondPtr];
            currentCharCount = 1;
        }
    }

    chars[firstPtr++] = currentChar;
    if (currentCharCount != 1)
    {
        std::string countStr = std::to_string(currentCharCount);
        for (char c : countStr)
        {
            chars[firstPtr++] = c;
        }
    }

    return firstPtr;
}

int main()
{
    std::vector<char> str = {'a', 'a', 'c', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'};
    int len = compress(str);
    std::cout << "len : " << len << std::endl;
    str.resize(len);
    for (char c : str)
    {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    return 0;
}
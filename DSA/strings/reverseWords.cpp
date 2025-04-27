#include <iostream>
#include <algorithm>

std::string reverseWords(std::string s)
{
    s = " " + s + " ";
    int strLen = s.length();
    int firstCharIndex = s.find_first_not_of(" ");
    int nextCharIndex = firstCharIndex;
    int lastCharIndex = s.find_last_not_of(" ");

    while (nextCharIndex >= 0 && nextCharIndex < strLen)
    {
        int nextSpaceIndex = s.find_first_of(" ", nextCharIndex);
        std::reverse(s.begin() + nextCharIndex, s.begin() + nextSpaceIndex);
        nextCharIndex = s.find_first_not_of(" ", nextSpaceIndex);
    }

    s = s.substr(firstCharIndex, lastCharIndex - firstCharIndex + 1);
    std::reverse(s.begin(), s.end());

    int i = 0, j = 0;
    strLen = s.length();
    while (j < strLen)
    {
        if (s[j] == ' ' && s[j + 1] == ' ')
        {
            j++;
            continue;
        }
        s[i++] = s[j++];
    }
    s.resize(strLen - (j - i));

    return s;
}

int main()
{
    std::string str = " a good   example ";
    std::cout << "\"" << reverseWords(str) << "\"" << std::endl;
    return 0;
}
#include <iostream>

bool isPalindrome(std::string s)
{
    int start = 0;
    int end = s.size() - 1;
    while (start < end)
    {
        while (!std::isalnum(s[start]))
        {
            start++;
        }
        while (!std::isalnum(s[end]))
        {
            end--;
        }

        if (start >= end)
        {
            break;
        }

        if (std::tolower(s[start++]) != std::tolower(s[end--]))
        {
            return false;
        }
    }
    return true;
}

std::string removeOccurrences(std::string s, std::string part)
{
    int foundIndx = 0;
    while (s.find(part) != std::string::npos)
    {
        foundIndx = s.find(part);
        s.erase(foundIndx, part.length());
    }
    return s;

    // More optimised
    // std::string x = s;
    // int n = s.size(), m = part.size(), i, j;
    // for (i = 0, j = 0; i < n; i++)
    // {
    //     x[j++] = s[i];
    //     if (j >= m && x.substr(j - m, m) == part)
    //         j -= m;
    // }
    // return x.substr(0, j);
}

int main()
{
    std::string s = "A man, a plan, a canal: Panama";
    std::cout << std::boolalpha << isPalindrome(s) << std::endl;
    std::cout << std::noboolalpha << isPalindrome(s) << std::endl;
    std::cout << removeOccurrences("daabcbaabcbc", "abc") << std::endl;
    return 0;
}
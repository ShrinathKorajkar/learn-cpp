#include <iostream>

bool checkInclusion(std::string s1, std::string s2)
{
    int freqs1[27] = {0};
    int freqs2[27] = {0};
    int sum = 0;
    int i = 0;
    int j = 0;

    if (s2.size() < s1.size())
    {
        return false;
    }

    for (char ch : s1)
    {
        freqs1[ch - 'a']++;
    }

    while (i < s1.size())
    {
        freqs2[s2[i] - 'a']++;
        if (freqs2[s2[i] - 'a'] == freqs1[s2[i] - 'a'])
        {
            sum += freqs2[s2[i] - 'a'];

            if (sum == s1.size())
            {
                return true;
            }
        }
        i++;
    }
    j = i;
    i = 0;

    while (j < s2.size())
    {
        if (freqs2[s2[i] - 'a'] == freqs1[s2[i] - 'a'])
        {

            sum -= freqs2[s2[i] - 'a'];
        }
        freqs2[s2[i] - 'a']--;
        freqs2[s2[j] - 'a']++;
        if (freqs2[s2[j] - 'a'] == freqs1[s2[j] - 'a'])
        {
            sum += freqs2[s2[j] - 'a'];
        }
        i++;
        j++;
        if (sum == s1.size())
        {
            return true;
        }
    }
    return false;
}

int main()
{
    std::string s1 = "eidbaooo";
    std::string s2 = "ab";
    std::cout << std::boolalpha << checkInclusion(s1, s2) << std::endl;
    return 0;
}
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <algorithm>
/*
    program to find the most frequent occurred words in sentence
*/
bool isSentenceEmpty(const std::string &sentence)
{
    return sentence.size() == 0;
}

void countWordsInSentence(const std::string &sentence, std::unordered_map<std::string, int> &wordCount)
{
    std::stringstream streamOfSentence(sentence);
    std::string word;

    while (streamOfSentence >> word)
    {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (wordCount.count(word) == 0)
        {
            wordCount[word] = 1;
        }
        else
        {
            wordCount[word] += 1;
        }
    }
}

void findMostFrequenWords(const std::unordered_map<std::string, int> &wordCount)
{
    int maxCount = std::max_element(wordCount.begin(), wordCount.end(),
                                    [](const std::pair<std::string, int> &p1, const std::pair<std::string, int> &p2)
                                    { return p1.second < p2.second; })
                       ->second;

    std::cout << "Most Frequent Word Length : " << maxCount << std::endl;
    std::cout << "All Possible Words : " << std::endl;
    for (auto pair : wordCount)
    {
        if (pair.second == maxCount)
        {
            std::cout << pair.first << std::endl;
        }
    }
}

int main()
{
    std::cout << "Enter Sentence : ";
    std::string sentence;
    std::getline(std::cin, sentence);

    if (isSentenceEmpty(sentence))
    {
        std::cout << "Sentence Empty" << std::endl;
        return 0;
    }

    std::unordered_map<std::string, int> wordCount;

    countWordsInSentence(sentence, wordCount);

    findMostFrequenWords(wordCount);
    return 0;
}
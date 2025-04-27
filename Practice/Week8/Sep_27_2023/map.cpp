#include <iostream>
#include <map>

int main()
{
    std::map<std::string, int> myMap;

    myMap["Alice"] = 25;
    myMap["Bob"] = 30;
    myMap["Charlie"] = 22;
    myMap.insert(std::pair<std::string, int>("Shri", 22));

    auto it = myMap.extract("Alice");
    std::map<std::string, int> newMap;
    newMap.insert(std::move(it));

    newMap.swap(myMap);
    std::swap(myMap, newMap);

    std::cout << "Age of Bob: " << myMap["Bob"] << std::endl;

    for (const auto &pair : myMap)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}

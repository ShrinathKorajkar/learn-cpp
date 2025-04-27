#include <iostream>
#include <unordered_map>
#include <string>

struct MyKey
{
    std::string name;
    int id;

    MyKey(const std::string &n, int i) : name(n), id(i) {}

    bool operator==(const MyKey &other) const
    {
        return name == other.name && id == other.id;
    }
};

struct MyKeyHash
{
    std::size_t operator()(const MyKey &key) const
    {
        std::size_t nameHash = std::hash<std::string>()(key.name);
        std::size_t idHash = std::hash<int>()(key.id);

        return nameHash ^ idHash;
    }
};

int main()
{
    std::unordered_map<MyKey, int, MyKeyHash> scores;

    scores[MyKey("Alice", 1)] = 90;
    scores[MyKey("Bob", 2)] = 85;
    scores[MyKey("Eve", 3)] = 88;

    MyKey searchKey("Alice", 1);
    auto it = scores.find(searchKey);
    if (it != scores.end())
    {
        std::cout << "Score for " << searchKey.name << " (ID " << searchKey.id << "): " << it->second << std::endl;
    }
    else
    {
        std::cout << "Score not found for " << searchKey.name << " (ID " << searchKey.id << ")" << std::endl;
    }

    return 0;
}

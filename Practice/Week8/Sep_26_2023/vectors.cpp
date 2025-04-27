#include <iostream>
#include <vector>

class Person
{
public:
    Person(std::string name, int age) : name_(std::move(name)), age_(age) {}

    void printInfo() const
    {
        std::cout << "Name: " << name_ << ", Age: " << age_ << std::endl;
    }

private:
    std::string name_;
    int age_;
};

int main()
{
    std::vector<int> array(2, 1);
    std::vector<int> array2 = {0, 1, 2, 3, 4, 5, 6, 7};

    array2.push_back(1);
    array.resize(4, 2);
    int *dataPointer = array.data();
    std::cout << dataPointer[1] << std::endl;

    std::cout << "Array 1 Elements : ";
    for (auto value : array)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "Array 2 capacity : " << array2.capacity() << std::endl;
    std::cout << "Array 2 size     : " << array2.size() << std::endl;
    std::cout << "Array 2 front    : " << array2.front() << std::endl;
    std::cout << "Array 2 back    : " << array2.back() << std::endl;

    array2.pop_back();
    array2.insert(array2.begin() + 1, 2);
    array2.erase(array2.end() - 1);
    array.shrink_to_fit();

    std::cout << "Array 2 Elements : ";
    for (std::vector<int>::iterator i = array2.begin(); i != array2.end(); ++i)
    {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    std::swap(array2, array);
    array.swap(array2);

    array2.clear();
    std::cout << "Array 2 capacity : " << array2.capacity() << std::endl;
    std::cout << "Array 2 size     : " << array2.size() << std::endl;
    std::cout << "Array 2 max_size : " << array2.max_size() << std::endl;
    std::cout << "Array 2 isEmpty  : " << array2.empty() << std::endl;

    // assign
    std::vector<int> numbers = {0, 1, 2, 3, 4, 5, 6};

    std::cout << "Original Vector: ";
    for (const int &num : numbers)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::vector<int> newValues = {10, 20, 30};
    numbers.assign(newValues.begin(), newValues.end());

    std::cout << "Modified Vector: ";
    for (const int &num : numbers)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // emplace
    std::vector<Person> people;

    people.emplace_back("Alice", 25); // insert in place
    people.emplace_back("Bob", 30);

    for (const auto &person : people)
    {
        person.printInfo();
    }

    std::cout << std::endl
              << sizeof(people) << std::endl;
    return 0;
}
#include <iostream>
#include <cstring>
#include <vector>

class MyString
{
public:
    char *data;
    MyString() : data(new char[10])
    {
        std::cout << "Default constructor : " << data << std::endl;
        strcpy(data, "Empty");
    }

    MyString(const char *value)
    {
        std::cout << "Param Constructor called : " << value << std::endl;
        data = new char[strlen(value) + 1];
        strcpy(data, value);
    }

    MyString(const MyString &other)
    {
        std::cout << "Copy Constructor called : " << other.data << std::endl;
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    MyString &operator=(const MyString &other)
    {
        std::cout << "Copy Assignment Operator called : " << other.data << std::endl;
        if (this != &other)
        {
            delete[] data;
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    MyString(MyString &&other) noexcept : data(other.data)
    {
        std::cout << "Move Constructor called : " << other.data << std::endl;
        other.data = nullptr;
    }

    MyString &operator=(MyString &&other) noexcept
    {
        std::cout << "Move Assignment Operator called : " << other.data << std::endl;
        if (this != &other)
        {
            delete[] data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }

    ~MyString()
    {
        if (data != nullptr)
        {
            std::cout << "Destructor Called : " << data << std::endl;
            delete[] data;
        }
        else
        {
            std::cout << "Destructor Called on nullptr " << std::endl;
        }
    }

    void display() const
    {
        if (data)
        {
            std::cout << data << std::endl;
        }
        else
        {
            std::cout << "Empty" << std::endl;
        }
    }
};

int main()
{
    std::vector<MyString> strings;
    // strings.reserve(3);
    strings.push_back("foo");
    strings.push_back("bar"); // for adding this reallocation happens as size is increased
    return 0;
}

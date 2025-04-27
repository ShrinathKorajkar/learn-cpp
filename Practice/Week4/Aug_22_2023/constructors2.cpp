#include <iostream>
#include <cstring>

class MyString
{
public:
    char *data;
    MyString() : data(new char[10])
    {
        std::cout << "Default constructor" << std::endl;
        strcpy(data, "Empty");
    }

    MyString(const char *value)
    {
        std::cout << "Param Constructor called" << std::endl;
        data = new char[strlen(value) + 1];
        strcpy(data, value);
    }

    MyString(const MyString &other)
    {
        std::cout << "Copy Constructor called" << std::endl;
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    MyString &operator=(const MyString &other)
    {
        std::cout << "Copy Assignment Operator called" << std::endl;
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
        std::cout << "Move Constructor called" << std::endl;
        other.data = nullptr;
    }

    MyString &operator=(MyString &&other) noexcept
    {
        std::cout << "Move Assignment Operator called" << std::endl;
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
        std::cout << "Destructor Called" << std::endl;
        delete[] data;
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
    MyString str1("Hello");

    MyString str2 = str1;

    MyString str3 = std::move(str2);

    MyString str4("World");
    str4 = std::move(str3);

    MyString str5("World");
    str5 = str4;

    std::cout << std::endl;

    MyString str6 = "hello"; // in aggregate class -> aggregate initialization
    MyString str7;
    str7 = "hello"; // param -> move -> destruct for "hello"

    MyString str8 = MyString("hello"); // only param
    MyString str9{"hello"};

    std::cout << std::endl;

    return 0;
}

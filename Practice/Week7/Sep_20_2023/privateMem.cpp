#include <sstream>
#include <string>
#include <gtest/gtest.h>

class Person
{
    std::string name_;
    int age_;

public:
    Person(const std::string &name, int age) : name_(name), age_(age) {}
    FRIEND_TEST(PersonTest, GetName);
    friend std::ostream &operator<<(std::ostream &os, const Person &person);
};

std::ostream &operator<<(std::ostream &os, const Person &person)
{
    os << "Name: " << person.name_ << ", Age: " << person.age_;
    return os;
}

class PersonTest : public ::testing::Test
{
protected:
    PersonTest() : person_("Alice", 30) {}
    void SetUp() override
    {
        person_ = Person("Alice", 30);
    }

    Person person_;
};

TEST_F(PersonTest, GetName)
{
    EXPECT_EQ(person_.name_, "Alice");
}

TEST_F(PersonTest, PrintPerson)
{
    std::stringstream ss;
    ss << person_;
    EXPECT_EQ(ss.str(), "Name: Alice, Age: 30");
    std::cout << testing::PrintToString(person_) << std::endl;
}

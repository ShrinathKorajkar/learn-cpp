#include "jsonParser.h"
#include <gtest/gtest.h>

TEST(JsonParserTest, SimpleValidJson_ParseSuccessfull)
{
    JsonParser parser;
    std::string validJson = R"(
            {
                "name": "John",
                "age": 30,
                "isMarried": true
            }
    )";

    EXPECT_NO_THROW({
        JsonValue root = parser.parse(validJson);
        EXPECT_EQ(root["name"].as_string(), "John");
        EXPECT_EQ(root["age"].as_double(), 30);
        EXPECT_EQ(root["isMarried"].as_bool(), true);
    });
}

TEST(JsonParserTest, JsonWithArray_ParseSuccessfull)
{
    JsonParser parser;
    std::string validJson = R"(
           {
                "names": ["John", "Alice", "Bob"],
                "numbers": [1, 2, 3, 4, 5]
           }

    )";

    EXPECT_NO_THROW(
        {
            JsonValue root = parser.parse(validJson);
            const JsonValue names = root["names"];

            EXPECT_EQ(names[0].as_string(), "John");
            EXPECT_EQ(names[1].as_string(), "Alice");
            EXPECT_EQ(names[2].as_string(), "Bob");

            JsonValue numbers = root["numbers"];
            EXPECT_EQ(numbers[0].as_double(), 1);
            EXPECT_EQ(numbers[1].as_double(), 2);
            EXPECT_EQ(numbers[2].as_double(), 3);
            EXPECT_EQ(numbers[3].as_double(), 4);
            EXPECT_EQ(numbers[4].as_double(), 5);
        });
}

TEST(JsonParserTest, ValidNestedJsonData_ParseSuccessfull)
{
    JsonParser parser;
    std::string validJson = R"(
           {
                "person": {
                    "name": "John",
                    "age": 30,
                    "address": {
                        "city": "New York",
                        "country": "USA"
                    }
                }
            }
    )";

    EXPECT_NO_THROW(
        {
            JsonValue root = parser.parse(validJson);

            JsonValue person = root["person"];
            EXPECT_EQ(person["name"].as_string(), "John");
            EXPECT_EQ(person["age"].as_double(), 30);
            EXPECT_EQ(person["address"]["city"].as_string(), "New York");
            EXPECT_EQ(person["address"]["country"].as_string(), "USA");
        });
}

TEST(JsonParserTest, JsonWithEscapedCharacters_ParseSuccessful)
{
    JsonParser parser;
    std::string validJson = R"(
        {
            "escapedChars": "This contains \"quotes\" and \n new line character."
        }
    )";

    EXPECT_NO_THROW({
        JsonValue root = parser.parse(validJson);
        JsonValue escapedChars = root["escapedChars"];
        EXPECT_EQ(escapedChars.as_string(), "This contains \"quotes\" and \n new line character.");
    });
}

TEST(JsonParserTest, EmptyObjectAndArray_ParseSuccessfully)
{
    JsonParser parser;
    std::string json = R"(
        {
            "emptyObject": {},
            "emptyArray": []
        }
    )";

    EXPECT_NO_THROW({
        JsonValue root = parser.parse(json);

        JsonValue emptyObject = root["emptyObject"];
        JsonValue emptyArray = root["emptyArray"];
    });
}

TEST(JsonParserTest, MissingJsonValue_ThrowException)
{
    JsonParser parser;
    std::string invalidJson = R"(
            {
                "name": "John",
                "age": 
            }
    )";

    EXPECT_THROW(
        {
            JsonValue root = parser.parse(invalidJson);
            std::string name = root["name"].as_string();
            int age = root["age"].as_double();
        },
        JsonParseException);
}

TEST(JsonParserTest, AccessNonexistentStringKey_ThrowException)
{
    JsonParser parser;
    std::string invalidJson = R"(
            {
                "name": "John",
                "age": 30
            }
    )";

    EXPECT_THROW(
        {
            JsonValue root = parser.parse(invalidJson);
            JsonValue value = root["nonExistentKey"];
        },
        JsonParseException);
}

TEST(JsonParserTest, AccessNonexistentIntKey_ThrowException)
{
    JsonParser parser;
    std::string invalidJson = R"(
            {
                "name": "John",
                "age": 30
            }
    )";

    JsonValue root = parser.parse(invalidJson);

    EXPECT_THROW(
        {
            JsonValue value = root[10];
        },
        JsonParseException);

    EXPECT_THROW(
        {
            JsonValue value = root[-1];
        },
        JsonParseException);
}

TEST(JsonParserTest, InvalidJsonFormat_ThrowException)
{
    JsonParser parser;
    // missing:  , }
    std::string invalidJson = R"(
           {
                "name": "John"
                "age": 30,
    )";

    EXPECT_THROW(
        {
            JsonValue root = parser.parse(invalidJson);
        },
        JsonParseException);
}

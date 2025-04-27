#include <gtest/gtest.h>
#include "webConnector.h"

class WebConnectorTest : public ::testing::Test
{
protected:
};

TEST_F(WebConnectorTest, Initialization_CURL)
{
    // Ensure CURL is initialized
    EXPECT_NO_THROW(WebConnector::get_instance());
}

TEST_F(WebConnectorTest, Singleton_SameInstanceIsReturned)
{
    WebConnector &instance1 = WebConnector::get_instance();
    WebConnector &instance2 = WebConnector::get_instance();
    EXPECT_EQ(&instance1, &instance2);
}

TEST_F(WebConnectorTest, UrlDataWithSpecialChars_EncodeInCorrectFormat)
{
    std::string encodedUrl = WebConnector::get_instance().url_safe_encode("http://example.com/?q=hello world");
    EXPECT_EQ(encodedUrl, "http%3A%2F%2Fexample.com%2F%3Fq%3Dhello%20world");
}

TEST_F(WebConnectorTest, HttpRequest_ReceiveProperResponse)
{
    EXPECT_NO_THROW({
        std::string response = WebConnector::get_instance().send_request("http://example.com");
        EXPECT_FALSE(response.empty());
    });
}

TEST_F(WebConnectorTest, InvalidHttpRequest_HandleError)
{
    EXPECT_THROW(
        {
            std::string response = WebConnector::get_instance().send_request("invalid_url");
        },
        RequestException);
}

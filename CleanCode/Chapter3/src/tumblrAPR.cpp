/**
 * @file tumblerAPI.cpp
 * @brief This file contains the implementation of TumblrAPI class.
 */

#include "tumblrAPI.h"
#include <stdexcept>

TumblrAPI::TumblrAPI(const TumblrApiParameters &apiParams)
{
    std::string blogName = apiParams.blogName;
    auto [postRangeStartIndex, postRangeEndIndex] = apiParams.postRange;
    int numberOfPostsToFetch = postRangeEndIndex - postRangeStartIndex + 1;

    apiEndpoint = "https://" + blogName + ".tumblr.com/api/read/json?type=photo&start=" + std::to_string(postRangeStartIndex - 1) + "&num=" + std::to_string(numberOfPostsToFetch);

    initApi();
}

void TumblrAPI::initApi()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curlHandle = curl_easy_init();

    if (curlHandle == nullptr)
    {
        throw std::runtime_error("Failed to initialize curl");
    }

    setUpRequestOptions();
}

void TumblrAPI::setUpRequestOptions()
{
    // Set the URL for request
    curl_easy_setopt(curlHandle, CURLOPT_URL, apiEndpoint.c_str());

    // Set callback function to handle response data
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, responseCallback);

    // Set data pointer to be passed to callback function
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &responseData);
}

size_t TumblrAPI::responseCallback(void *responseBuffer, size_t singleElementSize, size_t elementCount, std::string *outputString)
{
    size_t totalDataSize = singleElementSize * elementCount;
    outputString->append(static_cast<char *>(responseBuffer), totalDataSize);
    return totalDataSize;
}

std::string TumblrAPI::fetchData()
{
    // Perform the CURL request
    CURLcode responseStatus = curl_easy_perform(curlHandle);

    if (responseStatus != CURLE_OK)
    {
        throw std::runtime_error("In API Call - " + std::string(curl_easy_strerror(responseStatus)) + "\t\t(Check Network Connection or API endpoint URL)");
    }

    std::string jsonData = extractJsonData(responseData);
    return jsonData;
}

std::string TumblrAPI::extractJsonData(const std::string &responseData)
{
    size_t jsonStartPosition = responseData.find("{");
    size_t jsonEndPosition = responseData.find("};", jsonStartPosition);

    if (!validJsonData(jsonStartPosition, jsonEndPosition))
    {
        throw std::runtime_error("extracting JSON content from response");
    }

    std::string jsonData = responseData.substr(jsonStartPosition, jsonEndPosition - jsonStartPosition + 1);
    return jsonData;
}

bool TumblrAPI::validJsonData(const size_t &jsonStartPosition, const size_t &jsonEndPosition)
{
    return jsonStartPosition != std::string::npos && jsonEndPosition != std::string::npos;
}

TumblrAPI::~TumblrAPI()
{
    if (curlHandle != nullptr)
    {
        curl_easy_cleanup(curlHandle);
    }
    curl_global_cleanup();
}

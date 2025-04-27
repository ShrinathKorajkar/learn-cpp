/**
 * @file tumblrAPI.h
 * @brief This file contains the declaration of the TumblrAPI class and related structures.
 *
 * The TumblrAPI class is designed to facilitate communication with the Tumblr API
 * for retrieving blog information and posts. It uses the libcurl library for HTTP
 * requests and the JsonCpp library for JSON parsing.
 *
 * @section Usage
 *
 * To use the TumblrAPI class, create an instance with appropriate parameters using
 * the TumblrApiParameters struct. Call the `fetchData` method to perform the API
 * request and retrieve JSON data. The class provides methods for extracting
 * relevant information from the JSON response.
 *
 * @section Dependencies
 *
 * - libcurl: https://curl.haxx.se/libcurl/
 */

#ifndef TUMBLR_API_H
#define TUMBLR_API_H

#include <curl/curl.h>
#include <string>
#include <tuple>

/**
 * @brief Structure to hold parameters for Tumblr API
 */
struct TumblrApiParameters
{
    std::string blogName;
    std::tuple<int, int> postRange;
};

/**
 * @brief Class representing Tumblr API functionality
 */
class TumblrAPI
{
public:
    /**
     * @brief Constructor to initialize TumblrAPI with specified parameters
     * @param apiParams Parameters for configuring the TumblrAPI
     */
    TumblrAPI(const TumblrApiParameters &apiParams);

    /**
     * @brief Destructor to clean up resources when TumblrAPI object goes out of scope
     */
    ~TumblrAPI();

    /**
     * @brief Performs API call, fetches data, and returns JSON content.
     * @return JSON content fetched from the Tumblr API.
     */
    std::string fetchData();

private:
    /**
     * @brief Initializes libcurl and sets up request options.
     */
    void initApi();

    /**
     * @brief Set up options for the CURL request
     */
    void setUpRequestOptions();

    /**
     * @brief Extracts the JSON data from the Tumblr API response.
     *
     * This function locates the JSON content within the response and extracts it.
     * The API response format is typically like: "var tumblr_api_read = {...};"
     * We ignore the variable assignment and extract only the JSON data.
     *
     * @param responseData The raw response received from the Tumblr API.
     * @return A string containing the extracted JSON data.
     * @throws std::runtime_error if the JSON content extraction fails.
     */
    std::string extractJsonData(const std::string &responseData);

    /**
     * @brief Callback function to handle the response received from the API
     * @param responseBuffer Buffer containing the response data
     * @param singleElementSize Size of each element in the buffer
     * @param elementCount Number of elements in the buffer
     * @param outputString Pointer to a string to store the output
     * @return Size of the data processed
     */
    static size_t responseCallback(void *responseBuffer, size_t singleElementSize, size_t elementCount, std::string *outputString);

    /**
     * @brief Check if the JSON data in the response is valid
     * @param jsonStartPosition Starting position of JSON data in the response
     * @param jsonEndPosition Ending position of JSON data in the response
     * @return True if JSON data is valid, false otherwise
     */
    bool validJsonData(const size_t &jsonStartPosition, const size_t &jsonEndPosition);

    // Member variables
    std::string apiEndpoint;    ///< Holds the constructed API endpoint URL
    std::string responseData;   ///< Holds the response data received from the API
    CURL *curlHandle = nullptr; ///< CURL handle for making HTTP requests
};

#endif

#include <iostream>
#include <curl/curl.h>
#include <string>

// Callback function to handle the received data
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response)
{
    size_t totalSize = size * nmemb;
    response->append(static_cast<char *>(contents), totalSize);
    return totalSize;
}

int main()
{
    // Initialize cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create cURL handle
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        std::cerr << "cURL initialization failed" << std::endl;
        return 1;
    }

    // Set the URL for the GET request
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.example.com");

    // Set the callback function for writing received data
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    std::string responseData;
    // Set the data pointer to be passed to the write callback
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

    // Perform the GET request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
    }

    // Cleanup
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}

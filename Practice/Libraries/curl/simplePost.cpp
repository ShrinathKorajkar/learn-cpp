#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>
#include <iomanip>

// Callback function to handle the received data
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response)
{
    size_t totalSize = size * nmemb;
    response->append(static_cast<char *>(contents), totalSize);
    return totalSize;
}

std::string url_decode(const std::string &encodedStr)
{
    std::stringstream decodedStream;
    decodedStream << std::hex;

    for (size_t i = 0; i < encodedStr.length(); ++i)
    {
        if (encodedStr[i] == '%' && i + 2 < encodedStr.length())
        {
            char hex[3] = {encodedStr[i + 1], encodedStr[i + 2], '\0'};
            int decodedChar;
            std::istringstream(hex) >> decodedChar;
            decodedStream << static_cast<char>(decodedChar);
            i += 2;
        }
        else if (encodedStr[i] == '+')
        {
            decodedStream << ' '; // Convert '+' to space
        }
        else
        {
            decodedStream << encodedStr[i];
        }
    }

    return decodedStream.str();
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

    // Set the URL for the POST request
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.example.com");

    // Set the callback function for writing received data
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

    // Set the POST data
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "key1=value1&key2=value2"); // more control than formadd

    std::string responseData;
    // Set the data pointer to be passed to the write callback
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

    //
    /*
        POST /upload HTTP/1.1
        Host: example.com
        Content-Type: application/x-www-form-urlencoded

        username=john_doe&file=<contents-of-example.txt>
    */
    CURL *curl = curl_easy_init();
    struct curl_httppost *post = NULL;
    struct curl_httppost *last = NULL;

    // Add a regular field
    curl_formadd(&post, &last,
                 CURLFORM_COPYNAME, "username",
                 CURLFORM_COPYCONTENTS, "john_doe",
                 CURLFORM_END);

    // Add a file upload field
    curl_formadd(&post, &last,
                 CURLFORM_COPYNAME, "file",
                 CURLFORM_FILE, "example.txt",
                 CURLFORM_END);

    // Set the form to the cURL handle
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);

    //
    const char *originalString = "Hello, world!";

    char *encodedString = curl_easy_escape(curl, originalString, -1);

    if (encodedString)
    {
        std::string decodedString = url_decode(encodedString);

        std::cout << "Encoded string: " << encodedString << std::endl;
        std::cout << "Decoded string: " << decodedString << std::endl;

        // Free the allocated memory
        curl_free(encodedString);
    }

    //
    //// Initialize the list (additional servers list)
    struct curl_slist *dnsServers = NULL;

    // Append DNS server addresses to the list
    dnsServers = curl_slist_append(dnsServers, "8.8.8.8");
    dnsServers = curl_slist_append(dnsServers, "8.8.4.4");

    // Use the list in a cURL request, e.g., set DNS servers
    curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, dnsServers);

    // Free the list when done
    curl_slist_free_all(dnsServers);

    //
    // Perform the GET request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
    }

    // Cleanup
    curl_easy_cleanup(curl);
    curl_formfree(post);
    curl_global_cleanup();

    return 0;
}

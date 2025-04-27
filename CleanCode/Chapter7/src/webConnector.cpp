#include "webConnector.h"

size_t WebConnector::response_callback(void *contents, size_t size, size_t nmemb, std::string *output)
{
    size_t total_size = size * nmemb;
    output->append(static_cast<char *>(contents), total_size);
    return total_size;
}

bool WebConnector::initialize_curl()
{
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    return curl != nullptr;
}

WebConnector::WebConnector()
{
    if (!initialize_curl())
    {
        throw WebConnectorException("Failed to initialize CURL.");
    }

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, response_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
}

WebConnector::~WebConnector()
{
    if (curl != nullptr)
    {
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

WebConnector &WebConnector::get_instance()
{
    static WebConnector instance;
    return instance;
}

std::string WebConnector::url_safe_encode(const std::string &url)
{
    char *encoded_url = curl_easy_escape(curl, url.c_str(), url.length());

    if (encoded_url == nullptr)
    {
        throw UrlEncodeException("Memory allocation error while encoding URL");
    }

    std::string encoded_url_str(encoded_url);

    curl_free(encoded_url);

    return encoded_url_str;
}

std::string WebConnector::send_request(const std::string &url)
{
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    response_data.clear();

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        throw RequestException("Request Error : " + std::string(curl_easy_strerror(res)));
    }

    return response_data;
}

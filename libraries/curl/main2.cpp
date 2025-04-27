
#include <iostream>
#include <tuple>
#include <sstream>
#include <curl/curl.h>
#include <json/json.h>

struct TumblrApiParameters
{
    std::string blogName;
    std::tuple<int, int> postRange;
};

class TumblrAPI
{
    std::string apiEndpoint;
    std::string responseData;
    CURL *curl = nullptr;

    static size_t responseCallback(void *responseBuffer, size_t singleElementSize, size_t elementCount, std::string *outputString)
    {
        size_t totalDataSize = singleElementSize * elementCount;
        outputString->append(static_cast<char *>(responseBuffer), totalDataSize);
        return totalDataSize;
    }

    void setUpRequestOptions()
    {
        curl_easy_setopt(curl, CURLOPT_URL, apiEndpoint.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, responseCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);
    }

    void initApi()
    {
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();

        if (curl == nullptr)
        {
            throw std::runtime_error("Failed to initialize curl");
        }

        setUpRequestOptions();
    }

    bool validJsonData(const size_t &jsonStartPosition, const size_t &jsonEndPosition)
    {
        return jsonStartPosition != std::string::npos && jsonEndPosition != std::string::npos;
    }

    std::string extractJsonData(const std::string &responseData)
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

public:
    TumblrAPI(const TumblrApiParameters &apiParams)
    {
        std::string blogName = apiParams.blogName;
        auto [postRangeStartIndex, postRangeEndIndex] = apiParams.postRange;
        int numberOfPostsToFetch = postRangeEndIndex - postRangeStartIndex + 1;

        apiEndpoint = "https://" + blogName + ".tumblr.com/api/read/json?type=photo&start=" + std::to_string(postRangeStartIndex - 1) + "&num=" + std::to_string(numberOfPostsToFetch);

        initApi();
    }

    std::string fetchData()
    {
        CURLcode responseStatus = curl_easy_perform(curl);

        if (responseStatus != CURLE_OK)
        {
            throw std::runtime_error("In API Call - " + std::string(curl_easy_strerror(responseStatus)) + "\t\t(Check Network Connection or API endpoint URL)");
        }

        std::string jsonData = extractJsonData(responseData);
        return jsonData;
    }

    ~TumblrAPI()
    {
        if (curl != nullptr)
        {
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
    }
};

std::tuple<int, int> extractPostRange(const std::string &input)
{
    int start, end;
    char delimiter;

    std::istringstream stream(input);
    stream >> start >> std::ws >> delimiter >> std::ws >> end;

    return std::make_tuple(start, end);
}

std::string modifyBlogName(const std::string &blogName)
{
    std::istringstream blogNameStream(blogName);
    std::string modifiedBlogName;
    std::string word;
    while (blogNameStream >> word)
    {
        modifiedBlogName += word;
    }
    return modifiedBlogName;
}

TumblrApiParameters getApiParameters()
{
    std::string blogName;
    std::string postRangeAsString;

    std::cout << "Enter Name of the Blog       : ";
    std::getline(std::cin, blogName);

    std::cout << "Enter Post Range (start-end) : ";
    std::getline(std::cin, postRangeAsString);

    blogName = modifyBlogName(blogName);
    std::tuple<int, int> postRange = extractPostRange(postRangeAsString);

    TumblrApiParameters apiParameters;
    apiParameters.blogName = blogName;
    apiParameters.postRange = postRange;

    return apiParameters;
}

Json::Value getJsonRoot(const std::string &jsonData)
{
    Json::Value jsonRoot;
    Json::Reader reader;

    if (!reader.parse(jsonData, jsonRoot))
    {
        throw std::runtime_error("Error parsing JSON content");
    }

    return jsonRoot;
}

void parseJsonData(const std::string &jsonData)
{
    std::cout << std::endl;
    Json::Value jsonRoot = getJsonRoot(jsonData);

    Json::Value tumbleLogData = jsonRoot["tumblelog"];

    std::string title = tumbleLogData["title"].asString();
    std::string description = tumbleLogData["description"].asString();
    std::string name = tumbleLogData["name"].asString();
    int total_posts = jsonRoot["posts-total"].asInt();

    std::cout << "Title: " << title << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Total Posts: " << total_posts << std::endl;

    if (total_posts == 0)
    {
        std::cerr << "\nSorry! There are no posts for given blog" << std::endl;
    }
    else
    {
        Json::Value posts = jsonRoot["posts"];
        int i = 1;
        std::cout << "\nPOSTS: " << std::endl;
        for (const Json::Value &post : posts)
        {
            std::string photoUrlValue1280p = post["photo-url-1280"].asString();
            if (!photoUrlValue1280p.empty())
            {
                std::cout << i << ": " << photoUrlValue1280p << std::endl;
            }
            else
            {
                std::cerr << "Error: 'photo url' not found for a post " << i << std::endl;
            }
            i++;
        }
    }
}

void viewBlogPosts()
{
    TumblrApiParameters apiParameters = getApiParameters();

    TumblrAPI api(apiParameters);

    std::string jsonData = api.fetchData();

    parseJsonData(jsonData);
}

int main()
{
    try
    {
        viewBlogPosts();
    }
    catch (std::exception &e)
    {
        std::cerr << "\nError: " << e.what() << std::endl;
    }

    return 0;
}
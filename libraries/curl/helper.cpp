#include <iostream>
#include <json/json.h>
#include <curl/curl.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output)
{
    size_t total_size = size * nmemb;
    output->append(static_cast<char *>(contents), total_size);
    return total_size;
}

int main()
{
    std::string api_endpoint = "https://good.tumblr.com/api/read/json?type=photo&start=0&num=2";
    std::string response_data;

    CURL *curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, api_endpoint.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            std::cerr << "Error during request: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            size_t pos_start = response_data.find("{");
            size_t pos_end = response_data.find("};", pos_start);

            if (pos_start != std::string::npos && pos_end != std::string::npos)
            {
                std::string json_content = response_data.substr(pos_start, pos_end - pos_start + 1);

                Json::Value root;
                Json::Reader reader;
                if (reader.parse(json_content, root))
                {
                    Json::Value tumblelog_data = root["tumblelog"];
                    std::string title = tumblelog_data["title"].asString();
                    std::string description = tumblelog_data["description"].asString();
                    std::string name = tumblelog_data["name"].asString();

                    std::cout << "Title: " << title << std::endl;
                    std::cout << "Description: " << description << std::endl;
                    std::cout << "Name: " << name << std::endl;

                    int total_posts = root["posts-total"].asInt();
                    std::cout << "Total Posts: " << total_posts << std::endl;

                    Json::Value posts = root["posts"];
                    int i = 0;
                    for (const Json::Value &post : posts)
                    {
                        std::string photo_url_1280_value = post["photo-url-1280"].asString();
                        if (!photo_url_1280_value.empty())
                        {
                            std::cout << i << ": " << photo_url_1280_value << std::endl;
                            i++;
                        }
                        else
                        {
                            std::cerr << "Error: 'photo-url-1280' not found for a post." << std::endl;
                        }
                    }
                }
                else
                {
                    std::cerr << "Error parsing JSON content." << std::endl;
                }
            }
            else
            {
                std::cerr << "Error: Failed to extract relevant JSON content." << std::endl;
            }
        }

        curl_easy_cleanup(curl);
    }
    else
    {
        std::cerr << "Failed to initialize CURL." << std::endl;
    }

    return 0;
}

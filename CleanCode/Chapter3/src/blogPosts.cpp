/**
 * @file blogPosts.cpp
 * @brief Implementation file for interacting with Tumblr blog posts.
 *
 * This file defines functions related to retrieving and displaying Tumblr blog posts.
 * It includes functions for obtaining user input, making API calls, parsing JSON data,
 * and displaying relevant information about the blog and its posts.
 */

#include "blogPosts.h"
#include <iostream>
#include <sstream>

void viewBlogPostsInfo()
{
    TumblrApiParameters apiParameters = getApiParameters();
    TumblrAPI api(apiParameters);
    std::string jsonData = api.fetchData();
    diaplayBlogInfo(jsonData);
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

std::tuple<int, int> extractPostRange(const std::string &input)
{
    int start, end;
    char delimiter;

    std::istringstream stream(input);
    stream >> start >> std::ws >> delimiter >> std::ws >> end;

    return std::make_tuple(start, end);
}

void diaplayBlogInfo(const std::string &jsonData)
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

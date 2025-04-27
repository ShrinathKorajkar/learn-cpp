/**
 * @file blogPosts.h
 * @brief This file contains declarations for functions related to viewing Tumblr blog posts.
 *
 * The functions declared in this file provide functionalities for obtaining API parameters,
 * fetching and parsing JSON data, and displaying relevant information about Tumblr blog posts.
 *
 * @section Dependencies
 *
 * - JsonCpp: https://github.com/open-source-parsers/jsoncpp
 */

#ifndef BLOG_POSTS_H
#define BLOG_POSTS_H

#include "tumblrAPI.h"
#include <json/json.h>
#include <string>
#include <tuple>

void viewBlogPostsInfo();

/**
 * @brief Obtains user input for Tumblr API parameters.
 * @return A TumblrApiParameters struct containing user-specified parameters.
 */
TumblrApiParameters getApiParameters();

/**
 * @brief Displays relevant information about Tumblr blog posts.
 * @param jsonData A string containing the JSON data retrieved from the Tumblr API.
 */
void diaplayBlogInfo(const std::string &jsonData);

/**
 * @brief Modifies the blog name by removing spaces.
 * @param blogName The original blog name.
 * @return A string with spaces removed from the blog name.
 */
std::string modifyBlogName(const std::string &blogName);

/**
 * @brief Extracts post range values from the input string.
 * @param input A string containing the post range in the format "start-end".
 * @return A tuple of integers representing the start and end values of the post range.
 */
std::tuple<int, int> extractPostRange(const std::string &input);

/**
 * @brief Retrieves the root JSON value from the provided JSON data string.
 * @param jsonData A string containing the JSON data.
 * @return A Json::Value representing the root of the JSON data.
 */
Json::Value getJsonRoot(const std::string &jsonData);

#endif

#include "blogPosts.h"
#include <iostream>

int main()
{
    try
    {
        viewBlogPostsInfo();
    }
    catch (std::exception &e)
    {
        std::cerr << "\nError: " << e.what() << std::endl;
    }

    return 0;
}
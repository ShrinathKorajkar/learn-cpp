#include <stdio.h>
#include <curl/curl.h>

int main()
{
    // Initialize cURL globally
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create multi handle
    CURLM *multi_handle = curl_multi_init();
    if (!multi_handle)
    {
        fprintf(stderr, "curl_multi_init failed\n");
        return 1;
    }

    // Create easy handles for two transfers
    CURL *easy_handle1 = curl_easy_init();
    CURL *easy_handle2 = curl_easy_init();

    // Set options for the two transfers (URLs, callbacks, etc.)

    // Add the handles to the multi handle
    CURLMcode res1 = curl_multi_add_handle(multi_handle, easy_handle1);
    CURLMcode res2 = curl_multi_add_handle(multi_handle, easy_handle2);

    if (res1 != CURLM_OK || res2 != CURLM_OK)
    {
        fprintf(stderr, "curl_multi_add_handle failed\n");
        return 1;
    }

    int still_running;

    // Perform transfers in a loop until all are completed
    do
    {
        res1 = curl_multi_perform(multi_handle, &still_running);
        if (res1 != CURLM_OK)
        {
            fprintf(stderr, "curl_multi_perform failed\n");
            return 1;
        }

        // Perform any other tasks or wait for activity
        // (e.g., use select(), poll(), or another mechanism)

    } while (still_running > 0);

    // Clean up
    curl_multi_cleanup(multi_handle);
    curl_easy_cleanup(easy_handle1);
    curl_easy_cleanup(easy_handle2);

    // Cleanup cURL globally
    curl_global_cleanup();

    return 0;
}

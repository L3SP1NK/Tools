#include <stdio.h>
#include <curl/curl.h>

#define POOL_SIZE 5

int main() {
    CURL *curl_handles[POOL_SIZE];
    CURLM *multi_handle;
    int i, still_running;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    // Create a multi-handle for managing multiple transfers
    multi_handle = curl_multi_init();

    // Create and add individual easy-handles to the multi-handle
    for (i = 0; i < POOL_SIZE; i++) {
        curl_handles[i] = curl_easy_init();
        if (!curl_handles[i]) {
            fprintf(stderr, "Failed to initialize libcurl for handle %d.\n", i);
            return 1;
        }

        // Set the common request options for all handles
        curl_easy_setopt(curl_handles[i], CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl_handles[i], CURLOPT_URL, "https://large-text-to-speech.p.rapidapi.com/tts");

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "X-RapidAPI-Key: 4e3143ad1amsh30ced5bec04c0c7p1fdf6ejsned38bc14007c");
        headers = curl_slist_append(headers, "X-RapidAPI-Host: large-text-to-speech.p.rapidapi.com");
        curl_easy_setopt(curl_handles[i], CURLOPT_HTTPHEADER, headers);

        const char *data = "{\n    \"text\": \"Perfection is achieved not when there is nothing more to add, but rather when there is nothing more to take away.\"\n}";
        curl_easy_setopt(curl_handles[i], CURLOPT_POSTFIELDS, data);

        // Add the handle to the multi-handle
        curl_multi_add_handle(multi_handle, curl_handles[i]);
    }

    // Perform transfers
    do {
        curl_multi_perform(multi_handle, &still_running);
    } while (still_running);

    // Clean up
    for (i = 0; i < POOL_SIZE; i++) {
        curl_multi_remove_handle(multi_handle, curl_handles[i]);
        curl_easy_cleanup(curl_handles[i]);
    }

    curl_multi_cleanup(multi_handle);
    curl_global_cleanup();

    return 0;
}

#include <curl/curl.h> 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

static size_t callback(void *data, size_t size, size_t nmemb, void *clicentp)
{
    size_t realsize = size *nmemb;

    /*
    struct memory *mem (struct memory *)clientp;

    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    */

    return realsize;
}

void *fetch(CURL *curl, CURLcode response, void *arg)
{
    printf("[ thread => fetch ]\n");

    char *rss = "https://www.thecocktaildb.com/api/json/v1/1/search.php?s=gin";

    curl = curl_easy_init();

    if(curl == NULL)
        return EXIT_FAILURE;

    curl_easy_setopt(curl, CURLOPT_URL, rss);
    //    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    response = curl_easy_perform(curl);

    if(response != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(response));

    curl_easy_cleanup(curl);
}

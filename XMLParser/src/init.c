#include <curl/curl.h> 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

void init(CURL *curl, CURLcode response)
{
    curl = curl_easy_init();

    if(curl == NULL)
        return EXIT_FAILURE;

    curl_easy_setopt(curl, CURLOPT_URL, "https://www.thecocktaildb.com/api/json/v1/1/search.php?s=margarita");

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    response = curl_easy_perform(curl);

    if(response != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(response));

    curl_easy_cleanup(curl);
}

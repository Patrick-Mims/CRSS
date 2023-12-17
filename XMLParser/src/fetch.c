#include <curl/curl.h> 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
/**
 * ptr always points to the delivered data 
 * and the size of the data is nmemb and size is always 1
 */

struct URL *alloc_mem()
{
    struct URL *mem = NULL;

    if((mem = malloc(sizeof(struct URL *))) == NULL) 
        exit(EXIT_FAILURE);

    return mem;
}

static size_t callback(void *ptr, size_t size, size_t nmemb, void *data)
{
    size_t realsize = size * nmemb;

    struct MEMORY *mem = (struct memory *)data;

    char *item = realloc(mem->response, mem->size + realsize + 1);

    if(!item)
        exit(EXIT_FAILURE);

    mem->response = item;
    memcpy(&(mem->response[mem->size]), ptr, realsize);
    mem->size += realsize; 
    mem->response[mem->size] = 0;

    return realsize;
}

void *fetch(CURL *curl, CURLcode response, void *arg)
{
    printf("[ thread => fetch ]\n");

    struct URL *url = alloc_mem();
    struct MEMORY chunk = {0};
    chunk.response = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);

    url->url = "https://www.thecocktaildb.com/api/json/v1/1/search.php?s=gin";

    curl = curl_easy_init();

    if(curl == NULL)
        return EXIT_FAILURE;

    curl_easy_setopt(curl, CURLOPT_URL, url->url);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl--agent/1.0");

    if(curl_easy_perform(curl) != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(response));
    else 
        printf("%lu bytes retrieved\n", (unsigned long)chunk.size);

    free(url);
    curl_easy_cleanup(curl);
    free(chunk.response);
    curl_global_cleanup();
}

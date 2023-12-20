#include <curl/curl.h> 
#include <json-c/json.h>
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
    size_t new_size = size * nmemb;

    struct MEMORY *mem = (struct memory *)data;

    char *item = realloc(mem->response, mem->size + new_size + 1);

    if(!item)
        exit(EXIT_FAILURE);

    mem->response = item;
    memcpy(&(mem->response[mem->size]), ptr, new_size);
    mem->size += new_size;
    mem->response[mem->size] = 0;

    return new_size;
}

void *fetch_json(CURL *curl, CURLcode response, void *arg)
{
    struct URL *u = (struct memory *)arg;
    u = alloc_mem();

    struct MEMORY chunk = {0};
    chunk.response = malloc(1);
    chunk.size = 0;

    u->rss = "https://www.thecocktaildb.com/api/json/v1/1/search.php?s=vodka";
    u->file = "drinks.json";

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if(curl == NULL)
        return (void *) EXIT_FAILURE;

    curl_easy_setopt(curl, CURLOPT_URL, u->rss);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl--agent/1.0");

    if(curl_easy_perform(curl) != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(response));
    } else {
        json_object *list, *idDrink, *strDrink, *strCategory, *strGlass;

        json_object *root = json_tokener_parse(chunk.response);
        json_object *drinks = json_object_object_get(root, "drinks");

        size_t objects = json_object_array_length(drinks);

        printf("[ JSON STRING Pretty ] => %s", 
                json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));

        for(int i = 0; i < objects; i++)
        {
            list = json_object_array_get_idx(drinks, i);

            printf("%s\n%s\n%s\n%s\n\n", 
                json_object_get_string(json_object_object_get(list, "idDrink")),
                json_object_get_string(json_object_object_get(list, "strDrink")),
                json_object_get_string(json_object_object_get(list, "strCategory")), 
                json_object_get_string(json_object_object_get(list, "strGlass")));
        }

        json_object_put(root);
    }

    free(u);
    curl_easy_cleanup(curl);
    free(chunk.response);
    curl_global_cleanup();
}

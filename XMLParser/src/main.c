#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include <curl/curl.h> 

int main(void)
{
    char *url = "";
    CURL *curl = NULL;

    curl = curl_easy_init();

    if(curl == NULL)
        return EXIT_FAILURE;

    curl_easy_setopt(curl, CURLOPT_URL, );

    curl_easy_cleanup(curl);

    printf("Good Evening\n");

    return 0;  
}

/*
 * 1. Download an xml rss feed to a directory.
 * 2. Open, read, parse and close the file.
 */

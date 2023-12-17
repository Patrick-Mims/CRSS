#include <curl/curl.h> 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

int main(void)
{
    CURL *curl = NULL;
    CURLcode response;

    int rc; 
    pthread_t thread;
    void *result;

    struct URL *url = alloc_mem();

    // pass a structure to the thread
    rc = pthread_create(&thread, NULL, fetch, &url);

    printf("[ main => rc ] => %d\n", rc);
    printf("[ main value ] => ", url->rss);

    rc = pthread_join(thread, &result);

    return 0;  
}

/* Download an xml rss feed to a directory in a thread.
 * Files: 
 * main.c
 * fetch.c - fetch will be a thread
 *
 * Todo 12.17.23
 * 1. Write data to a file
 * */

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

    rc = pthread_create(&thread, NULL, fetch, "White Woman\n");

    printf("[ main => rc ] => %d\n", rc);

    rc = pthread_join(thread, &result);

    return 0;  
}

/*
 * Download an xml rss feed to a directory in a thread.
 * Files: 
 * main.c
 * fetch.c - fetch will be a thread
 *
 * 1. setup curl
 * 2. make request 
 * 3. save xml
 * 
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * 2. Open, read, parse and close the file.
 */

#include <curl/curl.h> 
#include <json-c/json.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <pcap/pcap.h>

#include "parser.h"

void find_network_device()
{
    char *device;
    char error_buffer[PCAP_ERRBUF_SIZE];

    device = pcap_lookupdev(error_buffer);

    if(device == NULL)
    {
        puts("Error");
        return 1;
    }

    printf("[ Device ] -> %s\n", device);
}

int main(void)
{
    CURL *curl = NULL;
    CURLcode response;

    int rc; 
    pthread_t write_thread, parse_thread;
    void *result;

    struct URL *url = alloc_mem();

    rc = pthread_create(&write_thread, NULL, fetch_json, &url);

    printf("[ main => rc ] => %d\n", rc);
    printf("[ main value ] => ", url->rss);

    rc = pthread_join(write_thread, &result);

    printf("[ main => rc ] => %d\n", rc);
    printf("[ main value ] => ", url->rss);

    find_network_device();

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

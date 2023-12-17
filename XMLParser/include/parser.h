#ifndef PARSER_H
#define PARSER_H

struct MEMORY
{
    char *response;
    size_t size;
};

struct URL 
{
    char *url;
};

struct URL *alloc_mem();
void *fetch(CURL *, CURLcode, void *);

#endif

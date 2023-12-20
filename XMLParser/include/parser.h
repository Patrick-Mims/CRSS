#ifndef PARSER_H
#define PARSER_H

struct MEMORY
{
    char *response;
    size_t size;
};

struct URL 
{
    char *rss;
    char *file;
};

struct URL *alloc_mem();

void *fetch_json(CURL *, CURLcode, void *);
// void *parse_json(void *);

#endif

#ifndef PARSER_H
#define PARSER_H

struct memory 
{
    char *response;
    size_t size;
};

void request_feed();
void *fetch(CURL *, CURLcode, void *);

#endif

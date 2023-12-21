#include <curl/curl.h> 
#include <json-c/json.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "list.h"

struct Node *create_node()
{
    struct Node *node = NULL;

    if((node = malloc(sizeof(struct Node *))) == NULL) exit(EXIT_FAILURE);

    return node;
}

void insert(struct Node **list, char *data)
{
    struct Node *node = create_node();

    node->data = data;
    node->next = *list;

    *list = node;
}

void display(struct Node *list)
{
    for(; list != NULL; list = list->next)
    {
        printf("[ display ] => %s\n", list->data);
    }
}

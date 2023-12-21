#ifndef LIST_H
#define LIST_H

struct Node
{
    char *data;
    /*
    char *tags;
    char *category;
    char *glass;
    char *instructions;
    */

    struct Node *next;
};

struct Node *create_node();
void display(struct Node *);
void insert(struct Node **, char *);

#endif

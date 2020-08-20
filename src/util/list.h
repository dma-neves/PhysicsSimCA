#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct _Node Node;

struct _Node
{
    void* element;
    Node* next;
    Node* prev;
};

typedef struct _List
{
    Node* head;
    Node* tail;
    size_t elemSize;
} List;

void list_init(List* list, size_t elemSize);
Node* list_find(List* list, void* element);
void list_add(List* list, void* element);
void* list_rem(List* list, Node* node);
void list_clear(List* list);

#endif
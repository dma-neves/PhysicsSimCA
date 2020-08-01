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

void initList(List* list, size_t elemSize);
Node* find(List* list, void* element);
void add(List* list, void* element);
void* rem(List* list, Node* node);
void clearList(List* list);

#endif
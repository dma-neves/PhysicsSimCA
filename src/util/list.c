#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "list.h"

void list_init(List* list, size_t elemSize)
{
    list->head = NULL;
    list->tail = NULL;
    list->elemSize = elemSize;
}

void list_add(List* list, void* element)
{
    if(list->head == NULL)
    {
        list->head = malloc(sizeof(Node));
        list->head->next = NULL;
        list->head->prev = NULL;
        list->head->element = element;
        list->tail = list->head;
    }
    else
    {
        Node* newNode = malloc(sizeof(Node));
        newNode->element = element;
        newNode->next = NULL;
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    
}

Node* list_find(List* list, void* element)
{
    Node* curNode = list->head;
    while(curNode != NULL && curNode->element != element) curNode = curNode->next;

    if(curNode == NULL || curNode->element != element) printf("Error: Invalid list find\n");

    return curNode;
}

void* list_rem(List* list, Node* node)
{  
    if(node == list->head)
    {
        list->head = node->next;
        if(list->head != NULL) list->head->prev = NULL;
    }
    else if(node == list->tail)
    {
        list->tail = node->prev;
        if(list->tail != NULL) list->tail->next = NULL;
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    void* elem =  node->element;
    free(node);
    return elem;
}

void list_clear(List* list)
{
    Node* curNode = list->head;
    while(curNode != NULL)
    {
        free(curNode->element);
        Node* aux = curNode;
        curNode = curNode->next;
        free(aux);
    }

    list->head = NULL;
    list->tail = NULL;
}
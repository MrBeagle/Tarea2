#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct ListNode {
    void *data;
    struct ListNode *next;
} ListNode;

struct List {
    ListNode *head;
    ListNode *tail;
    ListNode *current;
};

List *createList() {
    List *list = (List *)malloc(sizeof(List));
    list->head = list->tail = list->current = NULL;
    return list;
}

void pushBack(List *list, void *data) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->data = data;
    node->next = NULL;
    if (list->tail) {
        list->tail->next = node;
    } else {
        list->head = node;
    }
    list->tail = node;
}

void *firstList(List *list) {
    list->current = list->head;
    return list->current ? list->current->data : NULL;
}

void *nextList(List *list) {
    if (list->current) {
        list->current = list->current->next;
    }
    return list->current ? list->current->data : NULL;
}

void popFront(List *lista) {
    if (lista == NULL || lista->head == NULL) return;

    ListNode *temp = lista->head;
    lista->head = lista->head->next;
    free(temp);
}
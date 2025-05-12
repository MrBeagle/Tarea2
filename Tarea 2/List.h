#ifndef LIST_H
#define LIST_H

typedef struct List List;

List *createList();
void pushBack(List *list, void *data);
void *firstList(List *list);
void *nextList(List *list);
void popFront(List *lista);

#endif
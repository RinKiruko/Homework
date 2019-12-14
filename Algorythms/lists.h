#ifndef LISTS_H
#define LISTS_H

#include <stdbool.h>

int lists_1();
int lists_2();
int lists_3();

typedef struct list_node {
    int value, index;
    int len;
    struct list_node *next, *prev, *head;
} list_node;

list_node * initListNode(int value);
list_node * initRandomList(int number, int MAXIMUM);

void appendElement(list_node *to, list_node *element);

list_node * popElement(list_node *head, list_node *element);

list_node * getElement(list_node *from, int index);

void printList(list_node *list);

void printListNode(list_node *node, char tail);

bool checkIn(list_node *head, list_node *element);

void sortList(list_node * list_head);

void swapListNode(list_node *firstElement, list_node *secondElement);

list_node * intersection(list_node *firstHead, list_node *secondHead);

#endif /* LISTS_H */


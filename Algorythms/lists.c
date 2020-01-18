#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "lists.h"

list_node *initListNode(int value) {
    list_node *newElement;
    newElement = malloc(sizeof(list_node));
    newElement->next = NULL;
    newElement->prev = NULL;
    newElement->head = newElement;

    newElement->value = value;
    newElement->index = 0;
    newElement->len = 1;
    return newElement;
}

list_node *_init_list(int number) {
    list_node *newElement, *lastElement, *firstElement = initListNode(0);

    lastElement = firstElement;
    for (int i = 2; i <= number; i++) {
        newElement = initListNode(0);
        appendElement(lastElement, newElement);
        lastElement = newElement;
    }

    return firstElement;
}

list_node *initList(int number, const int *value) {
    list_node *list = _init_list(number);

    if (value != NULL) {
        list_node *element = list;
        for (int i = 0; i < list->len; i++) {
            element->value = *value;
            element = element->next;
        }
    }

    return list;
}

list_node *initRangeList(int number, int from) {
    list_node *list = _init_list(number);
    list_node *element = list;

    int value = from;
    for (int i = 0; i < list->len; i++) {
        element->value = value++;
        element = element->next;
    }

    return list;
}

list_node *initRandomList(int number, int MAXIMUM) {
    list_node *list = _init_list(number);

    list_node *element = list;
    for (int i = 0; i < list->len; i++) {
        element->value = random() % MAXIMUM;
        element = element->next;
    }

    return list;
}

void _chainElements(list_node *left, list_node *right) {
    left->next = right;
    right->prev = left;
}

list_node *_deleteElement(list_node *element) {
    list_node *previouslyELement = element->prev;
    list_node *nextElement = element->next;
    if (previouslyELement != NULL && nextElement != NULL) {
        _chainElements(previouslyELement, nextElement);
    }
    return element;
}

list_node *popElement(list_node *element) {
    list_node *startElementRewriteIndex = element->prev;
    list_node *_listHead = element->head;

    list_node *deletedElement = _deleteElement(element);

    _listHead->len--;

    for (list_node *el = startElementRewriteIndex->next; el != NULL; el = el->next) {
        el->index--;
    }

    return deletedElement;
}

void appendElement(list_node *to, list_node *element) {
    if (to == NULL || element == NULL) {
        return;
    }

    _chainElements(to, element);
    element->head = to->head;
    element->index = to->index + 1;

    to->head->len++;
}

list_node *getElement(list_node *from, int index) {
    int i = 0;
    list_node *element = from;
    while (element != NULL && i <= index) {
        if (i == index) {
            return element;
        }
        element = element->next;
        i++;
    }
    return NULL;
}

bool checkIn(list_node *checkingElement, list_node *headOfList) {
    if (checkingElement == NULL || headOfList == NULL) {
        return false;
    }

    list_node *current = headOfList;
    while (current != NULL) {
        if (current->value == checkingElement->value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

list_node *intersection(list_node *firstHead, list_node *secondHead) {
    list_node *resultHead, *resultElement, *currentElement = firstHead;

    while (currentElement != NULL) {
        if (checkIn(currentElement, secondHead) && !checkIn(currentElement, resultHead)) {
            if (resultHead == NULL) {
                resultHead = initListNode(currentElement->value);
                resultElement = resultHead;
            } else {
                list_node *temp = initListNode(currentElement->value);
                appendElement(resultElement, temp);
                resultElement = temp;
            }
        }
        currentElement = currentElement->next;
    }

    return resultHead;
}

void printList(list_node *listHead) {
    if (listHead == NULL) {
        printf("empty\n");
        return;
    }
    list_node *element = listHead;

    while (element != NULL) {
        printf("%d ", element->value);
        element = element->next;
    }
    printf("\n");
}

void printListNode(list_node *node, char tail) {
    if (node == NULL) {
        printf("nil%c", tail);
    } else {
        printf("%d%c", node->value, tail);
    }
}

void sortList(list_node *listHead) { // bubble sorting
    list_node *element = listHead;

    if (element->next == NULL || element == NULL) {
        return;
    }
    while (element != NULL) {
        list_node *internalElement = element->next;
        while (internalElement != NULL) {
            if (element->value > internalElement->value) {
                swapListNode(element, internalElement);
            }
            internalElement = internalElement->next;
        }

        element = element->next;
    }
}

void swapListNode(list_node *firstElement, list_node *secondElement) {
    int temp = firstElement->value;
    firstElement->value = secondElement->value;
    secondElement->value = temp;
}

int lists_1() {
    list_node *firstElement = initListNode(random() % 100);
    firstElement->index = 0;

    printf("insert N\n");
    int n;
    scanf("%d", &n);

    list_node *newElement, *toElement = firstElement;
    list_node *min = firstElement, *max = firstElement;
    for (int i = 0; i < n; i++) {
        newElement = initListNode(random() % 100);
        appendElement(toElement, newElement);
        toElement = newElement;

        min = newElement->value <= min->value ? newElement : min;
        max = newElement->value >= max->value ? newElement : max;
    }

    list_node *element = firstElement;
    while (element->next != NULL) {
        printf("self: %p , index: %d , value: %d \n", element, element->index, element->value);
        element = element->next;
    }

    element = max;
    while (element != min->prev) {
        printf("%d \n", element->value);
        element = element->prev;
    }
    return (EXIT_SUCCESS);
}

int lists_2() {
    int n1, n2, max_num = 1000;

    FILE *input = fopen("input.txt", "r");

    fscanf(input, "%d", &n1);
    fscanf(input, "%d", &n2);
    fscanf(input, "%d", &max_num);

    fclose(input);

    list_node *firstHead = initRandomList(n1, max_num), *secondHead = initRandomList(n2, max_num);
    printList(firstHead);
    printList(secondHead);

    list_node *commonElementsHead = intersection(firstHead, secondHead);
    sortList(commonElementsHead);
    printList(commonElementsHead);
    return (EXIT_SUCCESS);
}

int lists_3() {
    int n = 6, m = 15;
//    FILE *input = fopen("input.txt", "r");
//
//    fscanf(input, "%d", &n);
//    fscanf(input, "%d", &m);
//
//    fclose(input);

    list_node *group = initRangeList(n,1);
    printList(group);

    list_node *firstElement = group;
    list_node *lastElement = getElement(group, group->len - 1);

    _chainElements(lastElement, firstElement);
    int counter = 1;

    list_node *element = group->head;

    while (element->next != element) {
        if (counter == m) {
            list_node *deletedElement = _deleteElement(element);
            element = deletedElement->next;
            counter = 1;

            printf("was deleted %d\n", deletedElement->value);
        } else {
            counter++;
            element = element->next;
        }
    }
    printf("%d", element->value);

    return (EXIT_SUCCESS);
}
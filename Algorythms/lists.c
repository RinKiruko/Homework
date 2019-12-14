#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "lists.h"

list_node * initListNode(int value) {
    list_node *newElement;
    newElement = malloc(sizeof (list_node));
    newElement->next = NULL;
    newElement->prev = NULL;
    newElement->head = newElement;

    newElement->value = value;
    newElement->index = 0;
    newElement->len = 1;
    return newElement;
}

list_node * popElement(list_node *head, list_node *element) {
    list_node *temp = element, *elementForRewritingIndex = element->prev;
    // chain
    element->prev->next = element->next;
    element->next->prev = element->prev;

    for (list_node *el = elementForRewritingIndex->next; el != NULL; el = el->next) {
        el->index = el->prev->index + 1;
    }
    head->len--;
    return temp;
}

void appendElement(list_node *to, list_node *element) {
    if (to == NULL || element == NULL) {
        return;
    }

    element->head = to->head;
    element->prev = to;
    element->index = to->index + 1;

    to->next = element;
    to->head->len++;
}

list_node * getElement(list_node *from, int index) {
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

list_node * initRandomList(int number, int MAXIMUM) {
    list_node *newElement, *element, *firstElement = initListNode(random() % MAXIMUM);

    // cause firstElement also was limited
    number--;

    element = firstElement;
    while (number > 0) {
        newElement = initListNode(random() % MAXIMUM);
        appendElement(element, newElement);
        element = newElement;

        number--;
    }

    return firstElement;
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

list_node * intersection(list_node *firstHead, list_node *secondHead) {
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
    int n1, n2, max_num;
    printf("MaxRandomNumber=");
    scanf("%d", &max_num);
    printf("len(L1)=");
    scanf("%d", &n1);
    printf("len(L2)=");
    scanf("%d", &n2);

    list_node *firstHead = initRandomList(n1, max_num), *secondHead = initRandomList(n2, max_num);
    printList(firstHead);
    printList(secondHead);

    list_node *commonElementsHead = intersection(firstHead, secondHead);
    sortList(commonElementsHead);
    printList(commonElementsHead);
    return (EXIT_SUCCESS);
}

int lists_3() {
    int n, m;
//    printf("N=");
//    scanf("%d", &n);
//    printf("M=");
//    scanf("%d", &m);

    n = 5, m = 15;
    list_node *group = initRandomList(n, 100);
    printList(group);
    
    list_node *lastElement = getElement(group, group->len - 1);
    printListNode(getElement(group, 6), ' ');
    // chain elements
    group->prev = lastElement;
    lastElement->next = group;

    list_node *headOfGroup = group, *elementToPop;
    int groupLen = group->len, indexToPop = 0;
    while (groupLen > 1) {
        int indexToPop = (m - 1) % groupLen;
        elementToPop = getElement(headOfGroup, indexToPop);

        headOfGroup = getElement(headOfGroup, indexToPop+1);
        popElement(group, getElement(group, indexToPop));
        groupLen--;

    }
    return (EXIT_SUCCESS);
}
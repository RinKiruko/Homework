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

list_node *_initList(int number) {
    list_node *newElement, *firstElement = initListNode(0);

    for (int i = 2; i <= number; i++) {
        newElement = initListNode(0);
        _appendElement(firstElement, newElement);
    }

    return firstElement;
}

void _appendElement(list_node *to, list_node *element) {
    if (to == NULL) {
        return;
    }
    list_node *lastNode = to;
    while (lastNode->next != NULL)
        lastNode = lastNode->next;

    _chainElements(lastNode, element);
    element->head = to;
    element->index = lastNode->index + 1;

    to->head->len++;
}

list_node *initList(int number, int *value) {
    list_node *list = _initList(number);

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
    list_node *list = _initList(number);
    list_node *element = list;

    int value = from;
    for (int i = 0; i < list->len; i++) {
        element->value = value++;
        element = element->next;
    }

    return list;
}

list_node *initRandomList(int number, int MAXIMUM) {
    list_node *list = _initList(number);

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

list_node *union_(list_node *firstHead, list_node *secondHead) {
    list_node *element = firstHead->next, *resultHead = initList(1, &(firstHead->value));

    //first list
    while (element != NULL) {
        if (!checkIn(element, resultHead)) {
            _appendElement(resultHead, initListNode(element->value));
        }
        element = element->next;
    }

    //second list
    element = secondHead;
    while (element != NULL) {
        if (!checkIn(element, resultHead)) {
            _appendElement(resultHead, initListNode(element->value));
        }
        element = element->next;
    }
    return resultHead;
};

//list_node *intersection(list_node *firstHead, list_node *secondHead) {
//    list_node *resultHead, *resultElement, *currentElement = firstHead;
//
//    while (currentElement != NULL) {
//        if (checkIn(currentElement, secondHead) && !checkIn(currentElement, resultHead)) {
//            if (resultHead == NULL) {
//                resultHead = initListNode(currentElement->value);
//                resultElement = resultHead;
//            } else {
//                list_node *temp = initListNode(currentElement->value);
//                _appendElement(resultElement, temp);
//                resultElement = temp;
//            }
//        }
//        currentElement = currentElement->ahead;
//    }
//
//    return resultHead;
//}

list_node *maxInList(list_node *list) {
    int max = list->head->value;

    list_node *result = list->head, *element = list->head->next;
    while (element != NULL) {
        if (element->value > max) {
            max = element->value;
            result = element;
        }
        element = element->next;
    }
    return result;
}

list_node *minInList(list_node *list) {
    int min = list->head->value;

    list_node *result = list->head, *element = list->head->next;
    while (element != NULL) {
        if (element->value < min) {
            min = element->value;
            result = element;
        }
        element = element->next;
    }
    return result;
}

void printList(list_node *listHead, FILE *to) {
    if (to == NULL) {
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
    } else {
        if (listHead == NULL) {
            fprintf(to, "empty\n");
            return;
        }
        list_node *element = listHead;

        while (element != NULL) {
            fprintf(to, "%d ", element->value);
            element = element->next;
        }
        fprintf(to, "\n");
    }

}

void printListNode(list_node *node, char tail) {
    if (node == NULL) {
        printf("nil%c", tail);
    } else {
        printf("%d%c", node->value, tail);
    }
}

void sortList(list_node *list) { // bubble sorting
    list_node *head = list->head;

    if (head->next == NULL || head == NULL) {
        return;
    }
    for (list_node *element = head; element->next != NULL; element=element->next) {
        for (list_node *internalElement = element->next; internalElement->next !=NULL; internalElement=internalElement->next) {
            if (element->value > internalElement->value)
                swapListNode(element, internalElement);
        }
    }
}

void swapListNode(list_node *firstElement, list_node *secondElement) {
    int temp = firstElement->value;
    firstElement->value = secondElement->value;
    secondElement->value = temp;
}

int lists_1() {
    FILE *input = fopen("/home/hokage/CLionProjects/Homework/Algorythms/input.txt", "r");

    int n, max_num = 100;
    fscanf(input, "%d", &n);
    fscanf(input, "%d", &max_num);

    list_node *list = initRandomList(n, (int) rand() % max_num);
    _appendElement(list, initListNode(0));
    list_node *minElement = minInList(list), *maxElement = maxInList(list);

    FILE *output = fopen("/home/hokage/CLionProjects/Homework/Algorythms/output.txt", "w");
    printList(list, output);

    if (minElement < maxElement) {
        for (list_node *element = maxElement; element != minElement; element = element->prev)
            fprintf(output, "%d ", element->value);
    } else {
        for (list_node *element = minElement; element != maxElement; element = element->prev)
            fprintf(output, "%d ", element->value);
    }

    fclose(output);

    return (EXIT_SUCCESS);
}

int lists_2() {
    int n1, n2, max_num = 1000;

    FILE *input = fopen("/home/hokage/CLionProjects/Homework/Algorythms/input.txt", "r");

    fscanf(input, "%d", &n1);
    fscanf(input, "%d", &n2);
    fscanf(input, "%d", &max_num);

    fclose(input);

    list_node *firstHead, *secondHead;
    firstHead = initRandomList(n1, max_num);
    secondHead = initRandomList(n2, max_num);

    FILE *output = fopen("/home/hokage/CLionProjects/Homework/Algorythms/output.txt", "w");

    printList(firstHead, output);
    printList(secondHead, output);

    list_node *unionHead = union_(firstHead, secondHead);
    sortList(unionHead);
    printList(unionHead, output);

    fclose(output);

    return (EXIT_SUCCESS);
}

int lists_3() {
    int n, m;
    FILE *input = fopen("/home/hokage/CLionProjects/Homework/Algorythms/input.txt", "r");

    fscanf(input, "%d", &n);
    fscanf(input, "%d", &m);

    fclose(input);

    list_node *group = initRangeList(n, 1);

    FILE *output = fopen("/home/hokage/CLionProjects/Homework/Algorythms/output.txt", "w");
    printList(group, output);

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

            fprintf(output, "was deleted %d\n", deletedElement->value);
        } else {
            counter++;
            element = element->next;
        }
    }
    fprintf(output, "%d", element->value);

    return (EXIT_SUCCESS);
}
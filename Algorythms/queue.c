//
// Created by hokage on 20.01.2020.
//
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include "queue.h"

nodeptr *initNodep(void *ptr) {
    nodeptr *newElement;
    newElement = malloc(sizeof(node));
    newElement->ahead = NULL;
    newElement->behind = NULL;

    newElement->value = ptr;
    return newElement;

}
node *initNode(double initValue) {
    node *newElement;
    newElement = malloc(sizeof(node));
    newElement->ahead = NULL;
    newElement->behind = NULL;

    newElement->value = initValue;
    return newElement;
}

struct Queue *initQueue(double initValue) {
    node *newNode = initNode(initValue);

    struct Queue *queue;
    queue = malloc(sizeof(struct Queue));
    queue->next = newNode;
    queue->last = newNode;
    queue->len = 1;

    return queue;
}

void put(struct Queue *queue, double value) {
    if (queue == NULL) {
        return;
    }
    node *lastNode = queue->last;
    node *newNode = initNode(value);
    if (queue->len >= 1)
        chainElements(newNode, lastNode);
    else
        queue->next = newNode;

    queue->last = newNode;
    queue->len++;
}

void chainPtrElements(nodeptr *lagging, nodeptr *leading) {
    lagging->ahead = leading;
    leading->behind = lagging;
};

void chainElements(node *lagging, node *leading) {
    lagging->ahead = leading;
    leading->behind = lagging;
}

double get(struct Queue *queue) {
    node *resultNode = queue->next;
    queue->next = resultNode->behind;

    double result = resultNode->value;

    free(resultNode);
    queue->len--;

    if (queue->next != NULL) {
        queue->next->ahead = NULL;
    } else {
        queue->last = NULL;
    }

    return result;
}

node *getNode(struct Queue *queue) {
    if (queue->next == NULL)
        return NULL;

    node *result = queue->next;
    queue->next = result->ahead;
    return result;
}

void queue2() {
    FILE *input = fopen("/home/hokage/CLionProjects/Homework/Algorythms/input.txt", "r");
    double a, b;
    fscanf(input, "%le", &a);
    fscanf(input, "%le", &b);

    struct Queue *lessA, *betweenAB, *greatB;
    lessA = NULL;
    betweenAB = NULL;
    greatB = NULL;

    double value;
    int eof = fscanf(input, "%le ", &value);

    while (eof != -1) {

        if (value < (double) a) {
            // init queue didn't
            if (lessA == NULL) {
                lessA = initQueue(value);
            } else {
                put(lessA, value);
            }

        } else if ((double) a <= value && value <= (double) b) {
            // init queue if didn't
            if (betweenAB == NULL) {
                betweenAB = initQueue(value);
            } else {
                put(betweenAB, value);
            }
        } else {
            // init queue if didn't
            if (greatB == NULL) {
                greatB = initQueue(value);
            } else {
                put(greatB, value);
            }
        }
        eof = fscanf(input, "%le ", &value);
    }
    fclose(input);

    printf("lesser a:");
    while (lessA != NULL && lessA->next != NULL) {
        printf("%f ", (float) get(lessA));
    }
    printf("\n");

    printf("between a and b:");
    while (betweenAB != NULL && betweenAB->next != NULL) {
        printf("%f ", (float) get(betweenAB));
    }
    printf("\n");

    printf("greater b:");
    while (greatB != NULL && greatB->next != NULL) {
        printf("%f ", (float) get(greatB));
    }
}

void queue3() {
    FILE *f = fopen("/home/hokage/CLionProjects/Homework/Algorythms/f.txt", "r");
    FILE *g = fopen("/home/hokage/CLionProjects/Homework/Algorythms/g.txt", "w");

    char symbol, string[100];
    struct Queue *digits = NULL;

    int eof = fscanf(f, "%s", string);
    while (eof != -1){
        char *ch = string;
        while (*ch) {
            if (isdigit(*ch)) {
                if (digits == NULL) {
                    digits = initQueue((double) *ch);
                } else {
                    put(digits, (double) *ch);
                }
            }
            ch++;
        }
        fprintf(g, "%s ", string);
        while(digits->next != NULL)
            fprintf(g, "%c",(int) get(digits));

        eof = fscanf(f, "%s", string);
        fprintf(g, "\n");
    };
    fclose(f); fclose(g);

}
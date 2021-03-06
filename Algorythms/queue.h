//
// Created by hokage on 20.01.2020.
//

#ifndef ALGORYTHMS_QUEUE_H

#include <stdbool.h>
#include <stdio.h>
typedef struct nodeptr{
    struct nodeptr *ahead, *behind;
    void *value;
} nodeptr;

typedef struct node {
    struct node *ahead, *behind;
    double value;
} node;

struct Queue {
    node *next, *last;
    int len;
};
node *initNode(double initValue);

nodeptr *initNodep(void *ptr);

struct Queue *initQueue(double initValue);

void put(struct Queue *queue, double value);

void chainPtrElements(nodeptr *lagging, nodeptr *leading);
void chainElements(node *left, node *right);

double get(struct Queue *queue);

node *getNode(struct Queue *queue);

void queue2();

void queue3();

#define ALGORYTHMS_QUEUE_H

#endif //ALGORYTHMS_QUEUE_H

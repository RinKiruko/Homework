//
// Created by hokage on 24.01.2020.
//
#include "queue.h"
#ifndef ALGORYTHMS_STACK_H
#define ALGORYTHMS_STACK_H

struct Stack {
    node *next, *last;
    int len;
};
struct Stack *initStack(double initValue);

void stackPut(struct Stack *stack, double value);

double stackGet(struct Stack *queue);

void testStack();
void _testInitStack();
void _testStackPut();
void _testStackGet();
#endif //ALGORYTHMS_STACK_H
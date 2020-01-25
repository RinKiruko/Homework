//
// Created by hokage on 24.01.2020.
//
#include "queue.h"
#ifndef ALGORYTHMS_STACK_H
#define ALGORYTHMS_STACK_H

struct Stack {
    nodeptr *next, *last;
    int len;
};
struct Stack *initStack(void *initValue);

void stackPut(struct Stack *stack, void *value);

void * stackGet(struct Stack *stack);

void testStack();
void _testInitStack();
void _testStackPut();
void _testStackGet();
#endif //ALGORYTHMS_STACK_H
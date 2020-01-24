//
// Created by hokage on 24.01.2020.
//
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "queue.h"

struct Stack *initStack(double initValue) {
    node *newNode = initNode(initValue);

    struct Stack *stack;
    stack = malloc(sizeof(struct Queue));
    stack->next = newNode;
    stack->last = newNode;
    stack->len = 1;

    return stack;
}

void stackPut(struct Stack *stack, double value) {
    if (stack == NULL) {
        return;
    }
    node *nextNode = stack->next;
    node *newNode = initNode(value);
    if (stack->len >= 1)
        chainElements(newNode, nextNode);

    stack->next = newNode;
    stack->len++;
}

double stackGet(struct Stack *stack) {
    node *resultNode = stack->next;
    stack->next = resultNode->ahead;

    double result = resultNode->value;

    free(resultNode);
    stack->len--;

    if (stack->next != NULL) {
        stack->next->behind = NULL;
    } else {
        stack->last = NULL;
    }

    return result;
}


void _testInitStack() {
    double val = 0.423321451E-231;

    struct Stack *stack;
    stack = initStack(val);
    assert(stack->len == 1);
    assert(stack->next == stack->last);

    node *nextNode = stack->next;
    node *lastNode = stack->last;

    assert(nextNode->behind == NULL);
    assert(lastNode->ahead == NULL);
};

void _testStackPut() {
    double val1 = 0.423321451E-231, val2 = 0.1412513E+45;
    struct Stack *stack;

    stack = initStack(val1);
    stackPut(stack, val2);

    assert(stack->len == 2);

    node *nextNode = stack->next;
    node *previousNode = nextNode->ahead;
    node *lastNode = stack->last;

    assert(nextNode->behind == NULL);
    assert(nextNode->ahead == previousNode);
    assert(nextNode->value == val2);

    assert(previousNode == lastNode);
    assert(previousNode->behind == nextNode);
    assert(previousNode->value == val1);

    assert(lastNode->behind == nextNode);
    assert(lastNode->ahead == NULL);
    assert(lastNode->value == val1);
};

void _testStackGet() {
    double val1 = 0.423321451E-231, val2 = 0.1412513E+45;
    struct Stack *stack;

    stack = initStack(val1);
    stackPut(stack, val2);

    double obtainedElement = stackGet(stack);

    node *nextElement = stack->next;
    node *lastElement = stack->last;

    assert(stack->len == 1);
    assert(obtainedElement == val2);

    assert(nextElement == lastElement);
    assert(nextElement->behind == NULL);
    assert(nextElement->ahead == NULL);

    obtainedElement = stackGet(stack);

    node *temp = nextElement;
    nextElement = stack->next;
    lastElement = stack->last;

    assert(stack->len == 0);
    assert(obtainedElement == val1);

    assert(temp != nextElement);
    assert(nextElement == lastElement);
    assert(nextElement == NULL);
};

void testStack() {
    _testInitStack();
    _testStackPut();
    _testStackGet();
}
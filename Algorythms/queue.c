//
// Created by hokage on 20.01.2020.
//
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "queue.h"
#include "lists.h"

term *initTerm(int coef, int power) {
    term *newElement;
    newElement = malloc(sizeof(term));
    newElement->next = NULL;
    newElement->prev = NULL;
    newElement->head = newElement;

    newElement->coef = coef;
    newElement->power = power;
    newElement->index = 0;
    newElement->len = 1;
    return newElement;
}

term *initPolynome(int number) {
    term *firstTerm = initTerm(1, 0);

    for (int i = 1; i <= number; i++)
        appendTerm(firstTerm, 1);

    return firstTerm;
}

void appendTerm(term *to, int coef) {
    if (to == NULL) {
        return;
    }
    term *lastNode = to;
    while (lastNode->next != NULL)
        lastNode = lastNode->next;

    term *newNode = initTerm(coef, lastNode->power + 1);
    _chainElements(lastNode, newNode);
    newNode->head = to;
    newNode->index = lastNode->index + 1;

    to->head->len++;
}

void printPolynome(term *polynome, FILE *to) {
    if (to != NULL) {
        for (term *element = polynome->head; element != NULL; element = element->next) {
            fprintf(to, "%d*x^%d + ", element->coef, element->power);
        }
    } else {
        for (term *element = polynome->head; element != NULL; element = element->next) {
            printf("%d*x^%d + ", element->coef, element->power);
        }
    }
}

void comparePolynome() {
    term *firstPolynome = initPolynome(5), *secondPolynome = initPolynome(5);
    FILE *input = fopen("/home/hokage/CLionProjects/Homework/Algorythms/input.txt", "r");

    int coef;
    term *term = firstPolynome->head;
    for (int i = 0; i <= firstPolynome->len; i++) {
        fscanf(input, "%d", coef);
        term->coef = coef;
        term = term->next;
    }
    term = secondPolynome->head;
    for (int i = 0; i <= secondPolynome->len; i++) {
        fscanf(input, "%d", coef);
        term->coef = coef;
        term = term->next;
    }
    fclose(input);

    FILE *output = fopen("/home/hokage/CLionProjects/Homework/Algorythms/output.txt", "r");
    printPolynome(firstPolynome, output);
    fclose(output);
}
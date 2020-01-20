//
// Created by hokage on 20.01.2020.
//

#ifndef ALGORYTHMS_QUEUE_H

#include <stdbool.h>
#include <stdio.h>

typedef struct term {
    int index;
    int coef, power;
    int len;
    struct term *next, *prev, *head, *last;
} term;

term *initTerm(int coef, int power);

term *initPolynome(int termNumber);

void appendTerm(term *to, int coef);

void printPolynome(term *polynome, FILE *to);

void comparePolynome();
#define ALGORYTHMS_QUEUE_H

#endif //ALGORYTHMS_QUEUE_H

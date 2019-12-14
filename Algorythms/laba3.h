/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   laba2.h
 * Author: hokage
 *
 * Created on November 13, 2019, 3:38 PM
 */

#ifndef LABA2_H
#define LABA2_H

int TransLaba3();

struct Command{
    char name;
    char nextPossibleSteps[2];
};

struct State{
    struct Command (*get)(struct State * self, char key);

    char name;
    struct Command commands[3];
} ;

void checkOperations(char operations[]);


#endif /* LABA2_H */


//
// Created by hokage on 24.01.2020.
//
#include <stddef.h>
#include <stdlib.h>

#include "lists.h"
#include "stack.h"
#include "tree.h"


treeNode *initTreeNode(double value) {
    treeNode *newNode;
    newNode = malloc(sizeof(struct treeNode));
    newNode->value = value;

    newNode->parent = NULL;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;

    return newNode;
};


tree *initTree(double value) {
    tree *newTree = malloc(sizeof(tree));

    treeNode *root = initTreeNode(value);

    newTree->root = root;

    return newTree;
};

void addLeftChild(treeNode *parent, treeNode *child) {
    child->parent = parent;
    parent->leftChild = child;
}

void addRightChild(treeNode *parent, treeNode *child) {
    child->parent = parent;
    parent->rightChild = child;
}
void removeTreeNode(treeNode *node) {
    treeNode *parent = node->parent;
    node->parent = NULL;

};
void tree1() {
    struct Stack *stack;

    FILE *input = fopen("/home/hokage/CLionProjects/Homework/Algorythms/tree1_input.txt", "r");
    char n;

    int eof = fscanf(input, "%c", &n);
    list_node *list = initList(1,(int*) &n);
    list_node *head = list->head;

    tree *tree = initTree(head->value);
    stack = initStack(tree->root);
    do {
        eof = fscanf(input, "%d", &n);

    } while(eof != -1);

}
void findDepth(tree *tree) {

};
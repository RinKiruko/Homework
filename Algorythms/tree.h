//
// Created by hokage on 23.01.2020.
//

#ifndef ALGORYTHMS_TREE_H
#define ALGORYTHMS_TREE_H

#include "lists.h"
#include "stack.h"

typedef struct treeNode {
    struct treeNode *parent, *leftChild, *rightChild;
    double value;
} treeNode;

typedef struct tree {
    treeNode *root;
} tree;

treeNode *initTreeNode(double value);

tree *initTree(double value);

void chainNodes(tree *tree, treeNode *node);

void addLeftChild(treeNode *parent, treeNode *child);
void addRightChild(treeNode *parent, treeNode *child);

void removeTreeNode(treeNode *node);

void fillTree();
void findDepth(tree *tree);

#endif //ALGORYTHMS_TREE_H

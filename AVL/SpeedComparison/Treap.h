//
// Created by lhc456 on 2023/5/15.
//

#ifndef PLAY_WITH_ALGO_TREAP_H
#define PLAY_WITH_ALGO_TREAP_H

#include <iostream>

using namespace std;

struct TreapNode {
    int val, rank;
    TreapNode *leftChild, *rightChild, *parent;
};

TreapNode *root = NULL;


TreapNode *treapRotate(TreapNode *root, TreapNode *a) {
    TreapNode *b = a->parent;
    if (!b)
        return root;

    if (a == b->leftChild) {
        b->leftChild = a->rightChild;
        if (a->rightChild)
            a->rightChild->parent = b;
        a->rightChild = b;
    } else {
        b->rightChild = a->leftChild;
        if (a->leftChild)
            a->leftChild->parent = b;
        a->leftChild = b;
    }
    if (b->parent)
        if (b == b->parent->leftChild)
            b->parent->leftChild = a;
        else
            b->parent->rightChild = a;
    a->parent = b->parent;
    b->parent = a;
    if (root == b)
        root = a;
    return root;
}

TreapNode *treapInsert(TreapNode *root, int number) {
    TreapNode *current = root;
    TreapNode *previous = NULL;
    while (current) {
        previous = current;
        if (current->val >= number)
            current = current->leftChild;
        else
            current = current->rightChild;
    }

    TreapNode *node = new TreapNode;
    node->val = number;
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->parent = NULL;
    node->rank = rand();
    if (!previous)
        return node;

    node->parent = previous;
    if (previous->val >= node->val)
        previous->leftChild = node;
    else
        previous->rightChild = node;

    while (node->parent && node->parent->rank < node->rank)
        root = treapRotate(root, node);

    return root;
}

TreapNode *treapFind(TreapNode *root, int number) {
    TreapNode *current = root;
    while (current) {
        if (current->val == number)
            return current;
        else if (current->val > number)
            current = current->leftChild;
        else
            current = current->rightChild;
    }
    return NULL;
}

TreapNode *treapDelete(TreapNode *root, TreapNode *node) {
    while (node->leftChild || node->rightChild) {
        TreapNode *child = node->leftChild;
        if (!child || node->rightChild && node->rightChild->rank > child->rank)
            child = node->rightChild;
        root = treapRotate(root, child);
    }
    if (node->parent)
        if (node->parent->leftChild == node)
            node->parent->leftChild = NULL;
        else
            node->parent->rightChild = NULL;
    if (root == node)
        root = NULL;
    delete node;
    return root;
}

#endif //PLAY_WITH_ALGO_TREAP_H

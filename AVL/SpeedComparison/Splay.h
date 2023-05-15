//
// Created by lhc456 on 2023/5/15.
//

#ifndef PLAY_WITH_ALGO_SPLAY_H
#define PLAY_WITH_ALGO_SPLAY_H

#include<iostream>


using namespace std;

struct SplayNode {
    int val;
    SplayNode *leftChild, *rightChild, *parent;
};

SplayNode *root = NULL;


SplayNode *rotate(SplayNode *root, SplayNode *a) {
    SplayNode *b = a->parent;
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

SplayNode *splay(SplayNode *root, SplayNode *node) {
    while (node != root) {
        if (node->parent == root)
            root = rotate(root, node);
        else if (node == node->parent->leftChild
                 && node->parent == node->parent->parent->leftChild
                 || node == node->parent->rightChild
                    && node->parent == node->parent->parent->rightChild) {
            root = rotate(root, node->parent);
            root = rotate(root, node);
        } else {
            root = rotate(root, node);
            root = rotate(root, node);
        }
    }
    return root;
}

SplayNode *splayInsert(SplayNode *root, int number) {
    SplayNode *current = root;
    SplayNode *previous = NULL;
    while (current) {
        previous = current;
        if (current->val >= number)
            current = current->leftChild;
        else
            current = current->rightChild;
    }

    SplayNode *node = new SplayNode;
    node->val = number;
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->parent = NULL;
    if (!previous)
        return node;

    node->parent = previous;
    if (previous->val >= node->val)
        previous->leftChild = node;
    else
        previous->rightChild = node;

    return splay(root, node);
}

SplayNode *splayFind(SplayNode *root, int number) {
    SplayNode *current = root;
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

/**
 * a is the root of left sub-tree
 * b is the root of right sub-tree
 * largest element in a < smallest element in b
 */
SplayNode *splayMerge(SplayNode *a, SplayNode *b) {
    if (!a)
        return b;
    if (!b)
        return a;
    SplayNode *newRoot;
    if (rand() % 2 == 0) {
        newRoot = a;
        while (newRoot->rightChild)
            newRoot = newRoot->rightChild;
        newRoot = splay(a, newRoot);
        newRoot->rightChild = b;
        b->parent = newRoot;
    } else {
        newRoot = b;
        while (newRoot->leftChild)
            newRoot = newRoot->leftChild;
        newRoot = splay(b, newRoot);
        newRoot->leftChild = a;
        a->parent = newRoot;
    }
    return newRoot;
}

SplayNode *splayDelete(SplayNode *root, SplayNode *node) {
    root = splay(root, node);
    if (root->leftChild)
        root->leftChild->parent = NULL;
    if (root->rightChild)
        root->rightChild->parent = NULL;
    root = splayMerge(root->leftChild, root->rightChild);
    delete (node);
    return root;
}


#endif //PLAY_WITH_ALGO_SPLAY_H

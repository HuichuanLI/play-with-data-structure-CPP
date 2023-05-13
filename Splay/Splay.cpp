//
// Created by lhc456 on 2023/5/13.
//
#include<iostream>
#include <sys/time.h>
#include <fstream>


using namespace std;

long getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}


class SplayNode {
public:
    int val;
    SplayNode *leftChild, *rightChild, *parent;
};

class Splay {
public:
    SplayNode *root;
public:
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
        if (root == b) {
            this->root = a;
            root = a;
        }
        return root;
    }

    SplayNode *splayInsert(int number) {
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
        if (!previous) {
            root = node;
            return node;
        }

        node->parent = previous;
        if (previous->val >= node->val)
            previous->leftChild = node;
        else
            previous->rightChild = node;

        return splay(root, node);
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

    void printSplay(ofstream &fout, SplayNode *node) {
        if (node == NULL)
            return;
        printSplay(fout, node->leftChild);
        fout << node->val << endl;
        printSplay(fout, node->rightChild);
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


};

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("/Users/lhc456/Desktop/c++/play-with-data-structure-CPP/Splay/data/5.in");
    ofstream fout("/Users/lhc456/Desktop/c++/play-with-data-structure-CPP/Splay/data/5.out");
    cout.tie(NULL);
    srand((unsigned) time(NULL));

    long start_time = getTime();
    Splay *splay = new Splay();
    SplayNode *root = splay->root;
    int n;
    int number[1000000];

    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> number[i];
        root = splay->splayInsert(number[i]);
    }

    splay->printSplay(fout, root);

    for (int i = n - 1; i >= 0; i--) {
        SplayNode *node = splay->splayFind(root, number[i]);
        if (!node)
            cout << "Cannot find number " << number[i] << endl;
        else
            root = splay->splayDelete(root, node);
    }

    cout << "Empty Tree?:" << (root == NULL ? "Yes" : "No") << endl;
    long end_time = getTime();
    cout << "Total time: " << (end_time - start_time + 0.0) / 1000 << "(s)" << endl;
}
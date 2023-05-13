//
// Created by lhc456 on 2023/5/12.
//
#include<iostream>
#include <fstream>
#include <time.h>

using namespace std;

class TreapNode {
public:
    int val, rank;
    TreapNode *leftChild, *rightChild, *parent;
};


int number[1000000];

long getTime() {
    struct timeval tv;
    clock_t start, finish;
    start = clock();
    return start;
}

class Treap {
public:
    TreapNode *root = NULL;
public:
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

    TreapNode *treapFind(int number) {
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

    TreapNode *treapDelete(TreapNode *node) {
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

    void printBst(ofstream &fout, TreapNode *node) {
        if (node == NULL)
            return;
        printBst(fout, node->leftChild);
        fout << node->val << endl;
        printBst(fout, node->rightChild);
    }

    TreapNode *treapInsert(int number) {
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
        if (!previous) {
            root = node;
            return node;
        }
        node->parent = previous;
        if (previous->val >= node->val)
            previous->leftChild = node;
        else
            previous->rightChild = node;

        while (node->parent && node->parent->rank < node->rank)
            root = treapRotate(root, node);
        this->root = root;
        return root;
    }

};

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("/Users/lhc456/Desktop/c++/play-with-data-structure-CPP/Treap/data/5.in");
    ofstream fout("/Users/lhc456/Desktop/c++/play-with-data-structure-CPP/Treap/data/5.out");
    cout.tie(NULL);
    srand((unsigned) time(NULL));

    long start_time = getTime();
    Treap *treap = new Treap();
    TreapNode *root = treap->root;
    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> number[i];
        treap->treapInsert(number[i]);
    }
    fin.close();
    root = treap->root;
    treap->printBst(fout, root);

    for (int i = n - 1; i >= 0; i--) {
        TreapNode *node = treap->treapFind(number[i]);
        if (!node)
            cout << "Cannot find number " << number[i] << endl;
        else
            root = treap->treapDelete(node);
    }

    cout << "Empty Tree?:" << (root == NULL ? "Yes" : "No") << endl;
    long end_time = getTime();
    cout << "Total time: " << (end_time - start_time + 0.0) / 1000 << "(s)" << endl;
}
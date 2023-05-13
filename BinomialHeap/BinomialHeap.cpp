#include <iostream>
#include <vector>

using namespace std;

// 二项树
class BinomialTree {
public:
    int val; // 节点的值
    int degree; // 树的度数
    BinomialTree *child; // 左儿子
    BinomialTree *sibling; // 兄弟节点

    // 构造函数
    BinomialTree(int v = 0) {
        val = v;
        degree = 0;
        child = NULL;
        sibling = NULL;
    }

    // 合并两棵二项树
    BinomialTree *merge(BinomialTree *other) {
        if (degree != other->degree) {
            cout << "Error: Cannot merge trees with different degrees." << endl;
            return NULL;
        }
        BinomialTree *newTree = new BinomialTree();
        if (val < other->val) {
            newTree->val = val;
            child = other;
        } else {
            newTree->val = other->val;
            other->child = this;
        }
        newTree->degree = degree + 1;
        return newTree;
    }

    // 打印二项树
    void print() {
        cout << "Node " << val << " (degree " << degree << ")" << endl;
        if (child) {
            cout << "  Children:" << endl;
            child->print();
        }
        if (sibling) {
            cout << "  Sibling:" << endl;
            sibling->print();
        }
    }
};

// 二项堆
class BinomialHeap {
public:
    BinomialTree *root; // 根节点

    // 构造函数
    BinomialHeap() {
        root = NULL;
    }

    // 合并两个二项堆
    BinomialHeap *merge(BinomialHeap *other) {
        BinomialHeap *heap = new BinomialHeap();
        BinomialTree *carry = NULL;
        BinomialTree *t1 = root;
        BinomialTree *t2 = other->root;
        while (t1 && t2) {
            if (t1->degree < t2->degree) {
                if (carry) {
                    heap->root = carry->merge(t1);
                    carry = NULL;
                } else {
                    heap->root = t1;
                }
                t1 = t1->sibling;
            } else {
                if (carry) {
                    heap->root = carry->merge(t2);
                    carry = NULL;
                } else {
                    heap->root = t2;
                }
                t2 = t2->sibling;
            }
            heap->root->sibling = NULL;
            carry = heap->root;
            heap->root = heap->root->sibling;
        }
        while (t1) {
            if (carry) {
                heap->root = carry->merge(t1);
                carry = NULL;
            } else {
                heap->root = t1;
            }
            t1 = t1->sibling;
            heap->root->sibling = NULL;
            carry = heap->root;
            heap->root = heap->root->sibling;
        }
        while (t2) {
            if (carry) {
                heap->root = carry->merge(t2);
                carry = NULL;
            } else {
                heap->root = t2;
            }
            t2 = t2->sibling;
            heap->root->sibling = NULL;
            carry = heap->root;
            heap->root = heap->root->sibling;
        }
        if (carry) {
            heap->root = carry;
        }
        root = NULL;
        other->root = NULL;
        return heap;
    }

    // 插入一个值
    void insert(int val) {
        BinomialTree *tree = new BinomialTree(val);
        root = root->merge(tree);
    }

    // 删除最小值，并返回该值
    int deleteMin() {
        if (!root) {
            cout << "Error: Heap is empty." << endl;
            return -1;
        }
        int minVal = root->val;
        BinomialTree *minTree = root;
        BinomialTree *prevTree = NULL;
        BinomialTree *curTree = root->sibling;
        while (curTree) {
            if (curTree->val < minVal) {
                minVal = curTree->val;
                minTree = curTree;
                prevTree = root;
            } else {
                prevTree = curTree;
            }
            curTree = curTree->sibling;
        }
        if (minTree == root) {
            root = root->sibling;
        } else {
            prevTree->sibling = minTree->sibling;
        }
        BinomialHeap *heap = new BinomialHeap();
        BinomialTree *child = minTree->child;
        while (child) {
            BinomialTree *next = child->sibling;
            child->sibling = heap->root;
            heap->root = child;
            child = next;
        }
        root = root->merge(heap->root);
        return minVal;
    }

    // 打印二项堆
    void print() {
        if (!root) {
            cout << "Empty heap." << endl;
            return;
        }
        vector<BinomialTree *> trees;
        BinomialTree *curTree = root;
        while (curTree) {
            trees.push_back(curTree);
            curTree = curTree->sibling;
        }
        cout << "Heap:" << endl;
        for (int i = 0; i < trees.size(); i++) {
            cout << "  Tree " << i << ":" << endl;
            trees[i]->print();
        }
    }
};
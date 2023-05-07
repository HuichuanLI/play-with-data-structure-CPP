//
// Created by lhc456 on 2023/5/7.
//
#include <iostream>
#include <queue>

using namespace std;


struct node {                         //指针二叉树
    char value;
    node *l, *r;

    node(char value = '#', node *l = NULL, node *r = NULL) : value(value), l(l), r(r) {}
};

void remove_tree(node *root) {         //释放空间
    if (root == NULL) return;
    remove_tree(root->l);
    remove_tree(root->r);
    delete root;
}

int main() {
    node *A, *B, *C, *D, *E, *F, *G, *H, *I;             //以下建一棵二叉树
    A = new node('A');
    B = new node('B');
    C = new node('C');
    D = new node('D');
    E = new node('E');
    F = new node('F');
    G = new node('G');
    H = new node('H');
    I = new node('I');
    E->l = B;
    E->r = G;
    B->l = A;
    B->r = D;
    G->l = F;
    G->r = I;
    D->l = C;
    I->l = H;   //以上建了一棵二叉树
    queue<node> q;
    q.push(*E);
    while (q.size()) {
        node *tmp;
        tmp = &(q.front());
        cout << tmp->value << " ";            //打印队头
        q.pop();                              //去掉队头
        if (tmp->l) q.push(*(tmp->l));         //左孩子入队
        if (tmp->r) q.push(*(tmp->r));         //右孩子入队
    }
    remove_tree(E);
    return 0;
}
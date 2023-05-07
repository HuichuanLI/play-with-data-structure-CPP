//
// Created by lhc456 on 2023/5/7.
//
#include<iostream>
#include <queue>


using namespace std;
const int N = 100005;
struct Node {                  //用静态数组记录二叉树
    char value;
    int lson, rson;           //左右孩子
} tree[N];                     //tree[0]不用，0表示空结点


int index_num = 1;                //记录结点存在tree[]的位置，从tree[1]开始用
int newNode(char val) {
    tree[index_num].value = val;
    tree[index_num].lson = 0;     //0表示空，tree[0]不用
    tree[index_num].rson = 0;
    return index_num++;
}

void Insert(int &father, int child, int l_r) {    //插入孩子
    if (l_r == 0) tree[father].lson = child;     //左孩子
    else tree[father].rson = child;     //右孩子
}

int buildtree() {              //建一棵二叉树
    int A = newNode('A');
    int B = newNode('B');
    int C = newNode('C');
    int D = newNode('D');
    int E = newNode('E');
    int F = newNode('F');
    int G = newNode('G');
    int H = newNode('H');
    int I = newNode('I');
    Insert(E, B, 0);
    Insert(E, G, 1);       //E的左孩子是B，右孩子是G
    Insert(B, A, 0);
    Insert(B, D, 1);
    Insert(G, F, 0);
    Insert(G, I, 1);
    Insert(D, C, 0);
    Insert(I, H, 0);
    int root = E;
    return root;
}

int main() {
    int root = buildtree();
    queue<int> q;
    q.push(root);                          //从根结点开始
    while (q.size()) {
        int tmp = q.front();
        cout << tree[tmp].value << " ";    //打印队头
        q.pop();                           //去掉队头
        if (tree[tmp].lson != 0) q.push(tree[tmp].lson);   //左孩子入队
        if (tree[tmp].rson != 0) q.push(tree[tmp].rson);   //右孩子入队
    }
    return 0;
}
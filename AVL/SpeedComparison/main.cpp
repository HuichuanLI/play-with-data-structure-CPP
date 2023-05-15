//
// Created by lhc456 on 2023/5/15.
//

#include <iostream>
//#include "PseudoBST.h"
//#include "Splay.h"
//#include "Treap.h"
//#include "PseudoBST.h"
#include <fstream>
#include "RedBlackTree.h"
#include <sys/time.h>

long getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main() {


    ios::sync_with_stdio(false);
    ifstream fin("/Users/lhc456/Desktop/c++/play-with-data-structure-CPP/AVL/SpeedComparison/1.in");
    ofstream fout("/Users/lhc456/Desktop/c++/play-with-data-structure-CPP/AVL/SpeedComparison/1.out");
    cout.tie(NULL);
    long start_time = getTime();

    int n, m;
    int op, number;
    RBNode *node;
    fin >> n >> m;
    for (int i = 0; i < m; i++) {
        fin >> op >> number;
        switch (op) {
            case 1:
                root = rbInsert(root, number);
                break;
            case 2:
                fout << (rbFind(root, number) ? "Yes" : "No") << endl;
                break;
            case 3:
                node = rbFind(root, number);
                if (node)
                    root = rbDelete(root, node);
                break;
            default:
                break;
        }
    }
    fin.close();
    // 输出运行时间
    long end_time = getTime();
    cout << "Total time: " << (end_time - start_time + 0.0) / 1000 << "(s)" << endl;
}
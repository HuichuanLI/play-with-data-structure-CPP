//
// Created by lhc456 on 2023/5/13.
//
#include<iostream>
#include <fstream>


using namespace std;

const int n = 100000;
const int range = 100000000;

int getRand() {
    return rand() * 32768 + rand();
}

int main() {
    ios::sync_with_stdio(false);
    ofstream fout("/Users/lhc456/Desktop/c++/play-with-data-structure-CPP/Treap/data/5.in");
    srand((unsigned) time(NULL));

    fout << n << endl;
    for (int i = 0; i < n; i++) {
        fout << getRand() % range << endl;
        //fout << i << endl;
    }

    fout.close();
}
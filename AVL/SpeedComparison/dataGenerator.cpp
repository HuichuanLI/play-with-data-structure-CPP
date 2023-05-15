//
// Created by lhc456 on 2023/5/15.
//
#include <iostream>
#include <fstream>

using namespace std;

// N表示数字范围(1~N)
const int N = 10000;
// M表示操作数量
const int M = 5000000;
// FILE_NAME表示生成的输入数据文件名
const string FILE_NAME = "1.in";

// 返回1~range范围内的随机整数
int getRand(int range) {
    return (rand() * 32768 + rand()) % range + 1;
}

int main() {
    ios::sync_with_stdio(false);
    ofstream fout(FILE_NAME);
    srand((unsigned) time(NULL));


    fout << N << ' ' << M << endl;

    // 场景1
    for (int i = 0; i < M; i++) {
        fout << getRand(3) << ' ' << getRand(N) << endl;
    }

    /* 场景二
    for (int i = 0; i < M; i++) {
        fout << getRand(2) << ' ' << getRand(N) << endl;
    }
    */

    /* 场景三
    for (int i = 0; i < 1000000; i++) {
        fout << 1 << ' ' << (N == 10000 ? i / 100 + 1 : i + 1) << endl;
    }
    for (int i = 0; i < 4000000; i++) {
        fout << getRand(2) + 1 << ' ' << getRand((N == 10000 ? N : 1000000)) << endl;
    }
    */

    /* 场景四
    for (int i = 0; i < 1000000; i++) {
        fout << 1 << ' ' << (N == 10000 ? i / 100 + 1 : i + 1) << endl;
    }
    for (int i = 0; i < 3000000; i++) {
        fout << 2 + 1 << ' ' << getRand((N == 10000 ? N : 1000000)) << endl;
    }
    for (int i = 0; i < 1000000; i++) {
        fout << 3 << ' ' << (N == 10000 ? i / 100 + 1 : i + 1) << endl;
    }
    */

    /* 场景五
    for (int i = 0; i < 1000000; i++) {
        fout << 1 << ' ' << (N == 10000 ? i / 100 + 1 : i + 1) << endl;
    }
    for (int i = 0; i < 3000000; i++) {
        fout << 2 + 1 << ' ' << getRand((N == 10000 ? N : 1000000)) << endl;
    }
    for (int i = 999999; i >= 0; i--) {
        fout << 3 << ' ' << (N == 10000 ? i / 100 + 1 : i + 1) << endl;
    }
    */

    fout.close();
}
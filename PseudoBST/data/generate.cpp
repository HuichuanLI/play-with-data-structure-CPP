//
// Created by lhc456 on 2023/5/14.
//
#include<iostream>
#include <fstream>

using namespace std;

const int n = 500000;
const int range = 100000;

int number[1000001];

int getRand() {
    return rand() * 32768 + rand();
}

int main() {
    ios::sync_with_stdio(false);
    ofstream fout("/Users/lhc456/Desktop/c++/play-with-data-structure-CPP/PseudoBST/data/2.in");
    srand((unsigned) time(NULL));

    memset(number, 0, sizeof(number));
    fout << range << " " << n << endl;
    int numberCount = 0;
    for (int i = 0; i < n; i++) {
        int caseType;
        while (true) {
            caseType = rand() % 3 + 1;
            if (caseType == 2 && (numberCount == 0 || i < n / 2))
                continue;
            break;
        }
        int x, y;
        switch (caseType) {
            case 1:
                x = getRand() % range;
                number[x]++;
                fout << "1 " << x << endl;
                numberCount++;
                break;
            case 2:
                while (true) {
                    x = getRand() % range;
                    if (number[x] > 0)
                        break;
                }
                number[x]--;
                numberCount--;
                fout << "2 " << x << endl;
                break;
            case 3:
                while (true) {
                    x = getRand() % range;
                    y = getRand() % range;
                    if (x < y)
                        break;
                }
                fout << "3 " << x << " " << y << endl;
                break;
            default:
                break;
        }
    }

    fout.close();
}
//
// Created by lhc456 on 2023/5/2.
//

#include "QuickSort.h"
#include <iostream>

using namespace std;

int main() {
    vector<int> abc = {10, 0, -1, 2};
    QuickSort *q = new QuickSort();
    q->quick_sort(abc, 0, abc.size() - 1);
    for (auto elem: abc) {
        cout << elem << endl;
    }
}
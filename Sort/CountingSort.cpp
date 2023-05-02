//
// Created by lhc456 on 2023/5/2.
//

//
// Created by lhc456 on 2023/5/2.
//
//
// Created by lhc456 on 2023/5/2.
//
#include <functional>
#include <iterator>
#include <algorithm>
#include <utility>
#include <cmath>
#include <iostream>
#include <map>

using namespace std;

void CountingSort(std::vector<int> &arr) {
    if (arr.size() <= 1) {
        return;
    }
    int max_value = *std::max_element(arr.begin(), arr.end());
    int k = 0;
    std::map<int, int> count_num;
    for (int i = 0; i < arr.size(); i++) {
        count_num[arr.at(i)] += 1;
    }
    for (auto elem: count_num) {
        for (int i = 0; i < elem.second; i++) {
            arr.at(k) = elem.first;
            k += 1;
        }
    }
}

int main() {
    std::vector<int> abc = {2, 5, 3, 0, 2, 3, 0, 3, 0, 4, 4, 5, 1, 7, 8, 9};

    CountingSort(abc);
    for (auto elem: abc) {
        cout << elem << endl;
    }

}


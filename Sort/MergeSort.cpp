//
// Created by lhc456 on 2023/5/2.
//

#include "MergeSort.h"

#include <iostream>
#include <vector>
#include "MergeSort.h"

int main() {
    const std::vector<int> test_data{0, -1, 3, 190, -500};

    std::vector<int> a{test_data};
    merge_sort(a.begin(), a.end());
    for (auto i: a) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    std::vector<int> b{test_data};
    inplace_merge_sort(b.begin(), b.end());
    for (auto i: b) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    return 0;
}
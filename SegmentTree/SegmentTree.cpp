//
// Created by lhc456 on 2023/5/3.
//
#include <iostream>
#include "SegmentTree.h"

int main() {
    int nums[] = {-2, 0, 3, -5, 2, -1};
    SegmentTree<int> *segmentTree = new SegmentTree<int>(nums, 6, [](int a, int b) -> int {
        return a + b;
    });
    std::cout << segmentTree->query(2, 5) << std::endl;
    segmentTree->print();
    return 0;
}
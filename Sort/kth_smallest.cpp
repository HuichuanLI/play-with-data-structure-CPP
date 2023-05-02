//
// Created by lhc456 on 2023/5/2.
//
#include <functional>
#include <iterator>
#include <algorithm>
#include <utility>

int partition_two_way(std::vector<int> &arr, int p, int r) {
    srand((unsigned) time(NULL));
    int q = (rand() % (r - p + 1)) + p;
    std::swap(arr.at(p), arr.at(q));
    int pivot = arr.at(p);
    while (p < r) {
        while ((p < r) and (arr.at(r) >= pivot)) {
            r -= 1;
        }
        arr.at(p) = arr.at(r);
        while ((p < r) and (arr.at(p) <= pivot)) {
            p += 1;
        }
        arr.at(r) = arr.at(p);
    }
    arr.at(p) = pivot;
    return p;
}

int kth_smallest(std::vector<int> &arr, int k) {
    if (arr.size() < k) {
        return -1;
    }
    int q = partition_two_way(arr, 0, arr.size() - 1);
    while (q != k - 1) {
        if (q < k - 1) {
            q = partition_two_way(arr, q + 1, arr.size() - 1);
        } else {
            q = partition_two_way(arr, 0, q - 1);
        }
        return arr.at(q);
    }
}
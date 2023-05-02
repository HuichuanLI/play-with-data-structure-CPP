//
// Created by lhc456 on 2023/5/2.
//

#ifndef PLAY_WITH_ALGO_QUICKSORT_H
#define PLAY_WITH_ALGO_QUICKSORT_H

#include <functional>
#include <iterator>
#include <algorithm>
#include <utility>


class QuickSort {
public:
    int partition(std::vector<int> &list, int p, int r) {
        int i = p;
        int pivot = list.at(r);
        for (int j = p; j < r; j++) {
            if (list.at(j) < pivot) {
                if (i != j) {
                    std::swap(list.at(i), list.at(j));
                }
                i += 1;
            }
        }
        std::swap(list.at(i), list.at(r));
        return i;
    }

    void quick_sort(std::vector<int> &arr, int p, int r) {
        if (p >= r) {
            return;
        }
        int q = partition_two_way(arr, p, r);
        quick_sort(arr, p, q - 1);
        quick_sort(arr, q + 1, r);
    }

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
};


#endif //PLAY_WITH_ALGO_QUICKSORT_H

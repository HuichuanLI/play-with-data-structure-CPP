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

void bucket_sort(std::vector<int> &arr, int m) {
    if (arr.size() < 2) {
        return;
    }
    int min_num = *std::min_element(arr.begin(), arr.end());
    int max_num = *std::max_element(arr.begin(), arr.end());
    int i = 0;

    int bucket_size = ceil((max_num - min_num) / m);
    std::map<int, std::vector<int>> buckets;
    for (auto elem: arr) {
        int bucket_index = (elem - min_num) / bucket_size;
        buckets[bucket_index].push_back(elem);
    }
    int k = 0;
    for (auto elem: buckets) {
        std::sort(elem.second.begin(), elem.second.end());
        for (auto elm: elem.second) {
            arr.at(k) = elm;
            k += 1;
        }
    }
}

int main() {
    std::vector<int> abc = {2, 5, 3, 0, 2, 3, 0, 3, 0, 4, 4, 5, 1, 7, 8, 9};

    bucket_sort(abc, 4);
    for (auto elem: abc) {
        cout << elem << endl;
    }

}


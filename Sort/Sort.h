//
// Created by lhc456 on 2023/5/1.
//

#ifndef PLAY_WITH_ALGO_SORT_H
#define PLAY_WITH_ALGO_SORT_H

#include <iterator>
#include <functional>

template<typename BidirIt,
        typename BinaryPred = std::less<typename std::iterator_traits<BidirIt>::value_type>>

void bubble_sort(BidirIt first, BidirIt last, BinaryPred comp = BinaryPred()) {
    if (std::distance(first, last) <= 1) { return; }
    bool flag = true;
    for (auto it = first; flag and it != last; ++it) {
        flag = false;
        for (auto itt = first; itt != last - std::distance(first, it) - 1; ++itt) {
            if (comp(*(itt + 1), *itt)) {
                std::swap(*itt, *(itt + 1));
                flag = true;
            }
        }
    }
}

template<typename BidirIt,
        typename BinaryPred = std::less<typename std::iterator_traits<BidirIt>::value_type>>
void insertion_sort(BidirIt first, BidirIt last, BinaryPred comp = BinaryPred()) {
    if (std::distance(first, last) <= 1) { return; }
    for (auto it = first + 1; it != last; ++it) {
        const auto target = *it;
        auto itt = it;
        for (; std::distance(first, itt) > 0 and comp(target, *(itt - 1)); --itt) {
            *itt = *(itt - 1);
        }
        *itt = target;
    }
}

template<typename BidirIt,
        typename BinaryPred = std::less<typename std::iterator_traits<BidirIt>::value_type>>
void selection_sort(BidirIt first, BidirIt last, BinaryPred comp = BinaryPred()) {
    if (std::distance(first, last) <= 1) { return; }
    for (auto it = first; it != last - 1; ++it) {
        auto tag = it;
        for (auto itt = it + 1; itt != last; ++itt) {
            if (comp(*itt, *tag)) {
                tag = itt;
            }
        }
        if (tag != it) {
            std::swap(*it, *tag);
        }
    }
}

template<typename FrwdIt,
        typename BinaryPred = std::less<typename std::iterator_traits<FrwdIt>::value_type>>
void bubble_down_sort(FrwdIt first, FrwdIt last, BinaryPred comp = BinaryPred()) {
    if (std::distance(first, last) <= 1) { return; }
    for (auto it = first; it != last; ++it) {
        for (auto itt = it + 1; itt != last; ++itt) {
            if (comp(*itt, *it)) {
                std::swap(*it, *itt);
            }
        }
    }
}


template<typename BidirIt,
        typename BinaryPred = std::less<typename std::iterator_traits<BidirIt>::value_type>>
void shell_sort(BidirIt first, BidirIt last, BinaryPred comp = BinaryPred()) {
    const size_t len = std::distance(first, last);
    if (len <= 1) { return; }
    for (size_t step = len / 2; step >= 1; step /= 2) {
        for (auto it = first + step; it != last; ++it) {
            auto target = *it;
            auto itt = it - step;
            for (; std::distance(first, itt) >= 0 and comp(target, *itt); itt -= step) {
                *(itt + step) = *itt;
            }
            *(itt + step) = target;
        }
    }
}

#endif //PLAY_WITH_ALGO_SORT_H

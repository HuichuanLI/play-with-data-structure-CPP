//
// Created by lhc456 on 2023/5/15.
//

#ifndef PLAY_WITH_ALGO_PSEUDOBST_H
#define PLAY_WITH_ALGO_PSEUDOBST_H

#include <iostream>
#include <sys/time.h>
#include <fstream>

using namespace std;

int numberCount[1001];
int n;


void pseudoBSTInsert(int number) {
    int l = 1, r = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (mid == number) {
            numberCount[mid]++;
            return;
        } else if (mid > number) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
}

void pseudoBSTDelete(int number) {
    int l = 1, r = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (mid == number) {
            numberCount[mid]--;
            return;
        } else if (mid > number) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
}

#endif //PLAY_WITH_ALGO_PSEUDOBST_H

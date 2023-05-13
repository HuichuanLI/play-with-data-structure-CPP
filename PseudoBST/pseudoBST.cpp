//
// Created by lhc456 on 2023/5/14.
//
#include<iostream>
#include <sys/time.h>
#include <fstream>


using namespace std;

long getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

class pseudoBST {
public:
    int numberCount[1000001], rangeCount[1000001];
    int range;
public:

    void pseudoBSTInsert(int number) {
        int l = 0, r = range - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            rangeCount[mid]++;
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
        int l = 0, r = range - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            rangeCount[mid]--;
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

    int pseudoBSTSearch(int l, int r, int x, int y) {
        if (l > r) {
            return 0;
        }
        int mid = (l + r) / 2;
        if (l == x && r == y)
            return rangeCount[mid];

        int leftCount = 0, rightCount = 0;
        if (x < mid)
            leftCount = pseudoBSTSearch(l, mid - 1, x, min(mid - 1, y));
        if (y > mid)
            rightCount = pseudoBSTSearch(mid + 1, r, max(mid + 1, x), y);

        int res = leftCount + rightCount + ((mid >= x && mid <= y) ? numberCount[mid] : 0);
        return res;
    }


};

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("/Users/lhc456/Desktop/c++/play-with-data-structure-CPP/PseudoBST/data/2.in");
    ofstream fout("/Users/lhc456/Desktop/c++/play-with-data-structure-CPP/PseudoBST/data/2.out");
    cout.tie(NULL);
    long start_time = getTime();

    int n, caseType, x, y;
    int range;
    fin >> range >> n;
    pseudoBST *pseudoBst = new pseudoBST();
    pseudoBst->range = range;

    for (int i = 0; i < n; i++) {
        fin >> caseType;
        switch (caseType) {
            case 1:
                fin >> x;
                pseudoBst->pseudoBSTInsert(x);
                break;
            case 2:
                fin >> x;
                pseudoBst->pseudoBSTDelete(x);
                break;
            case 3:
                fin >> x >> y;
                fout << pseudoBst->pseudoBSTSearch(0, range - 1, x, y) << endl;
                break;
            default:
                break;
        }
    }

    long end_time = getTime();
    cout << "Total time: " << (end_time - start_time + 0.0) / 1000 << "(s)" << endl;
}
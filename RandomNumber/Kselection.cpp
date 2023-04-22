//
// Created by lhc456 on 2023/4/22.
//
#include <iostream>
#include "RandomNumber.h"

using namespace std;
//确定性算法中的划分函数


template<class T>
int Partition(T R[], int low, int high) {
    int i = low, j = high, pivot = R[low]; //用序列的第一个元素作为基准元素
    while (i < j)  //从序列的两端交替向中间扫描，直至i等于j为止
    {
        while (i < j && R[j] >= pivot) //pivot相当于在位置i上
            j--;  //从右向左扫描，查找第1个小于pivot的元素
        if (i < j) //表示找到了<pivot的元素
            swap(R[i++], R[j]); //交换R[i]和R[j]，交换后i执行加1操作
        while (i < j && R[i] <= pivot)
            i++; //从左向右扫描，查找第1个大于pivot的元素
        if (i < j) //表示找到了大于pivot的元素
            swap(R[i], R[j--]);//交换R[i]和R[j]，交换后j执行减1操作
    }
    return j;
}


template<class Type>
Type select(Type a[], int left, int right, int k) {
    RandomNumber rnd;
    if (left >= right)
        return a[left];
    int i = left, j = rnd.random(right - left + 1) + left;
    swap(a[i], a[j]);
    j = Partition(a, left, right);
    int count = j - left + 1;
    cout << "count=" << count << endl;
    if (count < k)
        select(a, j + 1, right, k - count);
    else
        select(a, left, j, k);
}


int main(int argc, char **argv) {
    int a[] = {5, 8, 2, 9, 10, 3, 111, 45, 34, 32, 56};
    int left = 0;
    int right = sizeof(a) / sizeof(int);
    int k;
    cout << "请输入要找的第k小的k:";
    cin >> k;
    while (k < 0 || k > right) {
        cout << "k不合法，请重新输入";
        cin >> k;
    }
    int xk = select(a, left, right - 1, k);
    cout << "第" << k << "小元素为：" << xk << endl;
    return 0;
}

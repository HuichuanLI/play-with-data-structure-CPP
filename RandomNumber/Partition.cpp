//
// Created by lhc456 on 2023/4/22.
//
#include <iostream>
#include "RandomNumber.h"

using namespace std;

//确定性算法中的划分函数
int Partition(int R[], int low, int high) {
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

//随机划分函数
int RandPartition(int a[], int low, int high) //随机划分
{
    RandomNumber rnd;
    int i = rnd.random(high - low + 1) + low;
    swap(a[low], a[i]);
    int j = Partition(a, low, high);
    return j;
}

void rqs(int a[], int left, int right)//随机快速排序
{
    if (left < right) {
        int p = RandPartition(a, left, right);
        rqs(a, left, p - 1);
        rqs(a, p + 1, right);
    }
}

int main(int argc, char **argv) {
    int a[] = {5, 8, 2, 9, 10, 3, 111, 45, 34, 32, 56};
    int left = 0;
    int right = sizeof(a) / sizeof(int);
    rqs(a, left, right - 1);
    for (int i = 0; i < right; i++)
        cout << a[i] << "  ";
    cout << endl;
    return 0;
}

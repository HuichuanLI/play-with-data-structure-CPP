//
// Created by lhc456 on 2023/5/7.
//
#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>
#include "MaxHeap.h"
#include "SortTestHelper.h"


using namespace std;

// heapSort1, 将所有的元素依次添加到堆中, 在将所有元素从堆中依次取出来, 即完成了排序
// 无论是创建堆的过程, 还是从堆中依次取出元素的过程, 时间复杂度均为O(nlogn)
// 整个堆排序的整体时间复杂度为O(nlogn)
template<typename T>
void heapSort1(T arr[], int n) {

    MaxHeap<T> maxheap = MaxHeap<T>(n);
    for (int i = 0; i < n; i++)
        maxheap.insert(arr[i]);

    for (int i = n - 1; i >= 0; i--)
        arr[i] = maxheap.extractMax();

}

// heapSort2, 借助我们的heapify过程创建堆
// 此时, 创建堆的过程时间复杂度为O(n), 将所有元素依次从堆中取出来, 实践复杂度为O(nlogn)
// 堆排序的总体时间复杂度依然是O(nlogn), 但是比上述heapSort1性能更优, 因为创建堆的性能更优
template<typename T>
void heapSort2(T arr[], int n) {

    MaxHeap<T> maxheap = MaxHeap<T>(arr, n);
    for (int i = n - 1; i >= 0; i--)
        arr[i] = maxheap.extractMax();

}


// 测试 MaxHeap
int main() {
    MaxHeap<int> maxheap = MaxHeap<int>(100);

    srand(time(NULL));
    int n = 100;    // 随机生成n个元素放入最大堆中
    for (int i = 0; i < n; i++) {
        maxheap.insert(rand() % 100);
    }

    int *arr = new int[n];
    // 将maxheap中的数据逐渐使用extractMax取出来
    // 取出来的顺序应该是按照从大到小的顺序取出来的
    for (int i = 0; i < n; i++) {
        arr[i] = maxheap.extractMax();
        cout << arr[i] << " ";
    }
    cout << endl;

    // 确保arr数组是从大到小排列的
    for (int i = 1; i < n; i++)
        assert(arr[i - 1] >= arr[i]);

    delete[] arr;


    n = 1000000;

    // 测试1 一般性测试
    cout << "Test for random array, size = " << n << ", random range [0, " << n << "]" << endl;
    int *arr1 = SortTestHelper::generateRandomArray(n, 0, n);
    int *arr2 = SortTestHelper::copyIntArray(arr1, n);
    int *arr3 = SortTestHelper::copyIntArray(arr1, n);
    int *arr4 = SortTestHelper::copyIntArray(arr1, n);
    int *arr5 = SortTestHelper::copyIntArray(arr1, n);
    int *arr6 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Heap Sort 1", heapSort1, arr5, n);
    SortTestHelper::testSort("Heap Sort 2", heapSort2, arr6, n);


    return 0;

}
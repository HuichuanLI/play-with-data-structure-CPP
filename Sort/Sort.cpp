//
// Created by lhc456 on 2023/5/1.
//

#include "Sort.h"

/* Function to print an array */
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


int main() {
    std::vector<int> arr = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    selection_sort<std::vector<int>::iterator>(arr.begin(), arr.end());
    printf("Sorted array: \n");
//    printArray(arr, n);
    return 0;
}
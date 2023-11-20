#include "Sorting.h"

void PrintArray(int* arr, int len) {
    for (int i = 0; i < len; i++)
        printf(" %d", arr[i]);
    printf("\n");
}

void SelectionSort(int* arr, int len) {
    for (int i = 0; i < len - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < len; j++) {
            if (arr[minIdx] > arr[j])
                minIdx = j;
        }
        int tmp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = tmp;
    }
}

void InsertionSort(int* arr, int len) {
    for (int i = 1; i < len; i++) {
        int idx = i, target = arr[i];
        while (idx-- && arr[idx] > target) {
            arr[idx + 1] = arr[idx];
        }
        arr[idx + 1] = target;
    }
}

int* CreateArray(int n) {
    int* array = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", array + i);
    return array;
}
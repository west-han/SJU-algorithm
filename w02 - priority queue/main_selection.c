#include <stdio.h>
#include <stdlib.h>
#include "Sorting.h"

int main() {
    int* arr = NULL;
    int n;
    scanf("%d", &n);

    arr = CreateArray(n);
    SelectionSort(arr, n);

    PrintArray(arr, n);
}
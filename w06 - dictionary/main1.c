#include <stdio.h>
#include <stdlib.h>

int rBinarySearch(const int arr[], int left, int right, const int key)
{
    int mid = (right + left) / 2;
    if(left > right){
        return right;
    }
    else if(arr[mid] > key){
        return rBinarySearch(arr, left, mid - 1, key);
    }
    else if(arr[mid] < key){
        return rBinarySearch(arr, mid + 1, right, key);
    }
    else{
        return mid;
    }
}


int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    int* arr = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++)
        scanf("%d", arr+i);

    printf("%d", rBinarySearch(arr, 0, n-1, k));
    free(arr);
}

// 8 -7 -92 -31 -7 4 14 20 29 44
// 8 39 -92 -31 -7 4 14 20 29 44
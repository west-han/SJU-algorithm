#include <stdio.h>
#include <stdlib.h>

int BinarySearch(int arr[], int n, int key)
{
    int left = 0;
    int right = n - 1;
    int mid;

    while(left <= right){
        mid = (right + left) / 2;

        if(arr[mid] == key){
            return mid;
        }
        else if(arr[mid] < key){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    
    return left;
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k); 
    int* arr = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++)
        scanf("%d", arr+i);

    printf(" %d", BinarySearch(arr, n, k));
    free(arr);
}
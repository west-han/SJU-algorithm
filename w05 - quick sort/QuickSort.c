
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void _Swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int inPlacePartition(int arr[], int l, int r, int k)
{
    int pivot = arr[k];
    int low = l + 1;
    int high = r;

    _Swap(arr+l, arr+k);

    while(low <= high){
        while(arr[low] <= pivot && low <= high) {
            low++;
        }
        while(arr[high] >= pivot && high >= low) {
            high--;
        }
        if(low < high){
            _Swap(arr+low, arr+high);
        }
    }
    
    _Swap(arr+l, arr+high);

    return high;
}

int findPivot(int arr[], int l, int r)
{
    return rand() % (r - l + 1) + l;
}

void inPlaceQuickSort(int arr[], int l, int r)
{
    int index;
    if(l >= r)
        return;
    int k = findPivot(arr, l, r);
    index = inPlacePartition(arr, l, r, k);
    inPlaceQuickSort(arr, l, index - 1);
    inPlaceQuickSort(arr, index + 1, r);
}

int main(){
    srand(time(NULL));
    int n;
    int* arr;
    scanf("%d", &n);
    arr = (int*)malloc(sizeof(int) * n);
    for(int i = 0, num = 0; i < n; i++){
        scanf("%d", &num);
        arr[i] = num;
    }
    inPlaceQuickSort(arr, 0, n - 1);
    for(int i = 0; i < n; i++)
        printf(" %d", arr[i]);

    free(arr);
}
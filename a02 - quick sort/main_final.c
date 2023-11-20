#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <windows.h>

typedef enum
{
    DET1, DET3, RAN1, RAN3
} Mode;

typedef struct _indices {
    int left, right;
} Indices;

const int g_n = 100000;
const int g_limits[] = { 1, 100, 500, 1000 };

int* CreateArray();
int* CopyArray(const int arr[]);

static void _Swap(int* a, int* b);
static int _GetMedian(const int arr[], const int a, const int b, const int c);
static int _FindPivot(const int arr[], const int l, const int r, const Mode mode);
static Indices _InplacePartition(int arr[], const int l, const int r, const int pivotIdx);

void rQuickSort(int arr[], int l, int r, int limits, const Mode mode);

void InsertionSort(int arr[], const int n);
void QuickSort(int arr[], const int limitsIdx, const Mode mode);

int main()
{
    srand(time(NULL));
    LARGE_INTEGER start, end;
    LARGE_INTEGER ticksPerSecond;
    double elapsedTime = 0.0;
    int* arr = CreateArray();
    int* tmpArr = NULL;
    QueryPerformanceFrequency(&ticksPerSecond);
    printf("Limit\tdeter1\t\tdeter3\t\trandom1\t\trandom3");

    for (int i = 0; i < 4; i++) {
        printf("\n%d\t", g_limits[i]);
        for (int j = 0; j < 4; j++) {
            tmpArr = CopyArray(arr);

            QueryPerformanceCounter(&start);
            QuickSort(tmpArr, i, j);
            QueryPerformanceCounter(&end);

            elapsedTime = (double)(end.QuadPart - start.QuadPart) / (double)ticksPerSecond.QuadPart;
            printf("%lf\t", elapsedTime);
            free(tmpArr);
        }
    }
}

void QuickSort(int arr[], const int limitsIdx, const Mode mode)
{
    rQuickSort(arr, 0, g_n - 1, g_limits[limitsIdx], mode);

    if (g_limits[limitsIdx] > 1) {
        InsertionSort(arr, g_n);
    }
}

void rQuickSort(int arr[], const int l, const int r, const int limits, const Mode mode)
{
    if (r - l > limits) { // 배열 크기 검사
        int pivotIdx = _FindPivot(arr, l, r, mode);
        Indices indices = _InplacePartition(arr, l, r, pivotIdx);
        rQuickSort(arr, l, indices.left, limits, mode);  // LT
        rQuickSort(arr, indices.right, r, limits, mode); // GT
    }
}

// 배열의 각 원소를 pivot과 비교해서 LT, EQ, GT 3 개의 그룹으로 분할하는 함수
static Indices _InplacePartition(int arr[], const int l, const int r, const int pivotIdx)
{
    int pivot = arr[pivotIdx];
    int low = l;                          // LT와 EQ의 경계(EQ의 첫번째 인덱스)
    int mid = l;                          // 배열 순회를 위한 인덱스
    int high = r;                         // EQ와 GT의 경계(GT의 첫번째 인덱스)

    while (mid <= high) {
        if (arr[mid] > pivot) {           // pivot보다 큰 값을 만나면 GT로 이동
            _Swap(arr + mid, arr + high);
            high--;
        }
        else if (arr[mid] < pivot) {      // pivot보다 작은 값을 만나면 LT로 이동
            _Swap(arr + low, arr + mid);
            low++;
            mid++;
        }
        else {                            // pivot과 같은 값을 만나면 그대로 두고 다음 셀 검사
            mid++;
        }
    }

    return (Indices) { low - 1, high };   // LT의 마지막 인덱스와 GT의 첫번째 인덱스를 구조체 리터럴로 묶어서 반환
}

static int _FindPivot(const int arr[], const int l, const int r, const Mode mode)
{
    if (mode == DET1) {
        return r;
    }
    else if (mode == RAN1) {
        return ((((long)rand() << 15) | rand()) % (r - l + 1) + l);
    }
    else if (r - l <= 1) {
        return l;
    }
    else if (mode == DET3) {
        int mid = (l + r) >> 1;
        return _GetMedian(arr, l, mid, r);
    }
    else if (mode == RAN3) {
        int n1, n2, n3;
        n1 = ((((long)rand() << 15) | rand()) % (r - l + 1) + l);
        n2 = ((((long)rand() << 15) | rand()) % (r - l + 1) + l);
        n3 = ((((long)rand() << 15) | rand()) % (r - l + 1) + l);
        return _GetMedian(arr, n1, n2, n3);
    }
    return 0;
}

int* CreateArray()
{
    int* retArr = (int*)malloc(sizeof(int) * g_n);
    if (retArr == NULL) {
        puts("Memory Allocation Failed.");
        exit(-1);
    }
    for (int i = 0; i < g_n; i++) {
        retArr[i] = ((((long long)rand() << 15) | rand()) % g_n) + 1;
    }
    return retArr;
}

int* CopyArray(const int arr[]) {
    int* retArr = (int*)malloc(sizeof(int) * g_n);
    if (retArr == NULL) {
        puts("Memory Allocation Failed.");
        exit(-1);
    }
    memcpy(retArr, arr, sizeof(int) * g_n);
    return retArr;
}

void InsertionSort(int arr[], const int n)
{
    for (int i = 1; i < n; i++) {
        int j = i;
        int save = arr[i];

        while (j > 0 && arr[j - 1] > save) {
            arr[j] = arr[j - 1];
            j--;
        }

        arr[j] = save;
    }
}

static int _GetMedian(const int arr[], const int a, const int b, const int c)
{
    if (arr[a] >= arr[b]) {
        if (arr[b] >= arr[c])
            return b;
        else if (arr[a] <= arr[c])
            return a;
        else
            return c;
    }
    else if (arr[a] >= arr[c])
        return a;
    else if (arr[c] >= arr[b])
        return b;
    else
        return c;
}

static void _Swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

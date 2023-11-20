#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void CaseA(int n);
void CaseB(int n);
void CaseC(int n);
void SelectionSort(int* arr, int len);
void InsertionSort(int* arr, int len);
void TestLoopA(int n);
void TestLoopB(int n);
void TestLoopC(int n);

int main() {
	TestLoopA(500);
	//A. a) 같은 n에 대해 5번씩 수행한 결과, 삽입정렬이 조금 더 빠르게 수행된 경우가 많았다.
	//A. b) n을 (500 → 5,000 → 50,000) 순으로 10배씩 늘렸을 때, 두 정렬 모두 수행 시간이 약 100배씩 증가했다.

	TestLoopB(500);
	//B. a) 같은 n에 대해 5번씩 수행한 결과, 모든 경우에 대해 삽입정렬이 훨씬 빠른 시간 안에 끝났다.
	//B. b) n을 (500 → 5,000 → 50,000) 순으로 10배씩 늘렸을 때, 선택정렬은 수행 시간이 약 100배씩 늘어났다.
	//      삽입정렬의 경우는 500에서 5,000으로 늘렸을 때 약 10배, 5,000에서 50,000으로 늘렸을 때 약 2 ~ 5배로 늘었다.

	TestLoopC(500);
	//C. a) 같은 n에 대해 5번씩 수행한 결과, 선택정렬이 더 빠른 시간 안에 끝나는 경우가 많았다.
	//C. b) 두 정렬 모두 n을 500에서 5,000으로 10배 늘렸을 때 수행 시간이 약 100배로 늘었고, n을 5,000에서 50,000으로 10배 늘렸을 때 수행시간이 약 100 ~ 200배로 증가했다.
}

void TestLoopA(int n) {
	for (int i = 0; i < 5; i++) {
		printf("Case A.a [test %d] - %d elements\n", i + 1, n);
		CaseA(n);
		printf("\n");
	}

	for (int i = 0; i < 3; i++) {
		printf("Case A.b - %d elements\n", n);
		CaseA(n);
		printf("\n");
		n *= 10;
	}
}

void TestLoopB(int n) {
	for (int i = 0; i < 5; i++) {
		printf("Case B.a [test %d] - %d elements\n", i + 1, n);
		CaseB(n);
		printf("\n");
	}

	for (int i = 0; i < 3; i++) {
		printf("Case B.b - %d elements\n", n);
		CaseB(n);
		printf("\n");
		n *= 10;
	}
}

void TestLoopC(int n) {
	for (int i = 0; i < 5; i++) {
		printf("Case C.a [test %d] - %d elements\n", i + 1, n);
		CaseC(n);
		printf("\n");
	}

	for (int i = 0; i < 3; i++) {
		printf("Case C.b - %d elements\n", n);
		CaseC(n);
		printf("\n");
		n *= 10;
	}
}

void _CopyArray(int* src, int* dst, int n) {
	for (int i = 0; i < n; i++)
		dst[i] = src[i];
}

void _SortDescendingOrder(int* arr, int len) {
	for (int i = 1; i < len; i++) {
		int idx = i, target = arr[i];
		while (idx-- && arr[idx] < target) {
			arr[idx + 1] = arr[idx];
		}
		arr[idx + 1] = target;
	}
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

void CaseA(int n) {
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	int* a, * b;
	srand(time(NULL));
	QueryPerformanceFrequency(&ticksPerSec);

	a = (int*)malloc(sizeof(int) * n);
	b = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
		a[i] = rand() % INT_MAX;
	_CopyArray(a, b, n);

	QueryPerformanceCounter(&start);
	SelectionSort(a, n);
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("Selection Sort: %.12fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	QueryPerformanceCounter(&start);
	InsertionSort(b, n);
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("Insertion Sort: %.12fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	free(a);
	free(b);
}



void CaseB(int n) {
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	int* a, * b;
	srand(time(NULL));
	QueryPerformanceFrequency(&ticksPerSec);

	a = (int*)malloc(sizeof(int) * n);
	b = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
		a[i] = rand() % INT_MAX;

	// sorting each array
	InsertionSort(a, n);
	_CopyArray(a, b, n);

	QueryPerformanceCounter(&start);
	SelectionSort(a, n);
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("Selection Sort: %.12fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	QueryPerformanceCounter(&start);
	InsertionSort(b, n);
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("Insertion Sort: %.12fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	free(a);
	free(b);
}

void CaseC(int n) {
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	int* a, * b;
	srand(time(NULL));
	QueryPerformanceFrequency(&ticksPerSec);

	a = (int*)malloc(sizeof(int) * n);
	b = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		a[i] = rand() % INT_MAX;
	}

	// sorting each array
	_SortDescendingOrder(a, n);
	_CopyArray(a, b, n);

	QueryPerformanceCounter(&start);
	SelectionSort(a, n);
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("Selection Sort: %.12fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	QueryPerformanceCounter(&start);
	InsertionSort(b, n);
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("Insertion Sort: %.12fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	free(a);
	free(b);
}
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
	//A. a) ���� n�� ���� 5���� ������ ���, ���������� ���� �� ������ ����� ��찡 ���Ҵ�.
	//A. b) n�� (500 �� 5,000 �� 50,000) ������ 10�辿 �÷��� ��, �� ���� ��� ���� �ð��� �� 100�辿 �����ߴ�.

	TestLoopB(500);
	//B. a) ���� n�� ���� 5���� ������ ���, ��� ��쿡 ���� ���������� �ξ� ���� �ð� �ȿ� ������.
	//B. b) n�� (500 �� 5,000 �� 50,000) ������ 10�辿 �÷��� ��, ���������� ���� �ð��� �� 100�辿 �þ��.
	//      ���������� ���� 500���� 5,000���� �÷��� �� �� 10��, 5,000���� 50,000���� �÷��� �� �� 2 ~ 5��� �þ���.

	TestLoopC(500);
	//C. a) ���� n�� ���� 5���� ������ ���, ���������� �� ���� �ð� �ȿ� ������ ��찡 ���Ҵ�.
	//C. b) �� ���� ��� n�� 500���� 5,000���� 10�� �÷��� �� ���� �ð��� �� 100��� �þ���, n�� 5,000���� 50,000���� 10�� �÷��� �� ����ð��� �� 100 ~ 200��� �����ߴ�.
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
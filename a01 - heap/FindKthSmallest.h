#pragma once

// 난수 배열 생성
int* buildList(int n, int min, int max);

// k번째로 작은 값 반환
int findKthSmallest(int* L, int n, int k);

// 동적할당한 공간에 난수 배열 복사한 뒤 주소값 반환
int* allocAndCopyArr(const int* src, int* p_dest, int numElem);

#pragma once

// 비재귀적 방식으로 상향식 최소힙 생성
void buildHeap(int arr[], const int lastIdx);

// 최소 키 반환
// 키 삭제 후 힙의 크기 변경을 위해 주소 전달
int removeMin(int arr[], int* const p_lastIdx);
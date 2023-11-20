#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct _listNode {
    int data;
    struct _listNode* next;
} LNode;

void LInsert(LNode** p_listHead, int data);
void LDiscard(LNode** p_listHead);
void mergeSort(LNode** p_listHead, int n);


int main() {
    int n = 0;
    LNode* listHead = NULL;
    scanf("%d", &n);

    for (int i = 0, num = 0; i < n; i++) {
        scanf("%d", &num);
        LInsert(&listHead, num);
    }
    
    mergeSort(&listHead, n);

    LDiscard(&listHead);

    return 0;
}
 
 
LNode* merge(LNode* subList1, LNode* subList2)
{
    LNode* retList = NULL;
    LNode* currentNode = NULL;

    if (subList1 == NULL)
        return subList2;
    else if (subList2 == NULL)
        return subList1;

    if (subList1->data < subList2->data) {
        retList = subList1;
        subList1 = subList1->next;
    }
    else {
        retList = subList2;
        subList2 = subList2->next;
    }
    currentNode = retList;

    while (subList1 && subList2) {
        if (subList1->data < subList2->data) {
            currentNode->next = subList1;
            subList1 = subList1->next;
        }
        else {
            currentNode->next = subList2;
            subList2 = subList2->next;
        }
        currentNode = currentNode->next;
    }

    while (subList1) {
        currentNode->next = subList1;
        currentNode = subList1;
        subList1 = subList1->next;
    }

    while (subList2) {
        currentNode->next = subList2;
        currentNode = subList2;
        subList2 = subList2->next;
    }

    return retList;
}

void partition(LNode* listHead, LNode** p_subList1, LNode** p_subList2, int k) {
    LNode* currentNode = listHead;
    *p_subList1 = listHead;
    for (int i = 0; i < k / 2 - 1; i++)
        currentNode = currentNode->next;
    *p_subList2 = currentNode->next;
    currentNode->next = NULL;
}

void mergeSort(LNode** p_listHead, int n) {
    LNode* listHead = *p_listHead;

    if(listHead == NULL || listHead->next == NULL){
      return;
    }
 
    LNode* subList1;
    LNode* subList2;
 
    partition(listHead, &subList1, &subList2, n);
  
    mergeSort(&subList1, n / 2);
    mergeSort(&subList2, (int)(n / 2 + 0.5));
    *p_listHead = merge(subList1, subList2);
}


void LInsert(LNode** p_listHead, int data) {
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    newNode->data = data;
    newNode->next = NULL;

    if (*p_listHead == NULL) {
        *p_listHead = newNode;
    }
    else {
        LNode* p_node = *p_listHead;
        while (p_node->next != NULL) {
            p_node = p_node->next;
        }
        p_node->next = newNode;
    }
}

void LDiscard(LNode** p_listHead) {
    LNode* p_node = *p_listHead;
    LNode* p_delNode = p_node;
    while (p_node != NULL) {
        printf(" %d", p_node->data);
        p_delNode = p_node;
        p_node = p_node->next;
        free(p_delNode);
    }
    *p_listHead = NULL;
}
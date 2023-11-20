#pragma once

typedef char ListElem;
typedef struct _listNode ListNode;
typedef struct _doubleLinkedList List;

struct _listNode {
    ListElem elem;
    ListNode* prev;
    ListNode* next;
};

struct _doubleLinkedList {
    ListNode* head;
    ListNode* trailer;
    int numOfData;
};

void ListInit(List*);
void Add(List*, int, ListElem);
ListElem Delete(List*, int);
ListElem Get(const List*, int);
void Print(const List*);
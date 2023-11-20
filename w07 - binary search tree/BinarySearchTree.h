#pragma once

typedef struct _bstNode{
    struct _bstNode* lChild;
    struct _bstNode* rChild;
    struct _bstNode* parent;
    int key;
} Node;

void initBST(Node** p_bst);
int findElement(Node* bst, const int key);
void insertItem(Node* bst, const int key);
Node* treeSearch(Node* bst, const int key);
int removeElement(Node* bst, const int key);
Node* inOrderSucc(Node* node);
void preOrderTraversal(Node* node);
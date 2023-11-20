//#include "BinarySearchTree.h"
//#include <stdio.h>
//#include <stdlib.h>
//
//Node* g_root = NULL;
//
//static inline _Bool isExternal(const Node* node)
//{
//    return (node->lChild == NULL && node->rChild == NULL);
//}
//
//static inline _Bool isInternal(const Node* node)
//{
//    return !isExternal(node);
//}
//static inline _Bool isRoot(const Node* node)
//{
//    return node->parent == NULL;
//}
//
//static Node* getSibling(const Node* node){
//    if(isRoot(node))
//        exit(-1);
//    Node* parent = node->parent;
//    return ((parent->lChild) == node) ? parent->rChild : parent->lChild;
//}
//
//static void expandExternal(Node* const node)
//{
//    Node* lChild = (Node*)malloc(sizeof(Node));
//    Node* rChild = (Node*)malloc(sizeof(Node));
//    lChild->lChild = NULL;
//    lChild->rChild = NULL;
//    lChild->parent = node;
//    node->lChild = lChild;
//    rChild->lChild = NULL;
//    rChild->rChild = NULL;
//    rChild->parent = node;
//    node->rChild = rChild;
//}
//
//static Node* reduceExternal(Node* node)
//{
//    Node* parent = node->parent;
//    Node* sibling = getSibling(node);
//    if(isRoot(parent)){
//        g_root = sibling;
//        sibling->parent = NULL;
//    }
//    else{
//        Node* gParent = parent->parent;
//        sibling->parent = gParent;
//        if(gParent->lChild == parent){
//            gParent->lChild = sibling;
//        }
//        else if(gParent->rChild == parent){
//            gParent->rChild = sibling;
//        }
//    }
//    
//    free(parent);
//    free(node);
//    return sibling;
//}
//
//void initBST(Node** p_bst)
//{
//    *p_bst = (Node*)malloc(sizeof(Node));
//    (*p_bst)->lChild = NULL;
//    (*p_bst)->rChild = NULL;
//    (*p_bst)->parent = NULL;
//}
//
//int findElement(Node* bst, const int key)
//{
//    Node* foundNode = treeSearch(bst, key);
//    if(isExternal(foundNode)){
//        puts("X");
//        return -1;
//    }
//    else{
//        return foundNode->key;
//    }
//}
//
//void insertItem(Node* bst, const int key)
//{
//    Node* currentNode = (Node*)bst;
//    while(isInternal(currentNode) && currentNode->key != key){
//        currentNode = (key < currentNode->key) ? currentNode->lChild : currentNode->rChild;
//    }
//    currentNode->key = key;
//    expandExternal(currentNode);
//}
//
//Node* treeSearch(Node* bst, const int key)
//{
//    while(bst->key != key && isInternal(bst)){
//        if(key < bst->key){
//            bst = bst->lChild;
//        }
//        else if(key > bst->key){
//            bst = bst->rChild;
//        }
//    }
//
//    return bst;
//}
//
//int removeElement(Node* bst, const int key){
//    Node* foundNode = treeSearch(bst, key);
//    if(isExternal(foundNode)){
//        puts("X");
//        return -1;
//    }
//
//    int retData = foundNode->key;
//
//    if(isExternal(foundNode->lChild)){
//        reduceExternal(foundNode->lChild);
//    }
//    else if(isExternal(foundNode->rChild)){
//        reduceExternal(foundNode->rChild);
//    }
//    else{
//        Node* inOrderSuccessor = inOrderSucc(foundNode);
//        foundNode->key = inOrderSuccessor->key;
//        reduceExternal(inOrderSuccessor->lChild);
//    }
//    return retData;
//}
//
//
//Node* inOrderSucc(Node* node)
//{
//    Node* currentNode = node->rChild;
//    while(isInternal(currentNode->lChild)){
//        currentNode = currentNode->lChild;
//    }
//    return currentNode;
//}
//
//void preOrderTraversal(Node *node)
//{
//    if(isInternal(node)){
//        printf(" %d", node->key);
//        preOrderTraversal(node->lChild);
//        preOrderTraversal(node->rChild);
//    }
//}
//
//
//// i 5 i 6 i 4 i 2 i 3 p d 5 p d 4 p d 6 p


#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct _node {
    struct _node* lChild;
    struct _node* rChild;
    struct _node* parent;
    int key;
} Node;

static _Bool isInternal(const Node* node);
static _Bool isExternal(const Node* node);
static _Bool isRoot(const Node* node);
static Node* getSibling(const Node* node);

void expandExternal(Node* node);
Node* reduceExternal(Node** p_root, Node* node);
Node* treeSearch(Node* root, const int key);
_Bool findElement(Node* root, const int key, int* outParam);
Node* findInOrderSucc(const Node* node);
_Bool insertItem(Node** p_root, const int key);
void preOrderPrintTree(Node* root);
_Bool removeElement(Node** p_root, const int key, int* outParam);

int main()
{
    char c;
    Node* root = (Node*)calloc(1, sizeof(Node));

    while ((c = getchar()) != 'q')
    {
        switch (c)
        {
            int key;
            int outKey;

        case 'i':
            scanf("%d", &key);
            getchar();
            insertItem(&root, key);
            break;

        case 's':
        {
            scanf("%d", &key);
            getchar();
            if (findElement(root, key, &outKey))
            {
                printf("%d\n", outKey);
            }
            else
            {
                puts("X");
            }
            break;
        }

        case 'd':
        {
            scanf("%d", &key);
            getchar();
            if (removeElement(&root, key, &outKey))
            {
                printf("%d\n", outKey);
            }
            else
            {
                puts("X");
            }
            break;
        }
        case 'p':
            preOrderPrintTree(root);
            putchar('\n');
        }
    }

    return 0;
}

static _Bool isInternal(const Node* node)
{
    return (node->lChild != NULL || node->rChild != NULL);
}

static _Bool isExternal(const Node* node)
{
    return (node->lChild == NULL && node->rChild == NULL);
}

static _Bool isRoot(const Node* node)
{
    return (node->parent == NULL);
}

static Node* getSibling(const Node* node)
{
    Node* retNode = node->parent;
    if (node == retNode->lChild)
    {
        retNode = retNode->rChild;
    }
    else
    {
        retNode = retNode->lChild;
    }
    return retNode;
}

void expandExternal(Node* node)
{
    Node* left = (Node*)calloc(1, sizeof(Node));
    Node* right = (Node*)calloc(1, sizeof(Node));

    left->parent = node;
    node->lChild = left;

    right->parent = node;
    node->rChild = right;
}

Node* reduceExternal(Node** p_root, Node* node)
{
    Node* z = node;
    Node* p = z->parent;
    Node* g = NULL;
    Node* zs = getSibling(z);

    if (isRoot(p))
    {
        *p_root = zs;
        zs->parent = NULL;
    }
    else
    {
        g = p->parent;
        zs->parent = g;
        if (p == g->lChild)
        {
            g->lChild = zs;
        }
        else
        {
            g->rChild = zs;
        }
    }

    free(z);
    free(p);
    return zs;
}

Node* treeSearch(Node* root, const int key)
{
    Node* retNode = root;
    while (isInternal(retNode))
    {
        if (retNode->key == key)
        {
            break;
        }
        else if (key < retNode->key)
        {
            retNode = retNode->lChild;
        }
        else
        {
            retNode = retNode->rChild;
        }
    }

    return retNode;
}

_Bool findElement(Node* root, const int key, int* outParam)
{
    Node* foundNode = treeSearch(root, key);
    if (isExternal(foundNode))
    {
        return 0;
    }
    else
    {
        *outParam = foundNode->key;
        return 1;
    }
}

Node* findInOrderSucc(const Node* node)
{
    Node* retNode = node->rChild;

    if (isExternal(node))
    {
        return;
    }

    while (isInternal(retNode->lChild))
    {
        retNode = retNode->lChild;
    }

    return retNode;
}

_Bool insertItem(Node** p_root, const int key)
{
    Node* foundNode = treeSearch(*p_root, key);
    if (isInternal(foundNode))
    {
        return 0;
    }

    foundNode->key = key;
    expandExternal(foundNode);
    return 1;
}

void preOrderPrintTree(Node* root)
{
    if (isExternal(root))
    {
        return;
    }

    printf(" %d", root->key);
    preOrderPrintTree(root->lChild);
    preOrderPrintTree(root->rChild);
}

_Bool removeElement(Node** p_root, const int key, int* outParam)
{
    Node* foundNode = treeSearch(*p_root, key);
    if (isExternal(foundNode))
    {
        return 0;
    }
    *outParam = foundNode->key;
    Node* z = (*p_root)->lChild;
    Node* zs = NULL;
    Node* y = NULL;
    if (isInternal(z))
    {
        z = getSibling(z);
    }
    if (isExternal(z))
    {
        zs = reduceExternal(p_root, z);
    }
    else
    {
        y = findInOrderSucc(foundNode);
        z = y->lChild;
        foundNode->key = y->key;
        zs = reduceExternal(p_root, z);
    }

    return 1;
}
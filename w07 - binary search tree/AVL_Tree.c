#include "AVL_Tree.h"
#include <stdio.h>
#include <stdlib.h>

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

static _Bool isBalanced(const Node* node)
{
    int diff = ((node->lChild)->height) - ((node->rChild)->height);
    return abs(diff) <= 1;
}

static Node* getSibling(const Node* node)
{
    if (node->parent == NULL)
    {
        return NULL;
    }

    if(node == (node->parent)->lChild)
    {
        return (node->parent)->rChild;
    }
    else
    {
        return (node->parent)->lChild;
    }
}

void expandExternal(Node* node)
{
    Node* left = (Node*)calloc(1, sizeof(Node));
    Node* right = (Node*)calloc(1, sizeof(Node));

    left->parent = node;
    node->lChild = left;

    right->parent = node;
    node->rChild = right;
    node->height = 1;
}

Node* reduceExternal(Node** p_root, Node* node)
{
    Node* z = node;
    Node* p = z->parent;
    Node* g = NULL;
    Node* zs = getSibling(z);

    if(isRoot(p))
    {
        *p_root = zs;
        zs->parent = NULL;
    }
    else
    {
        g = p->parent;
        zs->parent = g;
        if(p == g->lChild)
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

static _Bool updateHeight(Node* node)
{
    int height = 0;
    if(node->lChild->height > node->rChild->height)
    {
        height = node->lChild->height + 1;
    }
    else
    {
        height = node->rChild->height + 1;
    }

    if(height != node->height)
    {
        node->height = height;
        return 1;
    }

    return 0;
}

Node* restructure(Node** p_root, Node* x, Node* y, Node* z)
{
    Node* a;
    Node* b;
    Node* c;
    Node* T0;
    Node* T1;
    Node* T2;
    Node* T3;

    if((z->key < y->key) && (y->key < x->key))
    {
        a = z;
        b = y;
        c = x;
        T1 = b->lChild;
        T2 = c->lChild;
    }
    else if((x->key < y->key) && (y->key < z->key))
    {
        a = x;
        b = y;
        c = z;
        T1 = a->rChild;
        T2 = b->rChild;
    }
    else if((z->key < x->key) && (x->key < y->key))
    {
        a = z;
        b = x;
        c = y;
        T1 = b->lChild;
        T2 = b->rChild;
    }
    else
    {
        a = y;
        b = x;
        c = z;
        T1 = b->lChild;
        T2 = b->rChild;
    }
    T0 = a->lChild;
    T3 = c->rChild;

    if(isRoot(z))
    {
        *p_root = b;
        b->parent = NULL;
    }
    else if((z->parent)->lChild == z)
    {
        (z->parent)->lChild= b;
        b->parent = z->parent;
    }
    else if((z->parent)->rChild == z)
    {
        (z->parent)->rChild = b;
        b->parent = z->parent;
    }

    a->lChild = T0;
    a->rChild = T1;
    T0->parent = a;
    T1->parent = a;
    updateHeight(a);

    c->lChild = T2;
    c->rChild = T3;
    T2->parent = c;
    T3->parent = c;
    updateHeight(c);

    b->lChild = a;
    b->rChild = c;
    a->parent = b;
    c->parent = b;
    updateHeight(b);

    return b;
}

Node* treeSearch(Node* root, const int key)
{
    Node* retNode = root;

    while (retNode->key != key && isInternal(retNode))
    {
        if (key < retNode->key)
        {
            retNode = retNode->lChild;
        }
        else if (key > retNode->key)
        {
            retNode = retNode->rChild;
        }
    }

    return retNode;
}

_Bool findElement(Node* root, const int key, int* outParam)
{
    Node* foundNode = treeSearch(root, key);
    if(isExternal(foundNode))
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

    while(isInternal(retNode->lChild))
    {
        retNode = retNode->lChild;
    }

    return retNode;
}

static void searchAndFixAfterInsertion(Node** p_root, Node* node)
{
    (node->lChild)->height = 0;
    (node->rChild)->height = 0;
    node->height = 1;

    if(isRoot(node))
    {
        return;
    }

    Node* z = node->parent;
    Node* y = NULL;
    Node* x = NULL;
    
    while(updateHeight(z) && isBalanced(z))
    {
        if(isRoot(z))
        {
            return;
        }

        z = z->parent;
    }

    if(isBalanced(z))
    {
        return;
    }

    if((z->lChild)->height > (z->rChild)->height)
    {
        y = z->lChild;
    }
    else
    {
        y = z->rChild;
    }
    if((y->lChild)->height > (y->rChild)->height)
    {
        x = y->lChild;
    }
    else
    {
        x = y->rChild;
    }

    restructure(p_root, x, y, z);
}

static void searchAndFixAfterRemoval(Node** p_root, Node* node)
{
    Node* z = node;
    Node* y = NULL;
    Node* x = NULL;
    if(node == NULL)
    {
        return;
    }

    while(updateHeight(z) & isBalanced(z))
    {
        if(isRoot(z))
        {
            return;
        }

        z = z->parent;
    }

    if(isBalanced(z))
    {
        return;
    }

    if((z->lChild)->height > (z->rChild)->height)
    {
        y = z->lChild;
    }
    else
    {
        y = z->rChild;
    }

    if((y->lChild)->height > (y->rChild)->height)
    {
        x = y->lChild;
    }
    else if((y->lChild)->height < (y->rChild)->height)
    {
        x = y->rChild;
    }
    else
    {
        if(z->lChild == y)
        {
            x = y->lChild;
        }
        else
        {
            x = y->rChild;
        }
    }

    Node* b = restructure(p_root, x, y, z);

    searchAndFixAfterRemoval(p_root, b->parent);
}

_Bool insertItem(Node** p_root, const int key)
{
    Node* foundNode = treeSearch(*p_root, key);
    if(isInternal(foundNode))
    {
        return 0;
    }

    foundNode->key = key;
    expandExternal(foundNode);
    searchAndFixAfterInsertion(p_root, foundNode);
    return 1;
}

void preOrderPrintTree(Node* root)
{
    if(isExternal(root))
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
    if(isExternal(foundNode))
    {
        return 0;
    }
    *outParam = foundNode->key;
    Node* z = foundNode->lChild;
    Node* zs = NULL;
    Node* y = NULL;
    if(isInternal(z))
    {
        z = getSibling(z);
    }
    if(isExternal(z))
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
    searchAndFixAfterRemoval(p_root, zs->parent);

    return 1;
}
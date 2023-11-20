#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int key;
    struct _node* next;
} Node;

typedef Node Slot;
typedef Slot** Table;

int hashFunc(const int key, const int m);
void tableInit(Table table, const int m);
void insertItem(Table table, const int key, const int m);
int removeItem(Table table, const int key, const int m);
int findItem(Table table, const int key, const int m);
void printTable(Table table, const int m);

int main()
{
    int m;
    scanf("%d", &m);
    getchar();
    Table hashTable = (Table)malloc(sizeof(Slot*) * m);
    tableInit(hashTable, m);
    char c;

    while((c = getchar()) != 'e'){
        int key;
        switch(c){
            case 'i':
                scanf("%d", &key);
                getchar();
                insertItem(hashTable, key, m);
                break;
            case 's':
                scanf("%d", &key);
                getchar();
                printf("%d\n", findItem(hashTable, key, m));
                break;
            case 'd':
                scanf("%d", &key);
                getchar();
                printf("%d\n", removeItem(hashTable, key, m));
                break;
            case 'p':
                printTable(hashTable, m);
        }
    }
}

int hashFunc(const int key, const int m)
{
    return key % m;
}

void tableInit(Table table, int m)
{
    for(int i = 0; i < m; i++){
        table[i] = NULL;
    }
}

void insertItem(Table table, const int key, const int m)
{
    int v = hashFunc(key, m);
    Slot* newSlot = malloc(sizeof(Slot));
    newSlot->next = table[v];
    newSlot->key = key;
    table[v] = newSlot;
}

int removeItem(Table table, const int key, const int m)
{
    int v = hashFunc(key, m);
    int retData = 0;
    if(table[v] == NULL){
        return 0;
    }
    Slot* targetSlot = table[v];
    Slot* beforeTarget;
    if(targetSlot->key == key){
        table[v] = targetSlot->next;
        free(targetSlot);
        return 1;
    }
    else{
        targetSlot = table[v]->next;
        beforeTarget = table[v];
        retData = 1;
    }
    
    while(targetSlot){
        retData++;

        if(targetSlot->key == key){
            break;
        }

        beforeTarget = beforeTarget->next;
        targetSlot = targetSlot->next;
    }

    if(targetSlot == NULL){
        retData = 0;
    }
    else{
        beforeTarget->next = targetSlot->next;
        free(targetSlot);
    }

    return retData;
}

int findItem(Table table, const int key, const int m)
{
    int v = hashFunc(key, m);
    Slot* targetSlot = table[v];
    int retData = 0;
    if(targetSlot == NULL){
        return 0;
    }
    while(targetSlot){
        retData++;
        
        if(targetSlot->key == key){
            return retData;
        }
        
        targetSlot = targetSlot->next;
    }

    return 0;
}

void printTable(Table table, const int m)
{
    Slot* currentSlot;
    for(int i = 0; i < m; i++){
        currentSlot = table[i];
        while(currentSlot){
            printf(" %d", currentSlot->key);
            currentSlot = currentSlot->next;
        }
    }
    putchar('\n');
}
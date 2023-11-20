#include <stdio.h>
#include <stdlib.h>

typedef int* Table;

int h1(const int key, const int m);
int h2(const int key, const int q);
void tableInit(Table table, const int m);
int insertItem(Table table, const int key, const int m, const int q);
int findItem(Table table, const int key, const int m, const int q);
void printTable(Table table, const int m);

int main()
{
    int m, n, q;
    scanf("%d %d %d", &m, &n, &q);
    getchar();
    Table hashTable = (Table)malloc(sizeof(int) * m);
    tableInit(hashTable, m);
    char c;

    while((c = getchar()) != 'e'){
        int key;
        switch(c){
            case 'i':
            {
                scanf("%d", &key);
                getchar();
                printf("%d\n", insertItem(hashTable, key, m, q));
                break;
            }
            case 's':
                scanf("%d", &key);
                getchar();
                printf("%d\n", findItem(hashTable, key, m, q));
                break;
            case 'p':
                printTable(hashTable, m);
        }
    }

    printTable(hashTable, m);
    
}

int h1(const int key, const int m)
{
    return key % m;
}

int h2(const int key, const int q)
{
    return q - (key % q);
}

void tableInit(Table table, const int m)
{
    for(int i = 0; i < m; i++){
        table[i] = 0;
    }
}

int insertItem(Table table, const int key, const int m, const int q)
{
    int count = -1;
    int v;
    do{
        ++count;
        v = (h1(key, m) + count * h2(key, q)) % m;
    } while(table[v] != 0 && putchar('C'));
    // && 연산자의 short circuit을 활용해 v가 0이 아닌 경우에만 'C' 출력

    table[v] = key;

    return v;
}

int findItem(Table table, const int key, const int m, const int q)
{
    int count = -1;
    int v;

    do{
        ++count;
        v = (h1(key, m) + count * h2(key, q)) % m;
    } while(table[v] != 0 && count < m && table[v] != key);

    if(count >= m || table[v] == 0){
        return -1;
    }
    else{
        printf("%d ", v);
        return table[v];
    }
}

void printTable(Table table, const int m)
{
    for(int i = 0; i < m; i++){
        printf(" %d", table[i]);
    }
    putchar('\n');
}

// 13 10 i 16110243 i 17011111 i 17012331 i 17012354 i 17013672 i 16012342 s 17012354 i 15013986 i 102067 i 113478 i 14012322 s 16110243 e
// 13 10 11 i 25 i 13 i 16 i 15 i 70 p i 28 i 31 i 20 i 14 s 20 s 27 i 38 e
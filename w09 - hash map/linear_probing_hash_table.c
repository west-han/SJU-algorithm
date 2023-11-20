#include <stdio.h>
#include <stdlib.h>

typedef int* Table;

int hashFunc(const int key, const int m);
void tableInit(Table table, const int m);
int insertItem(Table table, const int key, const int m);
int findItem(Table table, const int key, const int m);

int main()
{
    int m, n, insertCount = 0;
    scanf("%d %d", &m, &n);
    getchar();
    Table hashTable = (Table)malloc(sizeof(int) * m);
    tableInit(hashTable, m);
    char c;

    while((c = getchar()) != 'e'){
        int key;
        switch(c){
            case 'i':
            {
                if(insertCount < n){
                    insertCount++;
                    scanf("%d", &key);
                    getchar();
                    printf("%d\n", insertItem(hashTable, key, m));
                }
                break;
            }
            case 's':
                scanf("%d", &key);
                getchar();
                printf("%d\n", findItem(hashTable, key, m));
                break;
        }
    }
}

int hashFunc(const int key, const int m)
{
    return key % m;
}

void tableInit(Table table, const int m)
{
    for(int i = 0; i < m; i++){
        table[i] = 0;
    }
}

int insertItem(Table table, const int key, const int m)
{
    int count = -1;
    int v;
    do{
        ++count;
        v = hashFunc(key + count, m);
    } while(table[v] != 0 && putchar('C'));
    // && 연산자의 short circuit을 활용해 v가 0이 아닌 경우에만 'C' 출력

    table[v] = key;

    return v;
}

int findItem(Table table, const int key, const int m)
{
    int count = -1;
    int v;

    do{
        ++count;
        v = hashFunc(key + count, m);
    } while(table[v] != 0 && count < m && table[v] != key);

    if(count >= m || table[v] == 0){
        return -1;
    }
    else{
        printf("%d ", v);
        return table[v];
    }
}

// 13 10 i 16110243 i 17011111 i 17012331 i 17012354 i 17013672 i 16012342 s 17012354 i 15013986 i 102067 i 113478 i 14012322 s 16110243 e
#include <stdio.h>
#include <stdlib.h>
// open addressing - double hashing

typedef struct Bucket Bucket;
typedef struct HashTable HashTable;
typedef int (*HashFunction)(int key, int i); // 함수 포인터를 이용해 해시맵에 해시 함수 등록해서 사용

// 저장할 키 k가 0 <= k <= 99이므로 예외 코드로 세 자리 수 할당
typedef enum ExceptionCode
{
    NO_SUCH_KEY    = 100,
    DUPLICATED_KEY = 101,
    TABLE_OVERFLOW = 102 
} ExceptionCode;

// bucket의 상태를 나타내는 enum 자료형 정의
typedef enum BucketStatus
{
    EMPTY    = 0,
    ACTIVE   = 1,
    INACTIVE = -1
} Status;

struct Bucket
{
    int key;
    Status status;
};

struct HashTable
{
    int size;               // 해시테이블의 크기 (MAX = 23)
    Bucket *bucketArray;
    HashFunction hf;        // 해시 함수 포인터
};

// 해시테이블 초기화(버켓 배열 동적할당, 해시 함수 등록)
void constructHashTable(HashTable* table, const int size, HashFunction hf);
// 해시테이블에 해시 함수 등록
void setHashFunc(HashTable* table, HashFunction hf);

// Hash Map ADTs
int findElement(const HashTable *table, const int key);
int insertItem(HashTable *table, const int key);
int removeElement(HashTable *table, const int key);
void printHashTable(const HashTable *table);

// helper functions
void deactivate(HashTable *table, const int v);
void activate(HashTable* table, const int v);
_Bool inactive(const Status status);
_Bool active(const Status status);
_Bool empty(const Status status);
int getKey(const HashTable *table, const int v);
Status getStatus(const HashTable *table, const int v);

// second hash function
int h2(const int key)
{
    const int q = 17;
    return q - (key % q);
}

// first hash function
int h1(const int key, const int i)
{
    const int M = 23;
    return ((key % M) + (h2(key) * i)) % M;
}


int main()
{
    const int M = 23;
    HashTable table;
    constructHashTable(&table, M, h1);

    char cmd;

    while ((cmd = getchar()) != 'q') {
        switch (cmd) {
            int k;
            int output;

            // find element
            case 'f' : {
                scanf("%d", &k);
                getchar();
                output = findElement(&table, k);

                if (output == NO_SUCH_KEY) {
                    puts("NoSuchKey");
                }
                else {
                    printf("%d\n", output);
                }
                break;
            }
            // insert element
            case 'i' : {
                scanf("%d", &k);
                getchar();
                output = insertItem(&table, k);

                if (output == TABLE_OVERFLOW) {
                    puts("Hash table is full.");
                }
                else if (output == DUPLICATED_KEY) {
                    printf("Key %d is duplicated.\n", k);
                }
                break;
            }
            // remove element
            case 'r': {
                scanf("%d", &k);
                getchar();
                output = removeElement(&table, k);

                if (output == NO_SUCH_KEY) {
                    puts("NoSuchKey");
                }
                else {
                    printf("%d\n", output);
                }
                break;
            }
            // print table
            case 'p': {
                printHashTable(&table);
                break;
            }
        }
    }
}

void constructHashTable(HashTable *table, const int size, HashFunction hf)
{
    table->size = size;
    table->bucketArray = (Bucket*)calloc(size, sizeof(Bucket)); // 동적할당 및 0 초기화
    setHashFunc(table, hf); // 해시 함수 등록
}

void setHashFunc(HashTable *table, HashFunction hf)
{
    table->hf = hf;
}

int findElement(const HashTable *table, const int key)
{
    int i = 0;
    int v = table->hf(key, i);

    // M개 셀 검사
    while (i < table->size) {
        const Status status = getStatus(table, v); // 버켓 상태 저장

        if(empty(status)){
            return NO_SUCH_KEY;
        }
        else if (active(status) && (key == getKey(table, v))) {
            return getKey(table, v);
        }
        else {
            i++;
            v = table->hf(key, i);
        }
    }

    return NO_SUCH_KEY;
}

int insertItem(HashTable *table, const int key)
{
    int i = 0;
    int v = table->hf(key, i);

    // 중복 키 검사
    if(findElement(table, key) != NO_SUCH_KEY){
        return DUPLICATED_KEY;
    }

    while (i < table->size) {
        const Status status = getStatus(table, v);
        // printf("key %d i %d v %d\n", key, i, v);
        // printf("array[v] %d status %d\n", getKey(table, v), status);

        if (empty(status) || inactive(status)) {
            table->bucketArray[v].key = key;
            activate(table, v);
            return key;
        }
        // incomplete duplication checking
        /*else if (active(status) && (key == getKey(table, v))) {
            return DUPLICATED_KEY;
        }*/
        else {
            i++;
            v = table->hf(key, i);
        }
    }

    return TABLE_OVERFLOW;
}

int removeElement(HashTable *table, const int key)
{
    int i = 0;
    int v = table->hf(key, i);

    while (i < table->size) {
        const Status status = getStatus(table, v);

        if (empty(status) || inactive(status)) {
            return NO_SUCH_KEY;
        }
        else if (active(status) && (key == getKey(table, v))) {
            deactivate(table, v);
            return key;
        }
        else {
            i++;
            v = table->hf(key, i);
        }
    }

    return NO_SUCH_KEY;
}

void printHashTable(const HashTable *table)
{
    const int size = table->size;

    // 인덱스 출력
    for (int i = 0; i < size; i++) {
        printf("%d ", i);
    }

    putchar('\n');

    // 원소 출력
    for (int i = 0; i < size; i++) {
        const Status status = getStatus(table, i);

        if (active(status)) {
            const int key = getKey(table, i);
            printf("%d ", key);
        }
        else {
            printf(". ");
        }
    }

    putchar('\n');
}

void deactivate(HashTable *table, const int v)
{
    // printf("bucket [%d] is deactivated", v);
    table->bucketArray[v].status = INACTIVE;
}

void activate(HashTable *table, const int v)
{
    // printf("bucket [%d] is activated", v);
    table->bucketArray[v].status = ACTIVE;
}

_Bool inactive(const Status status)
{
    // printf("inactive: %d\n", status == DEACTIVATED);
    return status == INACTIVE;
}

_Bool active(const Status status)
{
    // printf("active: %d\n", status == ACTIVATED);
    return status == ACTIVE;
}

_Bool empty(const Status status)
{
    // printf("empty: %d\n", status == EMPTY);
    return status == EMPTY;
}

int getKey(const HashTable *table, const int v)
{
    return table->bucketArray[v].key;
}

Status getStatus(const HashTable *table, const int v)
{
    return table->bucketArray[v].status;
}

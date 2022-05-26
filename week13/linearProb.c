#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE (10)
#define TABLE_SIZE (13)

struct Element
{
    char key[KEY_SIZE];
};
typedef struct Element Element;

inline int empty(const Element e)
{
    return e.key[0] == '\0';
}

inline int equal(const Element e1, const Element e2)
{
    return !strcmp(e1.key, e2.key);
}

Element hashTable[TABLE_SIZE];

void initTable(Element *hashTable)
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable[i].key[0] = '\0';
    }
}

int transform(const char *key)
{
    int number = 0;
    int size = strlen(key);
    
    for(int i = 0; i < size; i++)
    {
        number += key[i];
    }

    return number;
}

int hashFunction(const char *key)
{
    return transform(key) % TABLE_SIZE;
}

void addHashTable(Element item, Element *hashTable)
{
    int hashValue = hashFunction(item.key);
    int i = hashValue;

    while(!empty(hashTable[i]))
    {
        if(equal(item, hashTable[i]))
        {
            puts("해당하는 키가 이미 존재합니다.");
            exit(EXIT_FAILURE);
        }

        i = (i + 1) % TABLE_SIZE;

        if(i == hashValue)
        {
            puts("테이블이 꽉 차있습니다.");
            return;
        }
    }

    hashTable[i] = item;
}

void hashSearch(Element item, Element *hashTable)
{
    int hashValue = hashFunction(item.key);
    int i = hashValue;

    while(!empty(hashTable[i]))
    {
        if(equal(item, hashTable[i]))
        {
            puts("탐색 완료: 존재합니다.");
            return;
        }

        i = (i + 1) % TABLE_SIZE;

        if(i == hashValue)
        {
            break;
        }
    }

    puts("탐색 완료: 존재하지 않습니다.");
}

void printHashTable(Element *hashTable)
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        printf("[%d]    %s\n", i, hashTable[i].key);
    }
}

int main(void)
{
    Element temp;
    int op;

    while(1)
    {
        printf("연산 입력(0: 추가, 1: 탐색, 2: 종료) = ");
        scanf("%d", &op);

        if(op == 2) break;

        printf("키 입력: ");
        scanf("%s", temp.key);

        if(op == 0)
            addHashTable(temp, hashTable);
        else if(op == 1)
            hashSearch(temp, hashTable);

        printHashTable(hashTable);
    }

    return 0;
}
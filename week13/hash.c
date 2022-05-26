#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE (10)
#define TABLE_SIZE (5)


struct Element
{
    char key[KEY_SIZE];
};
typedef struct Element Element;

struct ListNode
{
    Element item;
    struct ListNode *link;
};
typedef struct ListNode ListNode;

inline int equal(const Element e1, const Element e2)
{
    return !strcmp(e1.key, e2.key);
}

ListNode *hashTable[TABLE_SIZE];

void initTable(ListNode **hashTable)
{
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable[i] = NULL;
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

void addHashTable(Element item, ListNode **hashTable)
{
    int hashValue = hashFunction(item.key);
    ListNode *tempPtr;

    for(ListNode *cursor = hashTable[hashValue]; cursor != NULL; cursor = cursor->link)
    {
        if(equal(item, cursor->item))
        {
            puts("이미 존재하는 값입니다.");
            exit(EXIT_FAILURE);
        }
    }

    tempPtr = (ListNode *)malloc(sizeof(ListNode));
    tempPtr->item = item;
    tempPtr->link = hashTable[hashValue];
    hashTable[hashValue] = tempPtr;
}

void hashSearch(Element item, ListNode **hashTable)
{
    int hashValue = hashFunction(item.key);
    for(ListNode *cursor = hashTable[hashValue]; cursor != NULL; cursor = cursor->link)
    {
        if(equal(item, cursor->item))
        {
            puts("탐색 완료: 존재합니다");
            return; 
        }
    }
    
    puts("탐색 완료: 존재하지 않습니다.");
}

void printHashTable(ListNode **hashTable)
{
    ListNode *temp;

    for(int i = 0; i < TABLE_SIZE; i++)
    {
        temp = hashTable[i];
        
        printf("[%d]:", i);
        while(temp != NULL)
        {
            printf(" %s", temp->item.key);

            temp = temp->link;
        }

        puts("");
    }
}

int main(void)
{
    Element temp;
    int op;

    while(1)
    {
        printf("연산 입력(0: 추가, 1: 탐색, 2:출력, 3: 종료) = ");
        scanf("%d", &op);

        if(op == 3)
            break;
        else if(op == 2)
            printHashTable(hashTable);
        else
        {
            printf("키 입력: ");
            scanf("%s", temp.key);
            if(op == 0)
                addHashTable(temp, hashTable);
            else if(op == 1)
                hashSearch(temp, hashTable);
        }
    }

    return 0;
}
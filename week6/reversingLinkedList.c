#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE (1)
#define FALSE (-1)

typedef int DataType;

struct Node
{
    DataType data;
    struct Node *nextNode;
};
typedef struct Node Node;

struct LinkedList
{
    int curCount;
    Node headNode;
};
typedef struct LinkedList LinkedList;

struct StackNode
{
    DataType data;
    struct StackNode *next;
};
typedef struct StackNode StackNode;

int addNode(LinkedList *pList, int pos, DataType data);
int removeNode(LinkedList *pList, int pos);
void showNode(LinkedList *pList);
int isEmpty(LinkedList *pList);
int findPos(LinkedList *pList, DataType data);
void makeEmpty(LinkedList *pList);

void pushLinkedStack(StackNode **top, int data);
StackNode *popLinkedStack(StackNode **top);
void showLinkedStack(StackNode *top);
StackNode *topLinkedStack(StackNode *top);
void deleteLinkedStack(StackNode **top);
int isEmptyStack(StackNode *top);

void reverseList(LinkedList *pList, StackNode **top);

int main(void)
{
    int pos;
    LinkedList *linkedList = (LinkedList *)malloc(sizeof(LinkedList));
    linkedList->curCount = 0;
    linkedList->headNode.nextNode = NULL;

    StackNode *top = NULL;

    addNode(linkedList, 0, 10);
    addNode(linkedList, 5, 100);
    addNode(linkedList, 1, 20);
    addNode(linkedList, 2, 30);
    addNode(linkedList, 1, 50);
    addNode(linkedList, 1, 70);
    addNode(linkedList, 1, 40);

    showNode(linkedList);

    reverseList(linkedList, &top);

    showNode(linkedList);

    makeEmpty(linkedList);
    showNode(linkedList);

    return 0;
}

void showNode(LinkedList *pList)
{
    int i = 0;
    Node *pNode = NULL;

    if(pList == NULL)
    {
        printf("showNode error\n");
        return;
    }

    printf("현재 Node 개수: %d\n", pList->curCount);

    pNode = pList->headNode.nextNode;

    while(pNode != NULL)
    {
        printf("[%d]\n", pNode->data);
        pNode = pNode->nextNode;
    }
    printf("-------------------\n");
}

int isEmpty(LinkedList *pList)
{
    if(pList == NULL)
    {
        printf("isEmpty() error\n");
        return FALSE;
    }

    if(pList->headNode.nextNode == NULL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int addNode(LinkedList *pList, int pos, DataType data)
{
    Node *pNewNode = NULL;
    Node *pTmpNode = NULL;

    if(pList == NULL)
    {
        printf("addNode() error1\n");
        return FALSE;
    }

    if(pos > pList->curCount)
    {
        printf("addNode() error2: 추가 범위 초과\n");
        return FALSE;
    }

    pNewNode = (Node *)malloc(sizeof(Node));
    if(pNewNode == NULL)
    {
        printf("addNode() error3\n");
        return FALSE;
    }

    pNewNode->data = data;
    pNewNode->nextNode = NULL;

    pTmpNode = &pList->headNode;
    for(int i = 0; i < pos; i++)
    {
        pTmpNode = pTmpNode->nextNode;
    }

    pNewNode->nextNode = pTmpNode->nextNode;
    pTmpNode->nextNode = pNewNode;

    pList->curCount++;
    
    return TRUE;
}

int removeNode(LinkedList *pList, int pos)
{
    Node *pDelNode = NULL;
    Node *pTmpNode = NULL;

    if(pList == NULL)
    {
        printf("removeNode() error1\n");
        return FALSE;
    }

    if(pos >= pList->curCount)
    {
        printf("removeNode() error2: 삭제 범위 초과\n");
        return FALSE;
    }

    pTmpNode = &pList->headNode;
    for(int i = 0; i < pos; i++)
    {
        pTmpNode = pTmpNode->nextNode;
    }

    pDelNode = pTmpNode->nextNode;
    pTmpNode->nextNode = pTmpNode->nextNode->nextNode;

    free(pDelNode);

    pList->curCount--;

    return TRUE;
}

int findPos(LinkedList *pList, DataType data)
{
    int pos = 0;
    Node *pNode = NULL;

    if(pList == NULL)
    {
        printf("findPos() error\n");
        return FALSE;
    }

    pNode = pList->headNode.nextNode;

    while(pNode != NULL)
    {
        if(pNode->data == data)
        {
            return pos;
        }

        pNode = pNode->nextNode;
        pos++;
    }

    return FALSE;
}

void makeEmpty(LinkedList *pList)
{
    Node *pDummyNode = NULL;
    Node *pTmpNode = NULL;

    if(pList != NULL)
    {
        pTmpNode = pList->headNode.nextNode;

        while(pTmpNode != NULL)
        {
            pDummyNode = pTmpNode;
            pTmpNode = pTmpNode->nextNode;
            free(pDummyNode);
        }

        pList->curCount = 0;
        pList->headNode.nextNode = NULL;
    }
}

int isEmptyStack(StackNode *top)
{
    if(top == NULL)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void showLinkedStack(StackNode *top)
{
    StackNode *pNode = NULL;
    if(isEmptyStack(top) == TRUE)
    {
        printf("the Stack is empty\n");
        return;
    }

    pNode = top;
    printf("==========Show Stack==========\n");
    while(pNode != NULL)
    {
        printf("[%d]\n", pNode->data);
        pNode = pNode->next;
    }
    printf("==============================\n");
}

void pushLinkedStack(StackNode **top, DataType data)
{
    StackNode *pNode = NULL;

    pNode = (StackNode *)malloc(sizeof(StackNode));
    pNode->data = data;
    pNode->next = NULL;

    if(isEmptyStack(*top) == TRUE)
    {
        *top = pNode;
    }
    else
    {
        pNode->next = *top;
        *top = pNode;
    }
}

StackNode *popLinkedStack(StackNode **top)
{
    StackNode *pNode = NULL;

    if(isEmptyStack(*top) == TRUE)
    {
        printf("the Stack is empty\n");
        return NULL;
    }

    pNode = *top;
    *top = pNode->next;

    return pNode;
}

StackNode *topLinkedStack(StackNode *top)
{
    StackNode *pNode = NULL;

    if(isEmptyStack(top) == FALSE)
    {
        pNode = top;
    }

    return pNode;
}

void deleteLinkedStack(StackNode **top)
{
    StackNode *pNode = NULL;
    StackNode *pDelNode = NULL;

    pNode = *top;
    
    while(pNode != NULL)
    {
        pDelNode = pNode;
        pNode = pNode->next;
        free(pDelNode);
    }

    *top = NULL;
}

void reverseList(LinkedList *pList, StackNode **top)
{
    Node *pNode = NULL;
    StackNode *sNode = NULL;

    printf("Reverse Linked List!\n");

    pNode = pList->headNode.nextNode;
    while(pNode != NULL)
    {
        pushLinkedStack(top, pNode->data);
        pNode = pNode->nextNode;
    }

    makeEmpty(pList);

    sNode = *top;
    while(sNode != NULL)
    {
        addNode(pList, pList->curCount, sNode->data);
        popLinkedStack(top);
        sNode = *top;
    }
}
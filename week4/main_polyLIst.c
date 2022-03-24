#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFSIZE (1024)

typedef int Coefficient;
typedef int Exponent;

struct Poly;
typedef struct Poly Poly;

struct Node;
typedef struct Node Node;

struct Node
{
    Coefficient coef;
    Exponent exp;

    Node *next;
};

struct Poly
{
    size_t size;

    Node startNode;
};

Poly createEmptyPoly(void)
{
    return (Poly){0, (Node){0, 0, NULL}};
}

void clearPoly(Poly *poly)
{
    Node *cursor = poly->startNode.next;

    while(cursor != NULL)
    {
        Node *temp = cursor->next;
        free(cursor);
        cursor = temp;
    }

    poly->startNode.next = NULL;
    poly->size = 0;
}

void addTerm(Poly *poly, Exponent exp, Coefficient coef)
{
    if(coef == 0)
    {
        return;
    }

    Node *cursor = &poly->startNode;

    while(cursor->next != NULL && cursor->next->exp > exp)
    {
        cursor = cursor->next;
    }

    if(cursor->next != NULL && cursor->next->exp == exp)
    {
        if(cursor->next->coef + coef == 0)
        {
            Node *temp = cursor->next;

            cursor->next = cursor->next->next;
            free(temp);

            poly->size -= 1;
        }
        else
        {
            cursor->next->coef += coef;
        }
    }
    else
    {
        Node *temp = cursor->next;

        cursor->next = (Node *)malloc(sizeof(Node));

        if(cursor->next == NULL)
        {
            exit(EXIT_FAILURE);
        }

        cursor->next->coef = coef;
        cursor->next->exp = exp;
        cursor->next->next = temp;

        poly->size += 1;
    }
}

Poly multiPoly(Poly lhs, Poly rhs)
{
    Poly retPoly = createEmptyPoly();

    const Node *lhsNode = lhs.startNode.next;

    while(lhsNode != NULL)
    {
        const Node *rhsNode = rhs.startNode.next;
        while(rhsNode != NULL)
        {
            addTerm(&retPoly, lhsNode->exp + rhsNode->exp, lhsNode->coef * rhsNode->coef);

            rhsNode = rhsNode->next;
        }

        lhsNode = lhsNode->next;
    }

    return retPoly;
}

void printPoly_impl(Poly A, char* buffer)
{
    buffer[0] = '\0';

    Node *node = A.startNode.next;

    if(node == NULL)
    {
        buffer += sprintf(buffer, "0");

        return;
    }

    if(node->exp == 0 || (node->coef != 1 && node->coef != -1))
    {
        buffer += sprintf(buffer, "%d", node->coef);
    }
    if(node->exp != 0)
    {
        buffer += sprintf(buffer, "x");
        if(node->exp != 1)
        {
            buffer += sprintf(buffer, "^%d", node->exp);
        }
    }

    node = node->next;

    while(node != NULL)
    {
        buffer += sprintf(buffer, (node->coef < 0) ? "-" : "+");

        if(node->exp == 0 || (node->coef != 1 && node->coef != -1))
        {
            buffer += sprintf(buffer, "%d", (node->coef < 0) ? -node->coef : node->coef);
        }

        if(node->exp != 0)
        {
            buffer += sprintf(buffer, "x");
            if(node->exp != 1)
            {
                buffer += sprintf(buffer, "^%d", node->exp);
            }
        }

        node = node->next;
    }
}

void printPoly(Poly A)
{
	char buffer[BUFFSIZE] = "";
	printPoly_impl(A, buffer);
	printf(buffer);
}



int main(void)
{
    Poly A, B;
    A = createEmptyPoly();
    B = createEmptyPoly();
    
    addTerm(&A, 1, 1);
    addTerm(&A, 0, 1);
    printf("poly A: ");
    printPoly(A);
    printf("\n");

    addTerm(&B, 1, 1);
    addTerm(&B, 0, -1);
    printf("poly B: ");
    printPoly(B);
    printf("\n");

    printf("A*B: ");
    printPoly(multiPoly(A, B));
    printf("\n");

    return 0;
}
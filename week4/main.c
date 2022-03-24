#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFSIZE 1024

typedef int Coefficient;
typedef int Exponent;

struct Poly;
typedef struct Poly Poly;
struct Poly_Term;
typedef struct Poly_Term Poly_Term;

struct Poly
{
    size_t size;

    Poly_Term *node;
};

struct Poly_Term
{
    Coefficient coef;
    Exponent exp;

    Poly_Term *next;
};

Poly createEmptyPoly(void)
{
    return (Poly){0, NULL};
}

void clearPoly(Poly* poly)
{
    Poly_Term **term = &poly->node;
    Poly_Term **temp = NULL;

    while(*term != NULL)
    {
        temp = term;
        term = &(*term)->next;
        free(*temp);
        *temp = NULL;
    }

    poly->size = 0;
}

void addTerm(Poly* poly, Exponent exp, Coefficient coef)
{
    Poly_Term **term = &poly->node;

    while(*term != NULL && (*term)->exp > exp)
    {
        term = &(*term)->next;
    }

    if(*term == NULL)
    {
        *term = (Poly_Term *)malloc(sizeof(Poly_Term));

        (*term)->coef = coef;
        (*term)->exp = exp;
        (*term)->next = NULL;

        poly->size++;
    }
    else if((*term)->exp == exp)
    {
        if((*term)->coef + coef == 0)
        {
            Poly_Term *nextNext = (*term)->next;

            free(*term);
            *term = nextNext;

            poly->size--;
        }
        else
        {
            (*term)->coef += coef;
        }
    }
    else
    {
        Poly_Term *temp = (*term)->next;

        *term = (Poly_Term *)malloc(sizeof(Poly_Term));

        (*term)->coef = coef;
        (*term)->exp = exp;
        (*term)->next = temp;

        poly->size++;
    }
}

Poly multiPoly(Poly lhs, Poly rhs)
{
    Poly retPoly = {0, NULL};

    const Poly_Term *lhsTerm = lhs.node;

    while(lhsTerm != NULL)
    {
        const Poly_Term *rhsTerm = rhs.node;
        while(rhsTerm != NULL)
        {
            addTerm(&retPoly, lhsTerm->exp + rhsTerm->exp, lhsTerm->coef * rhsTerm->coef);

            rhsTerm = rhsTerm->next;
        }

        lhsTerm = lhsTerm->next;
    }

    return retPoly;
}

void printPoly_impl(Poly A, char* buffer)
{
    buffer[0] = '\0';

    if(A.node == NULL)
    {
        buffer += sprintf(buffer, "0");

        return;
    }
    else
    {
        if(A.node->exp == 0 || A.node->coef != 1)
        {
            buffer += sprintf(buffer, "%d", A.node->coef);
        }
        if(A.node->exp != 0)
        {
            buffer += sprintf(buffer, "x");
            if(A.node->exp != 1)
            {
                buffer += sprintf(buffer, "^%d", A.node->exp);
            }
        }
    }

    Poly_Term *term = A.node->next;

    while(term != NULL)
    {
        if(term->coef < 0)
        {
            buffer += sprintf(buffer, "-");
            if(term->exp == 0 || (term->coef != 1 && term->coef != -1))
            {
                buffer += sprintf(buffer, "%d", -term->coef);
            }
            if(term->exp != 0)
            {
                buffer += sprintf(buffer, "x");
                if(term->exp != 1)
                {
                    buffer += sprintf(buffer, "^%d", term->exp);
                }
            }
        }
        else
        {
            buffer += sprintf(buffer, "+");
            if(term->exp == 0 || term->coef != 1)
            {
                buffer += sprintf(buffer, "%d", term->coef);
            }
            if(term->exp != 0)
            {
                buffer += sprintf(buffer, "x");
                if(term->exp != 1)
                {
                    buffer += sprintf(buffer, "^%d", term->exp);
                }
            }
        }

        term = term->next;
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
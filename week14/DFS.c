#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES (10)
#define TRUE 1
#define FALSE 0

int visited[MAX_VERTICES];

struct Graph
{
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    size_t n;
};
typedef struct Graph Graph;

void init(Graph *g)
{
    g->n = 0;

    for(int i = 0; i < MAX_VERTICES; i++)
    {
        for(int j = 0; j < MAX_VERTICES; j++)
        {
            g->adjMatrix[i][j] = 0;
        }
    }
}

void insertVertex(Graph *g, int v)
{
    if(g->n == MAX_VERTICES)
    {
        puts("vertex 개수가 너무 많습니다. 노드 삽입 불가\n");
        return;
    }

    g->n += 1;
}

void insertEdge(Graph *g, int u, int v)
{
    if(u >= g->n || v >= g->n)
    {
        puts("정점 번호가 잘못됨. 정점 번호는 0 ~ N-1");
        return;
    }

    g->adjMatrix[u][v] = 1;
    g->adjMatrix[v][u] = 1;
}

void dfs(Graph *g, int v)
{
    visited[v] = TRUE;
    printf("%d", v);

    for(int i = 0; i < g->n; i++)
    {
        if(visited[i] == FALSE && g->adjMatrix[v][i] == 1)
        {
            printf(" -> ");
            dfs(g, i);
        }
    }
}

int main()
{
    Graph g;

    init(&g);

    for(int i = 0; i < MAX_VERTICES; i++)
    {
        visited[i] = FALSE;
    }
    for(int i = 0; i < 7; i++)
    {
        insertVertex(&g, i);
    }

    insertEdge(&g, 0, 4);
    insertEdge(&g, 0, 6);
    insertEdge(&g, 1, 3);
    insertEdge(&g, 3, 5);
    insertEdge(&g, 4, 1);
    insertEdge(&g, 4, 2);
    insertEdge(&g, 6, 2);

    dfs(&g, 0);
}
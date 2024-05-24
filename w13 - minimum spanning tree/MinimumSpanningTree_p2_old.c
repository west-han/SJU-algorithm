#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Vertex   Vertex;
typedef struct Edge     Edge;
typedef struct Node     Node;
typedef struct Graph    Graph;
typedef struct PQ       PQ;
typedef struct DSet     DSet;

struct Vertex
{
    int distance;
    int group;
};

struct Edge
{
    int uName;
    int vName;
    int weight;
};

struct Graph
{
    Vertex* v;
    Edge* e;
};

struct PQ
{
    Edge* e;
    PQ* next;
};

void buildGraph(Graph* graph, const int n, const int m);
void insertEdges(Graph* graph, int uName, int vName, int weight, int idx);
int opposite(Graph* graph, int v, int e);
int kruskalMST(Graph* graph, const int n, const int m, const int sName);

void insertItem(PQ* pq, Edge* e);
Edge* removeMin(PQ* pq);
_Bool isEmpty(PQ* pq);
_Bool compareGroup(Graph* graph, Edge* edge);
void unionGroup(Graph* graph, Edge* e, const int n);

// 6 9 1 2 3 1 3 20 2 4 25 2 5 17 3 4 34 3 5 1 3 6 12 4 5 5 5 6 37
int main()
{
    int n, m;
    Graph graph;
    scanf("%d %d", &n, &m);

    buildGraph(&graph, n, m);

    printf("%d\n", kruskalMST(&graph, n, m, 1));
}


void buildGraph(Graph* graph, const int n, const int m)
{
    graph->v = (Vertex*)calloc((n + 1), sizeof(Vertex));
    graph->e = (Edge*)calloc(m, sizeof(Edge));
    for (int i = 1; i < n + 1; i++)
    {
        graph->v[i].distance = INT32_MAX;
    }

    for (int i = 0; i < m; i++)
    {
        int uName, vName, weight;
        scanf("%d %d %d", &uName, &vName, &weight);
        insertEdges(graph, uName, vName, weight, i);
    }
}

void insertEdges(Graph* graph, int uName, int vName, int weight, int idx)
{
    graph->e[idx].uName = uName;
    graph->e[idx].vName = vName;
    graph->e[idx].weight = weight;
}

int opposite(Graph* graph, int v, int e)
{
    if (graph->e[e].uName == v)
        return graph->e[e].vName;
    else
        return graph->e[e].uName;
}

int kruskalMST(Graph* graph, const int n, const int m, const int sName)
{
    int cost = 0;
    for (int i = 1; i <= n; i++)
    {
        graph->v[i].group = i;
    }

    PQ* pq = (PQ*)malloc(sizeof(PQ));
    pq->next = NULL;

    for (int i = 0; i < m; i++)
    {
        insertItem(pq, &(graph->e[i]));
    }

    while (!isEmpty(pq))
    {
        Edge* e = removeMin(pq);
        if (!compareGroup(graph, e))
        {
            printf(" %d", e->weight);
            cost += e->weight;

            unionGroup(graph, e, n);
        }
    }
    putchar('\n');
    return cost;
}

void insertItem(PQ* pq, Edge* e)
{
    PQ* newNode = (PQ*)malloc(sizeof(PQ));
    PQ* bef = pq;
    while (bef->next && bef->next->e->weight < e->weight)
    {
        bef = bef->next;
    }

    newNode->e = e;
    newNode->next = bef->next;
    bef->next = newNode;
}

Edge* removeMin(PQ* pq)
{
    if (isEmpty(pq))
        return NULL;
    PQ* delNode = pq->next;
    Edge* ret = delNode->e;

    pq->next = delNode->next;

    free(delNode);
    return ret;
}

_Bool isEmpty(PQ* pq)
{
    return pq->next == NULL;
}

_Bool compareGroup(Graph* graph, Edge* edge)
{
    
    return graph->v[edge->uName].group == graph->v[edge->vName].group;
}

void unionGroup(Graph* graph, Edge* e, const int n)
{
    int oldGroup, newGroup;
    if (graph->v[e->uName].group < graph->v[e->vName].group)
    {
        oldGroup = graph->v[e->vName].group;
        newGroup = graph->v[e->uName].group;
    }
    else
    {
        oldGroup = graph->v[e->uName].group;
        newGroup = graph->v[e->vName].group;
    }

    for (int i = 1; i <= n; i++)
    {
        if (graph->v[i].group == oldGroup)
        {
            graph->v[i].group = newGroup;
        }
    }
}
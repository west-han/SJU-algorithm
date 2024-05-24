#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Vertex   Vertex;
typedef struct Edge     Edge;
typedef struct Node     Node;
typedef struct Graph    Graph;
typedef struct PQ       PQ;

typedef enum Status
{
    FRESH = 0, VISITED = 1
} Status;


struct Vertex
{
    int distance;
    Status status;
    Node* incidentEdges;
};

struct Edge
{
    int uName;
    int vName;
    int weight;
};

struct Node
{
    int edge;
    Node* next;
};

struct Graph
{
    Vertex* v;
    Edge* e;
};

struct PQ
{
    Vertex* v;
    PQ* next;
};

void buildGraph(Graph* graph, const int n, const int m);
void insertEdges(Graph* graph, int uName, int vName, int weight, int idx);
int opposite(Graph* graph, int v, int e);
int primMST(Graph* graph, const int n, const int m, int sName);

_Bool isVisited(Graph* graph, int vName);
int removeMin(Graph* graph, int n);
_Bool compareWeight(Graph* graph, int edge, int vName);


int main()
{
    int n, m;
    Graph graph;
    scanf("%d %d", &n, &m);

    buildGraph(&graph, n, m);

    printf("%d\n", primMST(&graph, n, m, 1));
}


void buildGraph(Graph* graph, const int n, const int m)
{
    graph->v = (Vertex*)calloc((n + 1), sizeof(Vertex));
    graph->e = (Edge*)calloc(m, sizeof(Edge));
    for (int i = 1; i < n + 1; i++)
    {
        graph->v[i].distance = INT32_MAX;
        graph->v[i].incidentEdges = (Node*)calloc(1, sizeof(Node));
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

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = graph->v[uName].incidentEdges->next;
    graph->v[uName].incidentEdges->next = newNode;
    newNode->edge = idx;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->next = graph->v[vName].incidentEdges->next;
    graph->v[vName].incidentEdges->next = newNode;
    newNode->edge = idx;

    //printf("new edge: at index %d, from %d to %d with weight %d\n", idx, uName, vName, weight);
}

int opposite(Graph* graph, int v, int e)
{
    if (graph->e[e].uName == v)
        return graph->e[e].vName;
    else
        return graph->e[e].uName;
}

int primMST(Graph* graph, const int n, const int m, int sName)
{
    PQ *pq = (PQ*)calloc(1, sizeof(PQ));
    int cost = 0;

    for (int i = 1; i <= n; i++)
    {
        graph->v[i].distance = INT32_MAX;
        graph->v[i].status = FRESH;
    }

    graph->v[sName].distance = 0;

    for(int i = 1; i <= n; i++)
    {
        int u = removeMin(graph, n);
        cost += graph->v[u].distance;
        printf(" %d", u);

        Node* cur = graph->v[u].incidentEdges->next;
        while (cur)
        {
            int z = opposite(graph, u, cur->edge);
            if (!isVisited(graph, z) &&
                compareWeight(graph, cur->edge, z))
            {
                graph->v[z].distance = graph->e[cur->edge].weight;
            }
            cur = cur->next;
        }
        //printf("\nu: %d, w: %d, cost: %\nd", u, graph->v[u].distance, cost);
    }
    // 5 7 1 2 1 1 4 2 1 5 4 2 5 7 4 5 3 3 5 5 2 3 6
    free(pq);
    putchar('\n');
    return cost;
}

_Bool isVisited(Graph* graph, int vName)
{
    return graph->v[vName].status == VISITED;
}

int removeMin(Graph* graph, int n)
{
    int ret = 0;
    int min = INT32_MAX;
    for (int i = 1; i <= n; i++)
    {
        if (graph->v[i].distance < min && graph->v[i].status != VISITED)
        {
            min = graph->v[i].distance;
            ret = i;
        }
    }

    graph->v[ret].status = VISITED;

    return ret;
}

_Bool compareWeight(Graph* graph, int edge, int vName)
{
    return graph->e[edge].weight < graph->v[vName].distance;
}
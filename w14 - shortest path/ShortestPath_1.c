#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX     1000 * 30

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
    int name;
    int distance;
    int position;
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

// array heap
int g_heapSize = 0;
Vertex** g_heapArr = NULL;

// graph functions
void buildGraph(Graph* graph, const int n, const int m);
void insertEdges(Graph* graph, int uName, int vName, int weight, int idx);
int opposite(Graph* graph, int v, int e);
void DijkstraShortestPath(Graph* graph, int n, int s);

// heap functions
int getParentIdx(int idx);
int getLChildIdx(int idx);
int getRChildIdx(int idx);
void swap(int* n1, int* n2);
int isEmpty();
int isRoot(int idx);
int isExternal(int idx);
int getHighPriorChildIdx(int idx);
void downHeap(Graph* graph, int idx);
void upHeap(Graph* graph, int idx);
void buildHeap(Graph* graph, const int n);
Vertex* removeMin(Graph* graph);

int main()
{
    int n, m, s;
    Graph graph;
    scanf("%d %d %d", &n, &m, &s);

    buildGraph(&graph, n, m);

    DijkstraShortestPath(&graph, n, s);

    for (int i = 1; i <= n; i++)
    {
        if (i != s && graph.v[i].distance != MAX)
        {
            printf("%d %d\n", i, graph.v[i].distance);
        }
    }
}


void buildGraph(Graph* graph, const int n, const int m)
{
    graph->v = (Vertex*)calloc((n + 1), sizeof(Vertex));
    graph->e = (Edge*)calloc(m, sizeof(Edge));
    for (int i = 1; i < n + 1; i++)
    {
        graph->v[i].name = i;
        graph->v[i].distance = MAX;
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
}

int opposite(Graph* graph, int v, int e)
{
    if (graph->e[e].uName == v)
        return graph->e[e].vName;
    else
        return graph->e[e].uName;
}

// heap functionss
int getParentIdx(int idx) {
    return idx / 2;
}

int getLChildIdx(int idx) {
    return idx * 2;
}

int getRChildIdx(int idx) {
    return idx * 2 + 1;
}

void swap(int* n1, int* n2) {
    int tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}

int isEmpty()
{
    return g_heapSize == 0;
}

int isRoot(int idx) {
    return idx == 1;
}

int isExternal(int idx) {
    return getLChildIdx(idx) > g_heapSize;
}

int getHighPriorChildIdx(int idx) {
    int lIdx = getLChildIdx(idx);
    int rIdx = getRChildIdx(idx);
    if (rIdx > g_heapSize)
        return lIdx;

    if (g_heapArr[lIdx]->distance < g_heapArr[rIdx]->distance) { // comparing distance
        return lIdx;
    }
    else {
        return rIdx;
    }
}

void downHeap(Graph* graph, int idx) {
    int childIdx = getHighPriorChildIdx(idx);

    while (!isExternal(idx) && g_heapArr[idx]->distance >= g_heapArr[childIdx]->distance) {
        swap(g_heapArr + idx, g_heapArr + childIdx);

        // change position label of each vertices
        g_heapArr[idx]->position = idx;
        g_heapArr[childIdx]->position = childIdx;

        idx = childIdx;
        childIdx = getHighPriorChildIdx(idx);
    }
}

void upHeap(Graph* graph, int idx)
{
    int parentIdx = getParentIdx(idx);

    while (!isRoot(idx) && g_heapArr[idx]->distance <= g_heapArr[parentIdx]->distance) {
        swap(g_heapArr + idx, g_heapArr + parentIdx);

        // change position label of each vertices
        g_heapArr[idx]->position = idx;
        g_heapArr[parentIdx]->position = parentIdx;

        idx = parentIdx;
        parentIdx = getParentIdx(idx);
    }
}

// bottom-up
void buildHeap(Graph* graph, const int n)
{
    g_heapArr = (Vertex**)malloc(sizeof(Vertex*) * (n + 1));
    g_heapArr[0] = 0;


    for (int i = 1; i <= n; i++)
    {
        g_heapSize++;
        g_heapArr[i] = &(graph->v[i]);
        g_heapArr[i]->position = i;
    }

    for (int i = g_heapSize / 2; i >= 1; i--)
    {
        downHeap(graph, i);
    }

}

Vertex* removeMin(Graph* graph)
{
    Vertex* retVertex = g_heapArr[1];

    g_heapArr[1] = g_heapArr[g_heapSize--];
    downHeap(graph, 1);

    return retVertex;
}

void DijkstraShortestPath(Graph* graph, int n, int s) {
    for (int i = 1; i <= n; i++)
    {
        graph->v[i].distance = MAX;
        graph->v[i].status = FRESH;
    }
    graph->v[s].distance = 0;

    buildHeap(graph, n);

    while (!isEmpty())
    {
        Vertex* u = removeMin(graph);

        // if vertex u is not connected
        if(u->distance == MAX)
            continue;

        u->status = VISITED;

        Node* cur = u->incidentEdges->next;
        
        while (cur)
        {
            Vertex* z = &(graph->v[opposite(graph, u->name, cur->edge)]);
            if (z->status == FRESH) // if vertex z is in priority queue
            {
                if (u->distance + graph->e[cur->edge].weight < z->distance)
                {
                    z->distance = u->distance + graph->e[cur->edge].weight;
                    upHeap(graph, z->position);
                }
            }
            cur = cur->next;
        }
    }

    free(g_heapArr);
    g_heapArr = NULL;
}
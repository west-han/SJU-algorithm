#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Vertex   Vertex;
typedef struct Edge     Edge;
typedef struct Node     Node;
typedef struct Graph    Graph;
typedef struct PQ       PQ;

typedef enum VName {
    A = 1, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
};

typedef enum Status
{
    FRESH = 0, VISITED = 1
} Status;


struct Vertex
{
    int name;
    int distance;
    int position;
    int count;
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

int g_heapSize = 0;
Vertex** g_heapArr = NULL;

void buildGraph(Graph* graph, const int n, const int m);
void insertEdges(Graph* graph, int uName, int vName, int weight, int idx);
int opposite(Graph* graph, int v, int e);

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

void DijkstraShortestPath(Graph* graph, int n, int s, int t);

#define N       6   // 정점 개수
#define M       9   // 간선 개수
#define COUNT   4   // 실행 횟수

int main()
{
    Graph graph;

    buildGraph(&graph, N, M);     // 샘플 그래프 생성

    for (int i = 0; i < COUNT; i++)
    {
        int s = 0, t = 0;
        scanf("%c, %c", &s, &t);  // 정점 이름(알파벳 대문자) 입력
        getchar();

        s -= ('A' - 1);
        t -= ('A' - 1);

        DijkstraShortestPath(&graph, N, s, t);
        printf("최단거리: %d, 최단경로 수: %d\n", graph.v[t].distance, graph.v[t].count);
    }

    //DijkstraShortestPath(&graph, N, C, A);
    //printf("최단거리: %d, 최단경로 수: %d\n", graph.v[A].distance, graph.v[A].count);

    //DijkstraShortestPath(&graph, N, C, F);
    //printf("최단거리: %d, 최단경로 수: %d\n", graph.v[F].distance, graph.v[F].count);

    //DijkstraShortestPath(&graph, N, F, C);
    //printf("최단거리: %d, 최단경로 수: %d\n", graph.v[C].distance, graph.v[C].count);

    //DijkstraShortestPath(&graph, N, B, D);
    //printf("최단거리: %d, 최단경로 수: %d\n", graph.v[D].distance, graph.v[D].count);
}


void buildGraph(Graph* graph, const int n, const int m)
{
    graph->v = (Vertex*)calloc((n + 1), sizeof(Vertex));
    graph->e = (Edge*)calloc(m, sizeof(Edge));
    for (int i = 1; i < n + 1; i++)
    {
        graph->v[i].name = i;
        graph->v[i].distance = INT32_MAX;
        graph->v[i].incidentEdges = (Node*)calloc(1, sizeof(Node));
    }

    int edges[9][3] = { {A, B, 8}, {A, C, 1}, {A, D, 4}, {B, C, 7}, {B, E, 4}, {C, D, 5}, {C, E, 3}, {C, F, 9}, {D, F, 4} };
    for (int i = 0; i < m; i++)
    {
        insertEdges(graph, edges[i][0], edges[i][1], edges[i][2], i);
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

    if (g_heapArr[lIdx]->distance < g_heapArr[rIdx]->distance) { // 거리 비교
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

        // position 변수에 우선순위큐에서 정점의 위치 저장
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

        // position 변수에 우선순위큐에서 정점의 위치 저장
        g_heapArr[idx]->position = idx;
        g_heapArr[parentIdx]->position = parentIdx;
        
        idx = parentIdx;
        parentIdx = getParentIdx(idx);
    }
}

void buildHeap(Graph* graph, const int n) // 상향식 힙 생성
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

Vertex* removeMin(Graph* graph) // 힙에서 최솟값 제거
{
    Vertex* retVertex = g_heapArr[1];

    g_heapArr[1] = g_heapArr[g_heapSize--];
    downHeap(graph, 1); // 힙 재구조화

    return retVertex;
}

void DijkstraShortestPath(Graph* graph, int n, int s, int t) {
    for (int i = 1; i <= n; i++)
    {
        graph->v[i].distance = INT32_MAX;
        graph->v[i].status = FRESH;
        graph->v[i].count = 0;
    }
    graph->v[s].distance = 0;
    graph->v[s].count = 1;

    buildHeap(graph, n);

    while (!isEmpty())
    {
        Vertex* u = removeMin(graph);

        if (u->distance == INT32_MAX) // 연결되지 않은 정점 스킵
            continue;
        u->status = VISITED;

        Node* cur = u->incidentEdges->next;

        while (cur)
        {
            Vertex* z = &(graph->v[opposite(graph, u->name, cur->edge)]);
            if (z->status == FRESH)
            {
                if (u->distance + graph->e[cur->edge].weight < z->distance)
                {
                    z->distance = u->distance + graph->e[cur->edge].weight;
                    // 간선 완화가 이뤄지며 최단거리가 바뀌고, 정점 z로 가는 최단경로의 수가 정점 u로 가는 최단경로의 수와 같아짐
                    z->count = u->count;
                    upHeap(graph, z->position); // replaceKey()
                }
                else if (u->distance + graph->e[cur->edge].weight == z->distance)
                {
                    z->count += u->count; // u를 거치지 않고 z로 가는 기존의 최단경로 수에 u를 거쳐서 z로 가는 최단경로의 수가 더해짐
                }
            }
            cur = cur->next;
        }
    }

    free(g_heapArr);
    g_heapArr = NULL;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Vertex   Vertex;
typedef struct Edge     Edge;
typedef struct Node     Node;
typedef struct Graph    Graph;
typedef struct PQ       PQ;

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

int main()
{
    int n, m;
    Graph graph;
    scanf("%d %d", &n, &m);

    buildGraph(&graph, n, m);

    printf("%d\n", kruskalMST(&graph, n, m, 1));
}

// 그래프 생성(간선 리스트 구조)
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

// 간선 추가
void insertEdges(Graph* graph, int uName, int vName, int weight, int idx)
{
    graph->e[idx].uName = uName;
    graph->e[idx].vName = vName;
    graph->e[idx].weight = weight;
}

// 간선 e에 연결된 정점 v의 반대편 끝점 반환
int opposite(Graph* graph, int v, int e)
{
    if (graph->e[e].uName == v)
        return graph->e[e].vName;
    else
        return graph->e[e].uName;
}

// 크루스칼 알고리즘
int kruskalMST(Graph* graph, const int n, const int m, const int sName)
{
    int cost = 0;
    for (int i = 1; i <= n; i++)
    {
        graph->v[i].group = i;
    }

    // 우선순위 큐 생성
    PQ* pq = (PQ*)malloc(sizeof(PQ));
    pq->next = NULL;

    // 우선순위 큐에 모든 간선 추가
    for (int i = 0; i < m; i++)
    {
        insertItem(pq, &(graph->e[i]));
    }

    while (!isEmpty(pq))
    {
        // 최소 비용 간선 반환
        Edge* e = removeMin(pq);
        
        if (!compareGroup(graph, e)) // 간선의 양끝점이 서로 다른 그룹에 속해 있다면
        {
            // 간선의 비중 출력, 비용 갱신
            printf(" %d", e->weight);
            cost += e->weight;

            // 같은 그룹으로 통합
            unionGroup(graph, e, n);
        }
    }
    putchar('\n');

    free(pq);
    return cost;
}

// 간선의 가중치를 비교해 오름차순으로 맞는 위치를 찾아 삽입
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

// 최소 비용의 간선 제거 및 반환
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

// 간선의 양 끝점의 그룹 비교
_Bool compareGroup(Graph* graph, Edge* edge)
{

    return graph->v[edge->uName].group == graph->v[edge->vName].group;
}

// 간선의 양 끝점을 같은 그룹으로 통합
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
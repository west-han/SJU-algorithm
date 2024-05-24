#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX     30 * 1000

typedef struct Vertex   Vertex;
typedef struct Edge     Edge;
typedef struct Node     Node;
typedef struct Graph    Graph;

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

void buildGraph(Graph* graph, const int n, const int m);
void insertEdges(Graph* graph, int uName, int vName, int weight, int idx);
int opposite(Graph* graph, int v, int e);

int getMin(int a, int b);
void BellmanFordShortestPaths(Graph* graph, int n, int m, int s);

int main()
{
    int n, m, s;
    Graph graph;
    scanf("%d %d %d", &n, &m, &s);

    buildGraph(&graph, n, m);

    BellmanFordShortestPaths(&graph, n, m, s);

    for (int i = 1; i <= n; i++)
    {
        if (i != s && graph.v[i].distance != MAX)
        {
            printf("%d %d\n", i, graph.v[i].distance);
        }
    }
}

// 그래프 생성(간선 리스트 구조)
void buildGraph(Graph* graph, const int n, const int m)
{
    graph->v = (Vertex*)calloc((n + 1), sizeof(Vertex));
    graph->e = (Edge*)calloc(m, sizeof(Edge));
    for (int i = 1; i < n + 1; i++)
    {
        graph->v[i].distance = MAX;
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

int getMin(int a, int b)
{
    return a < b ? a : b;
}

void BellmanFordShortestPaths(Graph* graph, int n, int m, int s)
{
    for (int i = 1; i <= n; i++)
    {
        graph->v[i].distance = MAX;
    }

    graph->v[s].distance = 0;
    for (int i = 1; i < n; i++) // n-1번 반복
    {
        for (int e = 0; e < m; e++) // 모든 간선 탐색
        {
            int u = graph->e[e].uName;
            int z = graph->e[e].vName;
            if (graph->v[u].distance == MAX) // 라운드 i에 거리가 갱신되지 않는 간선 건너뛰기
                continue;
            graph->v[z].distance = getMin(graph->v[z].distance, graph->v[u].distance + graph->e[e].weight);
        }
    }
}
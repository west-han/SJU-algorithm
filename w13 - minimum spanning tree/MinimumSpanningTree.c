#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Vertex   Vertex;
typedef struct Edge     Edge;
typedef struct Node     Node;
typedef struct Graph    Graph;

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
    // 정점 및 간선 배열 동적할당
    graph->v = (Vertex*)calloc((n + 1), sizeof(Vertex));
    graph->e = (Edge*)calloc(m, sizeof(Edge));
    
    for (int i = 1; i < n + 1; i++)
    {
        graph->v[i].distance = INT32_MAX;
        // 부착 간선 리스트 더미 헤드 동적할당 및 초기화
        graph->v[i].incidentEdges = (Node*)calloc(1, sizeof(Node));
    }

    for (int i = 0; i < m; i++)
    {
        // 간선 정보 입력 및 그래프에 추가
        int uName, vName, weight;
        scanf("%d %d %d", &uName, &vName, &weight);
        insertEdges(graph, uName, vName, weight, i);
    }
}

void insertEdges(Graph* graph, int uName, int vName, int weight, int idx)
{
    // 간선 리스트에 추가
    graph->e[idx].uName = uName;
    graph->e[idx].vName = vName;
    graph->e[idx].weight = weight;

    // 정점의 부착 간선 갱신
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = graph->v[uName].incidentEdges->next;
    graph->v[uName].incidentEdges->next = newNode;
    newNode->edge = idx;
    // 정점의 부착 간선 갱신
    newNode = (Node*)malloc(sizeof(Node));
    newNode->next = graph->v[vName].incidentEdges->next;
    graph->v[vName].incidentEdges->next = newNode;
    newNode->edge = idx;
}

// 정점의 반대 끝점 반환
int opposite(Graph* graph, int v, int e)
{
    if (graph->e[e].uName == v)
        return graph->e[e].vName;
    else
        return graph->e[e].uName;
}


int primMST(Graph* graph, const int n, const int m, int sName)
{
    int cost = 0;

    // 거리 정보 및 라벨 초기화
    for (int i = 1; i <= n; i++)
    {
        graph->v[i].distance = INT32_MAX;
        graph->v[i].status = FRESH;
    }

    // 시작 정점의 거리 정보 0으로 설정
    graph->v[sName].distance = 0;

    for(int i = 1; i <= n; i++)
    {
        // 최소 거리 정점 저장
        int u = removeMin(graph, n);
        cost += graph->v[u].distance;
        printf(" %d", u);

        // 부착 간선 순회
        Node* cur = graph->v[u].incidentEdges->next;
        while (cur)
        {
            int z = opposite(graph, u, cur->edge);
            // 이미 방문한 정점인지 확인, 간선의 가중치 비교
            if (!isVisited(graph, z) &&
                compareWeight(graph, cur->edge, z))
            {
                // 거리 갱신
                graph->v[z].distance = graph->e[cur->edge].weight;
            }
            cur = cur->next;
        }
    }
    putchar('\n');
    return cost;
}

_Bool isVisited(Graph* graph, int vName)
{
    return graph->v[vName].status == VISITED;
}

// 미방문한 정점 중 최소 거리를 가진 정점을 찾아 라벨을 VISITED로 변경 후 반환
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
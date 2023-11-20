#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
// undirected weighted graph

typedef enum Label Label;       // 라벨
typedef struct Vertex Vertex;   // 정점 구조체
typedef struct Edge Edge;       // 간선 구조체
typedef struct Graph Graph;     // 그래프 구조체

// 그래프 생성
Graph* constructGraph(const int n, const int m);
// 정점 추가
Vertex* addVertex(Graph* graph, int vName);
// 간선 추가
void addEdge(Graph* graph, const int v1, const int v2, const int weight);
// 정점 검색
Vertex* findVertex(Graph* graph, const int vName);
// 부착 리스트에 간선에 대한 포인터 추가
void addNode(Graph * graph, Edge* edge, const int v1, const int v2);
// 정점 vName의 인접 정점 출력, 정점 vName의 존재 여부 반환
_Bool printAdjacentVertices(Graph* graph, const int vName);
// 정점 v1과 v2의 존재 여부 반환, 간선의 가중치 변경, 간선이 없는 경우 간선 생성
_Bool modifyWeight(Graph* graph, const int v1, const int v2, const int newWeight);
// 간선 제거
void removeEdge(Graph* graph, const int v1, const int v2);

// 라벨 초기화
void initLabels(Graph* graph);

// Breadth-First-Search
void BFS(Graph* graph, const int s);
void BFS1(Graph* graph, Vertex* v);

// 반대쪽 끝점 반환
Vertex* opposite(Graph* graph, const Vertex* v, const Edge* e);

//5 7 1 1 2 1 4 5 1 3 5 4 3 3 1 2 3
//8 12 7 1 2 2 4 4 7 3 6 6 1 7 6 7 8 1 3 2 7 1 4 2 5 7 5

int main() {
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    Graph* graph = constructGraph(n, m);

    BFS(graph, s);

    /*char c;
        const int n = 6;
        Graph* graph = constructGraph(n);
    
        while ((c = getchar()) != 'q') {
            int v1, v2, w;
            if (c == 'a') {
                scanf("%d", &v1);
                if (printAdjacentVertices(graph, v1) == 0) {
                    printf("%d", -1);
                };
                putchar('\n');
            }
            else if (c == 'm') {
                scanf("%d %d %d", &v1, &v2, &w);
                if (modifyWeight(graph, v1, v2, w) == 0) {
                    printf("%d\n", -1);
                }
            }
            getchar();
        }*/
}

enum Label
{
    FRESH, VISITED, TREE, BACK, CROSS
};

struct Vertex {
    Vertex* next;
    struct Node* list;
    int vName;
    int degree;
    Label label;
};

struct Edge {
    Edge* next;
    Vertex *v1, *v2;
    int weight;
    Label label;
};

struct Graph {
    Vertex* vList;
    Edge* eList;
    Vertex* tail;
    int vSize;
    int eSize;
    Edge** adjacencyMatrix;
};

Graph* constructGraph(const int n, const int m) {
    Graph* graph = (Graph*)calloc(1, sizeof(Graph));
    graph->eList = (Edge*)calloc(1, sizeof(Edge));          // dummy head (edges list)
    graph->vList = (Vertex*)calloc(1, sizeof(Vertex));      // dummy head (vetices list)
    graph->adjacencyMatrix = (Edge**)calloc((n*n), sizeof(Edge*));
    graph->tail = graph->vList;

    for (int i = 0; i < n; i++)
    {
        addVertex(graph, (i + 1));
    }

    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v, 0);
    }

    return graph;
}

Vertex* addVertex(Graph* graph, int vName)
{
    // 정점 동적할당 및 초기화
    Vertex* newV = (Vertex*)calloc(1, sizeof(Vertex));
    newV->vName = vName;
    newV->next = graph->tail->next;

    // 그래프의 정점 리스트에 새로운 정점 추가
    graph->tail->next = newV;
    graph->tail = newV;
    graph->vSize++;
    return newV;
}

void addEdge(Graph* graph, const int v1Name, const int v2Name, const int weight)
{
    // 간선 동적할당 및 초기화
    Edge* newEdge = (Edge*)calloc(1, sizeof(Edge));
    newEdge->next = graph->eList->next;
    newEdge->v1 = findVertex(graph, v1Name);
    newEdge->v2 = findVertex(graph, v2Name);
    newEdge->weight = weight;
    // 그래프의 간선 리스트에 새로운 간선 추가
    graph->eList->next = newEdge;
    graph->eSize++;

    addNode(graph, newEdge, v1Name, v2Name);
}

Vertex* findVertex(Graph* graph, const int vName)
{
    Vertex* target = graph->vList->next;
    while (target != NULL) {
        if (target->vName == vName)
            break;
        target = target->next;
    }

    return target; // 탐색 실패 시 NULL 반환
}

void addNode(Graph * graph, Edge* edge, const int v1, const int v2)
{
    Edge** matrix = graph->adjacencyMatrix;
    const int n = graph->vSize;
    const int row = v1 - 1;
    const int col = v2 - 1;

    *(matrix + col + (row * n)) = edge; // A[row][col] 갱신
    *(matrix + row + (col * n)) = edge; // A[col][row] 갱신
}

_Bool printAdjacentVertices(Graph* graph, const int vName)
{
    Vertex* targetVertex = findVertex(graph, vName);
    // vName이 존재하지 않는 경우
    if (targetVertex == NULL) {
        return 0;
    }
    Edge** matrix = graph->adjacencyMatrix;
    Edge* edge;
    const int n = graph->vSize;
    const int row = vName - 1;
    for (int col = 0; col < graph->vSize; col++) {
        if ((edge = *(matrix + col + (row * n))) != NULL) {
            if (edge->v1->vName == vName)
                printf(" %d", edge->v2->vName);
            else
                printf(" %d", edge->v1->vName);
            printf(" %d", edge->weight);
        }
    }
    return 1;
}

_Bool modifyWeight(Graph* graph, const int v1, const int v2, const int newWeight)
{
    Vertex* vertex1, * vertex2;
    // 각 정점 탐색, 둘 중 하나가 없으면 false 반환
    if ((vertex1 = findVertex(graph, v1)) == NULL ||
        (vertex2 = findVertex(graph, v2)) == NULL)
        return 0;

    // 입력한 가중치가 0이면 간선 제거
    else if (newWeight == 0) {
        removeEdge(graph, v1, v2);
        return 1;
    }
    const int n = graph->vSize;
    const int row = v1 - 1;
    const int col = v2 - 1;
    Edge** matrix = graph->adjacencyMatrix;
    Edge* target = *(matrix + col + (row * n));
    if (target != NULL) {
        target->weight = newWeight;
    }
    else {
        addEdge(graph, v1, v2, newWeight);
    }

    return 1;
}

void removeEdge(Graph* graph, const int v1, const int v2)
{
    Edge* beforeEdge = graph->eList;
    Edge* targetEdge;
    const int row = v1 - 1;
    const int col = v2 - 1;
    const int n = graph->vSize;

    // 인접 행렬 갱신
    Edge** matrix = graph->adjacencyMatrix;
    targetEdge = *(matrix + col + (row * n));
    *(matrix + col + (row * n)) = NULL;
    *(matrix + row + (col * n)) = NULL;

    // 간선 제거 및 간선 리스트 갱신
    while (beforeEdge->next != targetEdge)
        beforeEdge = beforeEdge->next;
    beforeEdge->next = targetEdge->next;
    free(targetEdge);
}

void initLabels(Graph* graph)
{
    Vertex* cV = graph->vList;
    Edge* cE = graph->eList;

    for (int i = 0; i < graph->vSize; i++)
    {
        cV = cV->next;
        cV->label = FRESH;
    }

    for (int i = 0; i < graph->eSize; i++)
    {
        cE = cE->next;
        cE->label = FRESH;
    }
}

void BFS(Graph* graph, const int s)
{
    Vertex* cV = findVertex(graph, s);
    initLabels(graph);

    for (int i = 0; i < graph->vSize; i++)
    {
        if (cV->label == FRESH)
        {
            BFS1(graph, cV);
        }

        cV = (cV->next) ? (cV->next) : (graph->vList->next);
    }
}

void BFS1(Graph* graph, Vertex* v)
{
    const int n = graph->vSize;
    Vertex *queue[100];
    Vertex *W;
    int h = 0, t = 0;
    int row = v->vName;
    v->label = VISITED;
    printf("%d\n", v->vName);

    Edge** matrix = graph->adjacencyMatrix;
    queue[h++] = v;
    while (h > t)
    {
        //printf("iteration %d, checking edges of vertex %d\n", (t+1), queue[t]->vName);
        v = queue[t];
        row = v->vName - 1;

        for (int col = 0; col < n; col++)
        {
            Edge* cE = *(matrix + col + (n * row));
            if (cE != NULL && cE->label == FRESH)
            {
                //printf("(%d, %d), ", cE->v1->vName, cE->v2->vName);
                W = opposite(graph, v, cE);
                if (W->label == FRESH)
                {
                    //printf("vertex %d is FRESH\n", W->vName);
                    queue[h++] = W;
                    W->label = VISITED;
                    printf("%d\n", W->vName);
                    cE->label = TREE;
                }
                else
                {
                    //printf("vertex %d is VISITED\n", W->vName);
                    cE->label = CROSS;
                }
            }
        }

        queue[t++] = NULL;
    }
}


Vertex* opposite(Graph* graph, const Vertex* v, const Edge* e)
{
    if (v->vName == e->v1->vName)
        return e->v2;
    else
        return e->v1;
}

// 6 9 1 3 5 1 3 4 1 2 3 3 4 6 4 3 6 1 2 2 5
// 8 12 4 1 2 2 4 4 7 3 6 6 1 7 6 7 8 1 3 2 7 1 4 2 5 7 5
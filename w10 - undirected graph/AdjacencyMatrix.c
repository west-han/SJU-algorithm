//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <stdlib.h>
//// undirected weighted graph
//
//typedef struct Vertex Vertex;   // 정점 구조체
//typedef struct Edge Edge;       // 간선 구조체
//typedef struct Graph Graph;     // 그래프 구조체
//
//// 그래프 생성
//Graph* constructGraph(const int n);
//// 정점 추가
//Vertex* addVertex(Graph* graph, int vName);
//// 간선 추가
//void addEdge(Graph* graph, const int v1, const int v2, const int weight);
//// 정점 검색
//Vertex* findVertex(Graph* graph, const int vName);
//// 부착 리스트에 간선에 대한 포인터 추가
//void addNode(Graph * graph, Edge* edge, const int v1, const int v2);
//// 정점 vName의 인접 정점 출력, 정점 vName의 존재 여부 반환
//_Bool printAdjacentVertices(Graph* graph, const int vName);
//// 정점 v1과 v2의 존재 여부 반환, 간선의 가중치 변경, 간선이 없는 경우 간선 생성
//_Bool modifyWeight(Graph* graph, const int v1, const int v2, const int newWeight);
//// 간선 제거
//void removeEdge(Graph* graph, const int v1, const int v2);
//
//int main() {
//    char c;
//    const int n = 6;
//    Graph* graph = constructGraph(n);
//
//    while ((c = getchar()) != 'q') {
//        int v1, v2, w;
//        if (c == 'a') {
//            scanf("%d", &v1);
//            if (printAdjacentVertices(graph, v1) == 0) {
//                printf("%d", -1);
//            };
//            putchar('\n');
//        }
//        else if (c == 'm') {
//            scanf("%d %d %d", &v1, &v2, &w);
//            if (modifyWeight(graph, v1, v2, w) == 0) {
//                printf("%d\n", -1);
//            }
//        }
//        getchar();
//    }
//}
//
//struct Vertex {
//    Vertex* next;
//    struct Node* list;
//    int vName;
//    int degree;
//};
//
//struct Edge {
//    Edge* next;
//    int v1Name, v2Name;
//    int weight;
//};
//
//struct Graph {
//    Vertex* vList;
//    Edge* eList;
//    int vSize;
//    int eSize;
//    Edge** adjacencyMatrix;
//};
//
//Graph* constructGraph(const int n) {
//    Graph* graph = (Graph*)calloc(1, sizeof(Graph));
//    graph->eList = (Edge*)calloc(1, sizeof(Edge));          // dummy head (edges list)
//    graph->vList = (Vertex*)calloc(1, sizeof(Vertex));      // dummy head (vetices list)
//    graph->adjacencyMatrix = (Edge**)calloc((n*n), sizeof(Edge*));
//    for (int i = 0; i < n; i++) {
//        addVertex(graph, (6 - i));
//    }
//
//    addEdge(graph, 1, 2, 1);
//    addEdge(graph, 1, 3, 1);
//    addEdge(graph, 1, 4, 1);
//    addEdge(graph, 1, 6, 2);
//    addEdge(graph, 2, 3, 1);
//    addEdge(graph, 3, 5, 4);
//    addEdge(graph, 5, 5, 4);
//    addEdge(graph, 5, 6, 3);
//
//    return graph;
//}
//
//Vertex* addVertex(Graph* graph, int vName)
//{
//    // 정점 동적할당 및 초기화
//    Vertex* newV = (Vertex*)calloc(1, sizeof(Vertex));
//    newV->vName = vName;
//    newV->next = graph->vList->next;
//
//    // 그래프의 정점 리스트에 새로운 정점 추가
//    graph->vList->next = newV;
//    graph->vSize++;
//    return newV;
//}
//
//void addEdge(Graph* graph, const int v1, const int v2, const int weight)
//{
//    // 간선 동적할당 및 초기화
//    Edge* newEdge = (Edge*)calloc(1, sizeof(Edge));
//    newEdge->next = graph->eList->next;
//    newEdge->v1Name = v1;
//    newEdge->v2Name = v2;
//    newEdge->weight = weight;
//    // 그래프의 간선 리스트에 새로운 간선 추가
//    graph->eList->next = newEdge;
//    graph->eSize++;
//
//    addNode(graph, newEdge, v1, v2);
//}
//
//Vertex* findVertex(Graph* graph, const int vName)
//{
//    Vertex* target = graph->vList->next;
//    while (target != NULL) {
//        if (target->vName == vName)
//            break;
//        target = target->next;
//    }
//
//    return target; // 탐색 실패 시 NULL 반환
//}
//
//void addNode(Graph * graph, Edge* edge, const int v1, const int v2)
//{
//    Edge** matrix = graph->adjacencyMatrix;
//    const int n = graph->vSize;
//    const int row = v1 - 1;
//    const int col = v2 - 1;
//
//    *(matrix + col + (row * n)) = edge; // A[row][col] 갱신
//    *(matrix + row + (col * n)) = edge; // A[col][row] 갱신
//}
//
//_Bool printAdjacentVertices(Graph* graph, const int vName)
//{
//    Vertex* targetVertex = findVertex(graph, vName);
//    // vName이 존재하지 않는 경우
//    if (targetVertex == NULL) {
//        return 0;
//    }
//    Edge** matrix = graph->adjacencyMatrix;
//    Edge* edge;
//    const int n = graph->vSize;
//    const int row = vName - 1;
//    for (int col = 0; col < graph->vSize; col++) {
//        if ((edge = *(matrix + col + (row * n))) != NULL) {
//            if (edge->v1Name == vName)
//                printf(" %d", edge->v2Name);
//            else
//                printf(" %d", edge->v1Name);
//            printf(" %d", edge->weight);
//        }
//    }
//    return 1;
//}
//
//_Bool modifyWeight(Graph* graph, const int v1, const int v2, const int newWeight)
//{
//    Vertex* vertex1, * vertex2;
//    // 각 정점 탐색, 둘 중 하나가 없으면 false 반환
//    if ((vertex1 = findVertex(graph, v1)) == NULL ||
//        (vertex2 = findVertex(graph, v2)) == NULL)
//        return 0;
//
//    // 입력한 가중치가 0이면 간선 제거
//    else if (newWeight == 0) {
//        removeEdge(graph, v1, v2);
//        return 1;
//    }
//    const int n = graph->vSize;
//    const int row = v1 - 1;
//    const int col = v2 - 1;
//    Edge** matrix = graph->adjacencyMatrix;
//    Edge* target = *(matrix + col + (row * n));
//    if (target != NULL) {
//        target->weight = newWeight;
//    }
//    else {
//        addEdge(graph, v1, v2, newWeight);
//    }
//
//    return 1;
//}
//
//void removeEdge(Graph* graph, const int v1, const int v2)
//{
//    Edge* beforeEdge = graph->eList;
//    Edge* targetEdge;
//    const int row = v1 - 1;
//    const int col = v2 - 1;
//    const int n = graph->vSize;
//
//    // 인접 행렬 갱신
//    Edge** matrix = graph->adjacencyMatrix;
//    targetEdge = *(matrix + col + (row * n));
//    *(matrix + col + (row * n)) = NULL;
//    *(matrix + row + (col * n)) = NULL;
//
//    // 간선 제거 및 간선 리스트 갱신
//    while (beforeEdge->next != targetEdge)
//        beforeEdge = beforeEdge->next;
//    beforeEdge->next = targetEdge->next;
//    free(targetEdge);
//}
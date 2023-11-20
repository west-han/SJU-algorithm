//#pragma warning(disable: 4819)
//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <stdlib.h>
//// undirected weighted graph
//
//typedef enum Label Label;       // 라벨
//typedef struct Vertex Vertex;   // 정점 구조체
//typedef struct Edge Edge;       // 간선 구조체
//typedef struct Graph Graph;     // 그래프 구조체
//typedef struct Node Node;       // 부착 리스트 노드 구조체
//
//// 그래프 생성
//Graph* constructGraph(const int n, const int m);
//// 정점 추가
//Vertex* addVertex(Graph* graph, int vName);
//// 간선 추가
//void addEdge(Graph* graph, const int v1, const int v2, const int weight);
//// 정점 검색
//Vertex* findVertex(Graph* graph, const int vName);
//// 부착 리스트에 간선에 대한 포인터 추가
//Node* addNode(Vertex* vertex, Edge* edge);
//// 정점 vName의 인접 정점 출력, 정점 vName의 존재 여부 반환
//_Bool printAdjacentVertices(Graph* graph, const int vName);
//// 정점 v1과 v2의 존재 여부 반환, 간선의 가중치 변경, 간선이 없는 경우 간선 생성
//_Bool modifyWeight(Graph* graph, const int v1, const int v2, const int newWeight);
//// 간선 제거
//void removeEdge(Graph* graph, Vertex* v1, Vertex* v2);
//// 노드가 가리키는 간선의 양 끝점과 두 정점을 비교해 일치 여부 반환
//_Bool checkEdge(Node* node, const int v1, const int v2);
//// 부착 리스트 오름차순 정렬을 위한 비교 수행
//_Bool compPrior(int vertexName, Edge* newEdge, Edge* existingEdge);
//
//// Depth-First-Search
//void DFS(Graph* graph, const int s);
//void rDFS(Graph* graph, Vertex* v);
//// 정점, 간선 라벨 초기화
//void initLabel(Graph* graph);
//// 간선의 반대 끝점 반환
//Vertex* opposite(Graph* graph, const Vertex* v, const Edge* e);
//
//int main() {
//    int n, m, s;
//    scanf("%d %d %d", &n, &m, &s);
//    Graph* graph = constructGraph(n, m);
//
//    DFS(graph, s);
//}
//
///*
//5 7 1 1 2 1 4 5 1 3 5 4 3 3 1 2 3
//8 12 7 1 2 2 4 4 7 3 6 6 1 7 6 7 8 1 3 2 7 1 4 2 5 7 5
//*/
//
//enum Label
//{
//    FRESH, VISITED, TREE, BACK, CROSS
//};
//
//struct Vertex {
//    Vertex* next;
//    struct Node* list;
//    int vName;
//    int degree;
//    Label label;
//};
//
//struct Edge {
//    Edge* next;
//    Vertex* v1, * v2;
//    int weight;
//    Label label;
//};
//
//struct Node {
//    Edge* edge;
//    struct Node* next;
//};
//
//struct Graph {
//    Vertex* vList;
//    Vertex* tail;
//    Edge* eList;
//    int vSize;
//    int eSize;
//};
//
//Graph* constructGraph(const int n, const int m) {
//    Graph* graph = (Graph*)calloc(1, sizeof(Graph));
//    graph->eList = (Edge*)calloc(1, sizeof(Edge));          // dummy head (edges list)
//    graph->vList = (Vertex*)calloc(1, sizeof(Vertex));      // dummy head (vetices list)
//    graph->tail = graph->vList;
//
//    for (int i = 0; i < n; i++) {
//        addVertex(graph, (i + 1));
//    }
//
//    for (int i = 0; i < m; i++)
//    {
//        int u, v;
//        scanf("%d %d", &u, &v);
//        addEdge(graph, u, v, 0);
//    }
//
//    return graph;
//}
//
//Vertex* addVertex(Graph* graph, int vName)
//{
//    // 정점 동적할당 및 초기화
//    Vertex* newV = (Vertex*)calloc(1, sizeof(Vertex));
//    newV->list = (Node*)calloc(1, sizeof(Node));
//    newV->vName = vName;
//    newV->next = graph->tail->next;
//
//    // 그래프의 정점 리스트에 새로운 정점 추가
//    graph->tail->next = newV;
//    graph->tail = newV;
//    graph->vSize++;
//    return newV;
//}
//
//void addEdge(Graph* graph, const int v1Name, const int v2Name, const int weight)
//{
//    // 간선 동적할당 및 초기화
//    Edge* newEdge = (Edge*)calloc(1, sizeof(Edge));
//    newEdge->next = graph->eList->next;
//    newEdge->v1 = findVertex(graph, v1Name);
//    newEdge->v2 = findVertex(graph, v2Name);
//    newEdge->weight = weight;
//    // 그래프의 간선 리스트에 새로운 간선 추가
//    graph->eList->next = newEdge;
//    graph->eSize++;
//
//    Vertex* target;
//
//    // 정점 v1 탐색 및 부착 리스트 갱신
//    target = newEdge->v1;
//    target->degree++;
//    addNode(target, newEdge);
//
//    // 정점 v2 탐색
//    target = newEdge->v2;
//    target->degree++;
//
//    // 간선이 루프가 아닌 경우 v2의 부착 리스트 갱신
//    if (v1Name != v2Name) {
//        addNode(target, newEdge);
//    }
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
//_Bool compPrior(int vertexName, Edge* newEdge, Edge* existingEdge)
//{
//    int newAdjName, existingAdjName;
//
//    // 두 간선 구조체에 대해 v1, v2 중 인접 정점 찾기
//    if (vertexName == newEdge->v1->vName)
//        newAdjName = newEdge->v2->vName;
//    else
//        newAdjName = newEdge->v1->vName;
//
//    if (vertexName == existingEdge->v1->vName)
//        existingAdjName = existingEdge->v2->vName;
//    else
//        existingAdjName = existingEdge->v1->vName;
//
//    // 인접 정점의 번호 비교
//    return newAdjName <= existingAdjName;
//}
//
//void DFS(Graph* graph, const int s)
//{
//    Vertex* cV = findVertex(graph, s);
//    initLabel(graph);
//    for (int i = 0; i < graph->vSize; i++)
//    {
//        if (cV->label == FRESH)
//        {
//            rDFS(graph, cV);
//        }
//        cV = cV->next;
//        if (cV == NULL)
//        {
//            cV = graph->vList->next;
//        }
//    }
//}
//
//void rDFS(Graph* graph, Vertex* v)
//{
//    v->label = VISITED;
//    printf("%d\n", v->vName);
//    Node* cN = v->list;
//    Edge* cE = v->list->edge;
//    Vertex* W;
//    while (cN->next != NULL)
//    {
//        cN = cN->next;
//        cE = cN->edge;
//        if (cE->label == FRESH)
//        {
//            W = opposite(graph, v, cE);
//            if (W->label == FRESH)
//            {
//                cE->label = TREE;
//                rDFS(graph, W);
//            }
//            else
//            {
//                cE->label = BACK;
//            }
//        }
//    }
//}
//
//void initLabel(Graph* graph)
//{
//    Vertex* cV = graph->vList;
//    Edge* cE = graph->eList;
//    for (int i = 0; i < graph->vSize; i++)
//    {
//        cV = cV->next;
//        cV->label = FRESH;
//    }
//    for (int i = 0; i < graph->eSize; i++)
//    {
//        cE = cE->next;
//        cE->label = FRESH;
//    }
//}
//
//Vertex* opposite(Graph* graph, const Vertex* v, const Edge* e)
//{
//    if (v->vName == e->v1->vName)
//        return e->v2;
//    else
//        return e->v1;
//}
//
//Node* addNode(Vertex* vertex, Edge* edge)
//{
//    Node* newNode = (Node*)calloc(1, sizeof(Node));
//    Node* beforeNode = vertex->list;
//    Node* currentNode = beforeNode->next;
//
//    while (currentNode != NULL) {
//        // 인접 정점의 번호를 비교해 올바른 위치 찾으면 종료
//        if (compPrior(vertex->vName, edge, currentNode->edge)) {
//            break;
//        }
//        beforeNode = beforeNode->next;
//        currentNode = beforeNode->next;
//    }
//
//    newNode->next = currentNode;
//    beforeNode->next = newNode;
//    newNode->edge = edge;
//    return newNode;
//}
//
//_Bool printAdjacentVertices(Graph* graph, const int vName)
//{
//    Vertex* targetVertex = findVertex(graph, vName);
//    // vName이 존재하지 않는 경우
//    if (targetVertex == NULL) {
//        return 0;
//    }
//
//    Node* currentNode = targetVertex->list->next;
//    Edge* currentEdge;
//    // vName의 인접 정점이 없는 경우
//    if (currentNode == NULL) {
//        return 0;
//    }
//
//    while (currentNode != NULL) {
//        currentEdge = currentNode->edge;
//        // 인접 정점을 출력
//        if (currentEdge->v1->vName == vName)
//            printf(" %d", currentEdge->v2->vName);
//        else
//            printf(" %d", currentEdge->v1->vName);
//        // 간선의 가중치 출력
//        printf(" %d", currentEdge->weight);
//        currentNode = currentNode->next;
//    }
//
//    return 1;
//}
//
//_Bool checkEdge(Node* node, const int v1, const int v2) {
//    if (node->edge->v1->vName == v1 && node->edge->v2->vName == v2)
//        return 1;
//    else if (node->edge->v1->vName == v2 && node->edge->v2->vName == v1)
//        return 1;
//    else
//        return 0;
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
//        removeEdge(graph, vertex1, vertex2);
//        return 1;
//    }
//
//    Node* node;
//    // v1, v2 중 차수가 낮은 정점의 부착리스트 선택
//    if (vertex1->degree < vertex2->degree)
//        node = vertex1->list->next;
//    else
//        node = vertex2->list->next;
//
//    // 간선을 찾는데 성공하면 가중치 갱신
//    while (node != NULL) {
//        if (checkEdge(node, v1, v2)) {
//            node->edge->weight = newWeight;
//            break;
//        }
//        node = node->next;
//    }
//
//    // 간선을 찾지 못 하면 새롭게 추가
//    if (node == NULL) {
//        addEdge(graph, v1, v2, newWeight);
//    }
//
//    return 1;
//}
//
//void removeEdge(Graph* graph, Vertex* v1, Vertex* v2)
//{
//    Node* beforeNode = v1->list;
//    Node* targetNode = v1->list->next;
//    Edge* beforeEdge = graph->eList;
//    Edge* targetEdge = graph->eList->next;
//
//    // 정점 v1의 부착리스트 갱신 및 삭제할 edge 찾기
//    while (targetNode != NULL) {
//        if (checkEdge(targetNode, v1->vName, v2->vName)) {
//            targetEdge = targetNode->edge;
//            beforeNode->next = targetNode->next;
//            free(targetNode);
//            break;
//        }
//        beforeNode = beforeNode->next;
//        targetNode = beforeNode->next;
//    }
//
//    // 정점 v2의 부착리스트 갱신
//    beforeNode = v2->list;
//    targetNode = v2->list->next;
//    while (targetNode != NULL) {
//        if (targetNode->edge == targetEdge) {
//            beforeNode->next = targetNode->next;
//            free(targetNode);
//            break;
//        }
//        beforeNode = beforeNode->next;
//        targetNode = beforeNode->next;
//    }
//
//    // 간선 제거 및 간선 리스트 갱신
//    while (beforeEdge->next != targetEdge)
//        beforeEdge = beforeEdge->next;
//    beforeEdge->next = targetEdge->next;
//    free(targetEdge);
//
//}
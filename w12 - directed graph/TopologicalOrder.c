#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *next;
    int edgeIdx;
} Node;

typedef struct Vertex
{
    Node *list;
    char name;
    int inDegree;
} Vertex;

typedef struct Edge
{
    int src, dest;
} Edge;

typedef struct Graph
{
    Vertex vertices[100];
    Edge edges[1000];
}  Graph;

int n, m;
Graph graph = {0};
int *topOrder;
int *Q;
int head, tail;

void buildGraph();
void insertVertex(char vName, int i);
void insertDirectedEdge(char uName, char vName, int i);
int getIndex(char vName);
void addFirst(Node *H, int i);
void topologicalSort();
_Bool isEmpty();
void enqueue(int i);
int dequeue();

int main()
{
    buildGraph();
    topOrder = (int *)calloc(n + 1, sizeof(int));
    Q = (int *)calloc(n, sizeof(int));

    topologicalSort();

    if (topOrder[0] == 0)
    {
        puts("0");
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            printf("%c ", graph.vertices[topOrder[i]].name);
        }
    }
}

void buildGraph()
{
    // vertices
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        char name;

        scanf(" %c", &name);
        insertVertex(name, i);
    }

    // edges
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        char v1, v2;

        scanf(" %c %c", &v1, &v2);
        insertDirectedEdge(v1, v2, i);
    }
}

void insertVertex(char vName, int i)
{
    graph.vertices[i].name = vName;
    graph.vertices[i].inDegree = 0;
    graph.vertices[i].list = (Node *)calloc(1, sizeof(Node)); // dummy head
}

void insertDirectedEdge(char uName, char vName, int i)
{
    int uIdx = getIndex(uName);
    int vIdx = getIndex(vName);

    graph.edges[i].src = uIdx;
    graph.edges[i].dest = vIdx;
    
    graph.vertices[vIdx].inDegree++;

    addFirst(graph.vertices[uIdx].list, i);
}

int getIndex(char vName)
{
    for (int i = 0; i < n; i++)
    {
        if (graph.vertices[i].name == vName)
        {
            return i;
        }
    }

    return -1;
}

void addFirst(Node *H, int i)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->edgeIdx = i;
    newNode->next = H->next;
    H->next = newNode;
}

void topologicalSort()
{
    head = 0;
    tail = 0;

    int in[n];

    for (int i = 0; i < n; i++)
    {
        in[i] = graph.vertices[i].inDegree;
        if (in[i] == 0)
        {
            enqueue(i);
        }
    }

    int t = 1;

    while (!isEmpty())
    {
        int u = dequeue();
        topOrder[t] = u;
        t++;

        Node* node = graph.vertices[u].list->next;

        while(node)
        {
            int w = graph.edges[node->edgeIdx].dest;
            in[w]--;
            if (in[w] == 0)
            {
                enqueue(w);
            }
            node = node->next;
        }
    }

    if (t <= n)
    {
        topOrder[0] = 0;
    }
    else
    {
        topOrder[0] = 1;
    }
}

_Bool isEmpty()
{
    return head == tail;
}

void enqueue(int i)
{
    Q[head++] = i;
}

int dequeue()
{
    tail++;
    return Q[tail - 1];
}
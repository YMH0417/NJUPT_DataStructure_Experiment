#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#define ERROR 0
#define OK 1
#define Overflow 2      // Overflow indicator
#define Underflow 3     // Underflow indicator
#define NotPresent 4    // Element not present indicator
#define Duplicate 5     // Duplicate element indicator
typedef int ElemType;
typedef int Status;

// Structure definition for adjacency list node
typedef struct ENode {
    int adjVex;              // Adjacent vertex of any vertex u
    ElemType w;              // Weight of the edge
    struct ENode* nextArc;   // Pointer to the next edge node
} ENode;

// Structure definition for graph using adjacency list
typedef struct {
    int n;           // Current number of vertices in the graph
    int e;           // Current number of edges in the graph
    ENode** a;       // Pointer to an array of pointers (adjacency list)
} LGraph;

// Structure definition for circular queue
typedef struct {
    int front;       // Front of the queue
    int rear;        // Rear of the queue
    int maxSize;     // Maximum capacity of the queue
    ElemType* element; // Array to hold queue elements
} Queue;

// Creates an empty queue that can hold mSize elements
void Create(Queue* Q, int mSize) {
    Q->maxSize = mSize;
    Q->element = (ElemType*)malloc(sizeof(ElemType) * mSize);
    Q->front = Q->rear = 0;
}

// Checks if the queue is empty, returns TRUE if empty, otherwise FALSE
BOOL IsEmpty(Queue* Q) {
    return Q->front == Q->rear;
}

// Checks if the queue is full, returns TRUE if full, otherwise FALSE
BOOL IsFULL(Queue* Q) {
    return (Q->rear + 1) % Q->maxSize == Q->front;
}

// Gets the front element of the queue and returns it through x. Returns TRUE if successful, otherwise FALSE
BOOL Front(Queue* Q, ElemType* x) {
    if (IsEmpty(Q))      // Handle empty queue
        return FALSE;
    *x = Q->element[(Q->front + 1) % Q->maxSize];
    return TRUE;
}

// Inserts element x at the rear of queue Q. Returns TRUE if successful, otherwise FALSE
BOOL EnQueue(Queue* Q, ElemType x) {
    if (IsFULL(Q))      // Handle overflow
        return FALSE;
    Q->rear = (Q->rear + 1) % Q->maxSize;
    Q->element[Q->rear] = x;
    return TRUE;
}

// Deletes the front element of queue Q. Returns TRUE if successful, otherwise FALSE
BOOL DeQueue(Queue* Q) {
    if (IsEmpty(Q)) {   // Handle empty queue
        return FALSE;
    }
    Q->front = (Q->front + 1) % Q->maxSize;
    return TRUE;
}

// Initializes the adjacency list
Status Init(LGraph* lg, int nSize) {
    int i;
    lg->n = nSize;
    lg->e = 0;
    lg->a = (ENode**)malloc(nSize * sizeof(ENode*)); // Dynamically create an array of pointers with length n
    if (!lg->a) return ERROR;
    else {
        for (i = 0; i < lg->n; i++) {
            lg->a[i] = NULL;  // Initialize the adjacency list to NULL
        }
        return OK;
    }
}

// Searches for an edge in the adjacency list
Status Exist(LGraph* lg, int u, int v) {
    ENode* p;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return ERROR;
    p = lg->a[u];   // Pointer p points to the first edge node of vertex u's adjacency list
    while (p && p->adjVex != v) {
        p = p->nextArc;
    }
    if (!p) return ERROR; // If edge is not found, return ERROR
    else return OK;
}

// Inserts an edge into the adjacency list
Status Insert(LGraph* lg, int u, int v, ElemType w) {
    ENode* p;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return ERROR;
    if (Exist(lg, u, v)) return Duplicate; // If edge exists, return Duplicate error
    p = (ENode*)malloc(sizeof(ENode));    // Allocate memory for the new edge node
    p->adjVex = v;
    p->w = w;
    p->nextArc = lg->a[u];               // Insert the new edge node at the beginning of the list
    lg->a[u] = p;
    lg->e++;                             // Increment the edge count
    return OK;
}

// DFS traversal for a single vertex in the adjacency list
void DFS(int v, int visited[], LGraph g) {
    ENode* w;
    printf("%d ", v);                    // Visit vertex v
    visited[v] = 1;                      // Mark vertex v as visited
    for (w = g.a[v]; w; w = w->nextArc) {   // Traverse all adjacent vertices of v
        if (!visited[w->adjVex]) {
            DFS(w->adjVex, visited, g);  // Recursively call DFS for unvisited adjacent vertices
        }
    }
}

// DFS traversal for the entire graph in the adjacency list
void DFSGraph(LGraph g) {
    int i;
    int* visited = (int*)malloc(g.n * sizeof(int)); // Dynamically create the visited array
    for (i = 0; i < g.n; i++) {
        visited[i] = 0; // Initialize visited array
    }
    for (i = 0; i < g.n; i++) {            // Check each vertex, if not visited, call DFS
        if (!visited[i]) {
            DFS(i, visited, g);
        }
    }
    free(visited);                         // Free the visited array
}

// BFS traversal for a single vertex in the adjacency list
void BFS(int v, int visited[], LGraph g) {
    ENode* w;
    Queue q;
    Create(&q, g.n);                      // Initialize queue
    visited[v] = 1;                       // Mark vertex v as visited
    printf("%d ", v);                     // Visit vertex v
    EnQueue(&q, v);                       // Enqueue vertex v
    while (!IsEmpty(&q)) {
        Front(&q, &v);
        DeQueue(&q);                     // Dequeue the front vertex
        for (w = g.a[v]; w; w = w->nextArc) { // Traverse all adjacent vertices of v
            if (!visited[w->adjVex]) {    // If adjacent vertex is not visited, visit and enqueue it
                visited[w->adjVex] = 1;
                printf("%d ", w->adjVex);
                EnQueue(&q, w->adjVex);
            }
        }
    }
}

// BFS traversal for the entire graph in the adjacency list
void BFSGraph(LGraph g) {
    int i;
    int* visited = (int*)malloc(g.n * sizeof(int)); // Dynamically create the visited array
    for (i = 0; i < g.n; i++) {                     // Initialize visited array
        visited[i] = 0;
    }
    for (i = 0; i < g.n; i++) {                     // Check each vertex, if not visited, call BFS
        if (!visited[i]) {
            BFS(i, visited, g);
        }
    }
    free(visited);
}

int main() {
    LGraph g;
    int i, u, v, enode, edge;
    ElemType w;
    printf("Please enter the number of the nodes: ");
    scanf_s("%d", &enode);           // Read the number of nodes
    Init(&g, enode);                 // Initialize the graph
    printf("Please enter the number of the edges: ");
    scanf_s("%d", &edge);            // Read the number of edges
    printf("Enter edges with the order of u, v, w: \n");
    for (i = 0; i < edge; i++) {     // Read edges and add them to the graph
        scanf_s("%d%d%d", &u, &v, &w);
        Insert(&g, u, v, w);
    }
    printf("DFS:\n");
    DFSGraph(g);                     // Perform DFS traversal
    printf("\nBFS:\n");
    BFSGraph(g);                     // Perform BFS traversal
    return 0;
}

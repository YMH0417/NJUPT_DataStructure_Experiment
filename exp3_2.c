#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define ERROR 0         // Define error status
#define OK 1            // Define success status
#define Overflow 2      // Define overflow status
#define Underflow 3     // Define underflow status
#define NotPresent 4    // Define "not present" status
#define Duplicate 5     // Define duplicate status

typedef int ElemType;   // Define element type as integer
typedef int Status;     // Define status type as integer

// Define structure for the graph with adjacency matrix representation
typedef struct {
    ElemType** a;       // Adjacency matrix
    int n;              // Number of vertices
    int e;              // Number of edges
    ElemType noEdge;    // Value representing no edge between vertices
} mGraph;

// Define structure for a circular queue
typedef struct {
    int front;          // Index of the front element
    int rear;           // Index of the rear element
    int maxSize;        // Maximum size of the queue
    ElemType* element;  // Array to store queue elements
} Queue;

// Initialize the queue with a given size
void Create(Queue* Q, int mSize) {
    Q->maxSize = mSize;                                  // Set maximum size of the queue
    Q->element = (ElemType*)malloc(sizeof(ElemType) * mSize); // Allocate memory for elements
    Q->front = Q->rear = 0;                              // Initialize front and rear indices
}

// Check if the queue is empty
int IsEmpty(Queue* Q) {
    return Q->front == Q->rear;
}

// Check if the queue is full
int IsFULL(Queue* Q) {
    return (Q->rear + 1) % Q->maxSize == Q->front;
}

// Retrieve the front element of the queue without removing it
int Front(Queue* Q, ElemType* x) {
    if (IsEmpty(Q))
        return 0;
    *x = Q->element[(Q->front + 1) % Q->maxSize];
    return 1;
}

// Add an element to the rear of the queue
int EnQueue(Queue* Q, ElemType x) {
    if (IsFULL(Q))
        return 0;
    Q->rear = (Q->rear + 1) % Q->maxSize; // Update rear index circularly
    Q->element[Q->rear] = x;              // Insert element
    return 1;
}

// Remove the front element from the queue
int DeQueue(Queue* Q) {
    if (IsEmpty(Q))
        return 0;
    Q->front = (Q->front + 1) % Q->maxSize; // Update front index circularly
    return 1;
}

// Initialize the graph with a specified size and no-edge value
Status Init(mGraph* mg, int nSize, ElemType noEdgeValue) {
    int i, j;
    mg->n = nSize;                               // Set number of vertices
    mg->e = 0;                                   // Initialize number of edges to 0
    mg->noEdge = noEdgeValue;                    // Set value representing no edge
    mg->a = (ElemType**)malloc(nSize * sizeof(ElemType*)); // Allocate memory for adjacency matrix
    if (!mg->a) return ERROR;                    // Return error if allocation fails
    for (i = 0; i < mg->n; i++) {
        mg->a[i] = (ElemType*)malloc(nSize * sizeof(ElemType)); // Allocate row
        for (j = 0; j < mg->n; j++) {
            mg->a[i][j] = mg->noEdge;           // Initialize with no-edge value
        }
        mg->a[i][i] = 0;                         // Set self-loop edge weight to 0
    }
    return OK;
}

// Destroy the graph by freeing allocated memory
int Destroy(mGraph* mg) {
    int i;
    for (i = 0; i < mg->n; i++) {
        free(mg->a[i]);                          // Free each row
    }
    free(mg->a);                                 // Free the adjacency matrix
    return 1;
}

// Check if an edge exists between two vertices
Status Exist(mGraph* mg, int u, int v) {
    if (u < 0 || v < 0 || u >= mg->n || v >= mg->n || u == v || mg->a[u][v] == mg->noEdge)
        return ERROR;                            // Return error if edge does not exist
    return OK;
}

// Insert an edge between two vertices with a given weight
Status Insert(mGraph* mg, int u, int v, ElemType w) {
    if (u < 0 || v < 0 || u >= mg->n || v >= mg->n || u == v) return ERROR;
    if (mg->a[u][v] != mg->noEdge) return Duplicate;
    mg->a[u][v] = w;                             // Set weight of edge
    mg->e++;                                     // Increment edge count
    return OK;
}

// Remove an edge between two vertices
Status Remove(mGraph* mg, int u, int v) {
    if (u < 0 || v < 0 || u >= mg->n || v >= mg->n || u == v) return ERROR;
    if (mg->a[u][v] == mg->noEdge) return NotPresent;
    mg->a[u][v] = mg->noEdge;                    // Set to no-edge value
    mg->e--;                                     // Decrement edge count
    return OK;
}

// Depth-First Search (DFS) starting from a vertex
void DFS(int v, int visited[], mGraph g) {
    int j;
    printf("%d ", v);                            // Print the visited vertex
    visited[v] = 1;                              // Mark vertex as visited
    for (j = 0; j < g.n; j++) {
        if (!visited[j] && g.a[v][j] > 0) {
            DFS(j, visited, g);                  // Recursively visit adjacent vertices
        }
    }
}

// Perform DFS on the entire graph
void DFSGraph(mGraph g) {
    int i;
    int* visited = (int*)malloc(g.n * sizeof(int)); // Allocate memory for visited array
    for (i = 0; i < g.n; i++) {
        visited[i] = 0;                           // Initialize all vertices as unvisited
    }
    for (i = 0; i < g.n; i++) {
        if (!visited[i]) {
            DFS(i, visited, g);                   // Start DFS if vertex is unvisited
        }
    }
    free(visited);                                // Free visited array
}

// Breadth-First Search (BFS) starting from a vertex
void BFS(int v, int visited[], mGraph g) {
    Queue q;
    Create(&q, g.n);                              // Initialize queue
    visited[v] = 1;                               // Mark vertex as visited
    printf("%d ", v);                             // Print the visited vertex
    EnQueue(&q, v);                               // Enqueue the starting vertex
    while (!IsEmpty(&q)) {
        Front(&q, &v);                            // Get front vertex
        DeQueue(&q);                              // Remove front vertex from queue
        for (int i = 0; i < g.n; i++) {
            if (!visited[i] && g.a[v][i] > 0) {
                visited[i] = 1;                   // Mark as visited
                printf("%d ", i);                 // Print the visited vertex
                EnQueue(&q, i);                   // Enqueue adjacent vertex
            }
        }
    }
}

// Perform BFS on the entire graph
void BFSGraph(mGraph g) {
    int i;
    int* visited = (int*)malloc(g.n * sizeof(int)); // Allocate memory for visited array
    for (i = 0; i < g.n; i++) {
        visited[i] = 0;                           // Initialize all vertices as unvisited
    }
    for (i = 0; i < g.n; i++) {
        if (!visited[i]) {
            BFS(i, visited, g);                   // Start BFS if vertex is unvisited
        }
    }
    free(visited);                                // Free visited array
}

int main() {
    mGraph g;
    int nSize, edge, u, v, i;
    ElemType w;
    printf("Please enter the size of the graph: ");
    scanf_s("%d", &nSize);                        // Input graph size
    Init(&g, nSize, -1);                          // Initialize graph
    printf("Please enter the number of the edges: ");
    scanf_s("%d", &edge);                         // Input number of edges

    printf("Enter edges with the order of u, v, w: \n");
    for (i = 0; i < edge; i++) {
        scanf_s("%d%d%d", &u, &v, &w);            // Input each edge's vertices and weight
        Insert(&g, u, v, w);                      // Insert edge into graph
    }
    printf("DFS:\n");
    DFSGraph(g);                                  // Perform DFS
    printf("\nBFS:\n");
    BFSGraph(g);                                  // Perform BFS

    Destroy(&g);                                  // Free graph memory
    return 0;
}

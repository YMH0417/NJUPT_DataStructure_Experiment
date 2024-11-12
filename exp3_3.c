#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#define ERROR 0
#define OK 1
#define Overflow 2     // Indicates overflow
#define Underflow 3    // Indicates underflow
#define NotPresent 4   // Indicates element does not exist
#define Duplicate 5    // Indicates duplicate element
typedef int ElemType;
typedef int Status;


// Definition of the adjacency list structure
typedef struct ENode {
    int adjVex;             // Adjacent vertex of any vertex u
    ElemType w;             // Weight of the edge
    struct ENode* nextArc;  // Pointer to the next edge node
} ENode;

typedef struct {
    int n;                  // Current number of vertices in the graph
    int e;                  // Current number of edges in the graph
    ENode** a;              // Pointer to a 1D array of pointers
} LGraph;


// Initialization of the adjacency list
Status Init(LGraph* lg, int nSize) {
    int i;
    lg->n = nSize;  // Set the number of vertices
    lg->e = 0;      // Initialize the number of edges to 0
    lg->a = (ENode**)malloc(nSize * sizeof(ENode*));  // Dynamically create a 1D array of pointers with length n
    if (!lg->a) return ERROR; // Check if memory allocation is successful
    else {
        for (i = 0; i < lg->n; i++) {
            lg->a[i] = NULL;  // Initialize each element in the pointer array to NULL
        }
        return OK;
    }
}


// Destroy the adjacency list (changed to int type to return a value)
int Destory(LGraph* lg) {
    int i;
    ENode* p, * q;
    for (i = 0; i < lg->n; i++) { // Loop through each vertex
        p = lg->a[i];             // Pointer p points to the first edge node of the vertex i¡¯s linked list
        q = p;
        while (p) {               // Free all edge nodes in the linked list of vertex i
            p = p->nextArc;
            free(q);
            q = p;
        }
    }
    free(lg->a);                  // Free the memory of the 1D pointer array a
    return 1;                     // Return a value, as it's an int function
}


// Search for an edge in the adjacency list
Status Exist(LGraph* lg, int u, int v) {
    ENode* p;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return ERROR; // Validate vertices u and v
    p = lg->a[u];                  // Pointer p points to the first edge node of the vertex u¡¯s linked list
    while (p != NULL && p->adjVex != v) { // Traverse to find if there is an edge between u and v
        p = p->nextArc;
    }
    if (!p) return ERROR;          // If edge is not found, return ERROR
    else return OK;
}


// Insert an edge into the adjacency list
Status Insert(LGraph* lg, int u, int v, ElemType w) {
    ENode* p;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return ERROR; // Validate vertices u and v
    if (Exist(lg, u, v)) return Duplicate;  // If edge already exists, return Duplicate error
    p = (ENode*)malloc(sizeof(ENode)); // Allocate memory for a new edge node
    p->adjVex = v;                     // Set the adjacent vertex to v
    p->w = w;                          // Set the weight of the edge
    p->nextArc = lg->a[u];             // Insert the new edge node at the beginning of the linked list
    lg->a[u] = p;
    lg->e++;                           // Increase the edge count
    return OK;
}


// Remove an edge from the adjacency list
Status Remove(LGraph* lg, int u, int v) {
    ENode* p, * q;
    if (u < 0 || v < 0 || u > lg->n - 1 || v > lg->n - 1 || u == v) return ERROR; // Validate vertices u and v
    p = lg->a[u];
    q = NULL;
    while (p && p->adjVex != v) {    // Search to check if the edge to be deleted exists
        q = p;
        p = p->nextArc;
    }
    if (!p) return NotPresent;       // If p is NULL, the edge does not exist
    if (q) q->nextArc = p->nextArc;  // Remove the edge from the linked list
    else lg->a[u] = p->nextArc;
    free(p);                         // Free memory of the edge node
    lg->e--;                         // Decrease the edge count
    return OK;
}


int main() {
    LGraph g;                             // Declare graph variable
    int nSize, edge, u, v, i;             // Declare variables for input
    ElemType w;                           // Variable to store edge weight

    printf("Please enter the number of nodes in the graph: ");
    scanf_s("%d", &nSize);                // Input number of nodes
    Init(&g, nSize);                      // Initialize graph

    printf("Please enter the number of edges: ");
    scanf_s("%d", &edge);                 // Input number of edges

    printf("Enter edges with the order of u, v, w: \n");
    for (i = 0; i < edge; i++) {
        scanf_s("%d%d%d", &u, &v, &w);    // Input edge endpoints and weight
        Insert(&g, u, v, w);              // Insert each edge into the graph
    }

    printf("Please enter the edge to delete:\n");
    printf("Enter the u of the edge: ");
    scanf_s("%d", &u);                    // Input node u for edge deletion

    printf("Enter the v of the edge: ");
    scanf_s("%d", &v);                    // Input node v for edge deletion
    Remove(&g, u, v);                     // Remove the specified edge

    printf("Now searching for the edge just deleted: ");
    if (Exist(&g, u, v))                  // Check if the deleted edge still exists
        printf("OK\n");
    else
        printf("ERROR\n");

    printf("Now destroying the graph: ");
    if (Destory(&g))                      // Destroy the graph and free memory
        printf("OK\n");
    else
        printf("ERROR\n");

    return 0;                             // End of program
}

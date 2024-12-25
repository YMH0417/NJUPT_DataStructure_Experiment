#include <stdio.h>      // Include standard input-output header
#include <stdlib.h>     // Include standard library header for dynamic memory functions

// Define status codes for various conditions
#define ERROR 0
#define OK 1
#define Overflow 2    
#define Underflow 3   
#define NotPresent 4  
#define Duplicate 5   

typedef int ElemType;   // Define ElemType as an integer
typedef int Status;     // Define Status as an integer for function return types

// Define structure for adjacency matrix graph
typedef struct {
    ElemType** a;       // Pointer to adjacency matrix
    int n;              // Number of nodes
    int e;              // Number of edges
    ElemType noEdge;    // Value representing no edge between nodes
} mGraph;

// Initialize the graph with a given number of nodes and no-edge value
Status Init(mGraph* mg, int nSize, ElemType noEdgeValue) {
    int i, j;
    mg->n = nSize;                        // Set number of nodes
    mg->e = 0;                            // Initialize edge count to zero
    mg->noEdge = noEdgeValue;             // Set the no-edge indicator
    mg->a = (ElemType**)malloc(nSize * sizeof(ElemType*)); // Allocate memory for adjacency matrix rows
    if (!mg->a) return ERROR;             // Return error if memory allocation fails

    for (i = 0; i < mg->n; i++) {
        mg->a[i] = (ElemType*)malloc(nSize * sizeof(ElemType)); // Allocate memory for each row
        for (j = 0; j < mg->n; j++) {
            mg->a[i][j] = mg->noEdge;     // Initialize all entries to no-edge value
        }
        mg->a[i][i] = 0;                  // Set self-loop weight to zero
    }
    return OK;                            // Return OK status
}

// Free the memory allocated for the graph
int Destory(mGraph* mg) {
    int i;
    for (i = 0; i < mg->n; i++) {
        free(mg->a[i]);                   // Free each row in the adjacency matrix
    }
    free(mg->a);                          // Free the matrix pointer itself
    return 1;                             // Return 1 to indicate successful destruction
}

// Check if an edge exists between nodes u and v
Status Exist(mGraph* mg, int u, int v) {
    if (u < 0 || v < 0 || u > mg->n - 1 || v > mg->n - 1 || u == v || mg->a[u][v] == mg->noEdge)
        return ERROR;                     // Return ERROR if edge does not exist
    return OK;                            // Return OK if edge exists
}

// Insert an edge with weight w between nodes u and v
Status Insert(mGraph* mg, int u, int v, ElemType w) {
    if (u < 0 || v < 0 || u > mg->n - 1 || v > mg->n - 1 || u == v)
        return ERROR;                     // Return ERROR if nodes are invalid or are the same
    if (mg->a[u][v] != mg->noEdge)
        return Duplicate;                 // Return Duplicate if edge already exists
    mg->a[u][v] = w;                      // Set the weight of edge u-v
    mg->e++;                              // Increment edge count
    return OK;                            // Return OK status
}

// Remove the edge between nodes u and v
Status Remove(mGraph* mg, int u, int v) {
    if (u < 0 || v < 0 || u > mg->n - 1 || v > mg->n - 1 || u == v)
        return ERROR;                     // Return ERROR if nodes are invalid or are the same
    if (mg->a[u][v] == mg->noEdge)
        return NotPresent;                // Return NotPresent if edge does not exist
    mg->a[u][v] = mg->noEdge;             // Set edge weight to no-edge value to remove it
    mg->e--;                              // Decrement edge count
    return OK;                            // Return OK status
}

// Main function to test graph operations
int main() {
    mGraph g;                             // Declare a graph variable
    int nSize, edge, u, v, i;             // Declare variables for input
    ElemType w;                           // Variable to store edge weight

    printf("Please enter the number of nodes in the graph: ");
    scanf_s("%d", &nSize);                // Input number of nodes
    Init(&g, nSize, -1);                  // Initialize graph with no-edge value as -1

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

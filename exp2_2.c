#include <stdio.h>    // Include standard input/output library
#include <stdlib.h>   // Include standard library for memory allocation
#define ElemType char // Define ElemType as char

typedef struct btnode {  // Define binary tree node structure
    ElemType element;    // Element of the node
    struct btnode* lChild; // Pointer to the left child
    struct btnode* rChild; // Pointer to the right child
} BTNode;

void PreOrderTransverse(BTNode* t); // Function prototype for pre-order traversal
void InOrderTransverse(BTNode* t);  // Function prototype for in-order traversal
void PostOrderTransverse(BTNode* t); // Function prototype for post-order traversal
int CountNodes(BTNode* t);           // Function prototype to count nodes
int CountLeafNodes(BTNode* t);       // Function prototype to count leaf nodes
int CalculateHeight(BTNode* t);      // Function prototype to calculate height

void PreOrderTransverse(BTNode* t) { // Pre-order traversal function
    if (t == NULL) {                  // Check if the current node is NULL
        return;                       // Return if it is NULL
    }
    printf("%c ", t->element);        // Print the current node's element
    PreOrderTransverse(t->lChild);    // Traverse the left child
    PreOrderTransverse(t->rChild);    // Traverse the right child
}

void InOrderTransverse(BTNode* t) { // In-order traversal function
    if (t == NULL) {                  // Check if the current node is NULL
        return;                       // Return if it is NULL
    }
    InOrderTransverse(t->lChild);     // Traverse the left child
    printf("%c ", t->element);        // Print the current node's element
    InOrderTransverse(t->rChild);     // Traverse the right child
}

void PostOrderTransverse(BTNode* t) { // Post-order traversal function
    if (t == NULL) {                  // Check if the current node is NULL
        return;                       // Return if it is NULL
    }
    PostOrderTransverse(t->lChild);    // Traverse the left child
    PostOrderTransverse(t->rChild);    // Traverse the right child
    printf("%c ", t->element);        // Print the current node's element
}

BTNode* PreCreateBt(BTNode* t) {      // Function to create binary tree from pre-order input
    char c;                            // Character to hold input
    c = getchar();                     // Read a character from input
    if (c == '#') {                   // Check for the null node indicator
        t = NULL;                     // Set the node to NULL
    }
    else {
        t = (BTNode*)malloc(sizeof(BTNode)); // Allocate memory for a new node
        t->element = c;               // Assign the character to the node's element
        t->lChild = PreCreateBt(t->lChild); // Recursively create the left subtree
        t->rChild = PreCreateBt(t->rChild); // Recursively create the right subtree
    }
    return t;                         // Return the created tree node
}

int CountNodes(BTNode* t) {           // Function to count total nodes in the tree
    if (t == NULL) {                  // Check if the current node is NULL
        return 0;                     // Return 0 if it is NULL
    }
    return 1 + CountNodes(t->lChild) + CountNodes(t->rChild); // Count the current node and children
}

int CountLeafNodes(BTNode* t) {       // Function to count leaf nodes in the tree
    if (t == NULL) {                  // Check if the current node is NULL
        return 0;                     // Return 0 if it is NULL
    }
    if (t->lChild == NULL && t->rChild == NULL) { // Check if the node is a leaf
        return 1;                     // Return 1 for a leaf node
    }
    return CountLeafNodes(t->lChild) + CountLeafNodes(t->rChild); // Count leaf nodes in children
}

int CalculateHeight(BTNode* t) {      // Function to calculate the height of the tree
    if (t == NULL) {                  // Check if the current node is NULL
        return 0;                     // Return 0 for NULL node
    }
    int leftHeight = CalculateHeight(t->lChild); // Calculate left subtree height
    int rightHeight = CalculateHeight(t->rChild); // Calculate right subtree height
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1; // Return max height + 1
}

int main() {                           // Main function
    BTNode* t = NULL;                 // Declare the root of the tree
    printf("Enter the pre-order traversal of the binary tree (use # for null nodes):\n"); // Prompt for input
    t = PreCreateBt(t);               // Create the binary tree from input

    int nodeCount = CountNodes(t);    // Count total nodes
    int leafCount = CountLeafNodes(t); // Count leaf nodes
    int height = CalculateHeight(t);   // Calculate tree height

    printf("\nNumber of nodes in the binary tree: %d", nodeCount); // Print total nodes
    printf("\nNumber of leaf nodes in the binary tree: %d", leafCount); // Print leaf nodes
    printf("\nHeight of the binary tree: %d\n", height); // Print height

    printf("\nPre-order traversal result:\n"); // Print pre-order result
    PreOrderTransverse(t);                   // Perform pre-order traversal

    printf("\n\nIn-order traversal result:\n"); // Print in-order result
    InOrderTransverse(t);                     // Perform in-order traversal

    printf("\n\nPost-order traversal result:\n"); // Print post-order result
    PostOrderTransverse(t);                    // Perform post-order traversal

    return 0;                                 // Return success
}

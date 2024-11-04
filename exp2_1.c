#include <stdio.h>    // Include standard input/output library
#include <stdlib.h>   // Include standard library for memory allocation
#define ElemType char // Define ElemType as char

typedef struct btnode {  // Define binary tree node structure
    ElemType element;    // Element of the node
    struct btnode* lChild; // Pointer to the left child
    struct btnode* rChild; // Pointer to the right child
} BTNode;

void PreOrderTransverse(BTNode* t);  // Function prototype for pre-order traversal
void InOrderTransverse(BTNode* t);   // Function prototype for in-order traversal
void PostOrderTransverse(BTNode* t); // Function prototype for post-order traversal

void PreOrderTransverse(BTNode* t) {
    if (t == NULL) {  // If the node is null
        return;       // Return from the function
    }
    printf("%c ", t->element); // Print the element of the node
    PreOrderTransverse(t->lChild); // Recursively traverse the left child
    PreOrderTransverse(t->rChild); // Recursively traverse the right child
}

void InOrderTransverse(BTNode* t) {
    if (t == NULL) {  // If the node is null
        return;       // Return from the function
    }
    InOrderTransverse(t->lChild); // Recursively traverse the left child
    printf("%c ", t->element); // Print the element of the node
    InOrderTransverse(t->rChild); // Recursively traverse the right child
}

void PostOrderTransverse(BTNode* t) {
    if (t == NULL) {  // If the node is null
        return;       // Return from the function
    }
    PostOrderTransverse(t->lChild); // Recursively traverse the left child
    PostOrderTransverse(t->rChild); // Recursively traverse the right child
    printf("%c ", t->element); // Print the element of the node
}

BTNode* PreCreateBt(BTNode* t) {
    char c; // Declare a character variable
    c = getchar(); // Read a character from input
    if (c == '#') { // If the character is '#'
        t = NULL; // Set the node to NULL
    } else {
        t = (BTNode*)malloc(sizeof(BTNode)); // Allocate memory for the node
        t->element = c; // Set the element of the node
        t->lChild = PreCreateBt(t->lChild); // Recursively create the left child
        t->rChild = PreCreateBt(t->rChild); // Recursively create the right child
    }
    return t; // Return the created node
}

int main() {
    BTNode* t = NULL; // Declare a binary tree node pointer and initialize it to NULL
    printf("Enter the pre-order traversal of the binary tree (use # for null nodes):\n"); // Prompt for input
    t = PreCreateBt(t); // Create the binary tree from input

    printf("\nPre-order traversal result:\n"); // Print pre-order traversal header
    PreOrderTransverse(t); // Call pre-order traversal function

    printf("\n\nIn-order traversal result:\n"); // Print in-order traversal header
    InOrderTransverse(t); // Call in-order traversal function

    printf("\n\nPost-order traversal result:\n"); // Print post-order traversal header
    PostOrderTransverse(t); // Call post-order traversal function

    printf("\n"); // Print a newline
    return 0; // Return from the main function
}


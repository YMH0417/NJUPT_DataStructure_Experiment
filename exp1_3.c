#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;  // Define ElemType as int to represent the type of elements stored in the list nodes
typedef int Status;    // Define Status as int to represent the status of function returns (success or failure)

// Define the structure for a list node
typedef struct Node {
    ElemType element;        // The element stored in the node
    struct Node* link;       // Pointer to the next node in the list
} Node;

// Define the structure for the list header
typedef struct {
    struct Node* head;  // Pointer to the head node of the list
    int n;              // Number of elements in the list
} ListHeader;

// Function to initialize the list by creating a head node
Status Init(ListHeader* h) {
    h->head = (Node*)malloc(sizeof(Node));  // Allocate memory for the head node
    if (!h->head) {                         // Check if memory allocation was successful
        return 0;                           // Return 0 if allocation failed
    }
    h->head->link = NULL;                   // Initialize the link pointer of the head node to NULL
    h->n = 0;                               // Initialize the number of elements in the list to 0
    return 1;                               // Return 1 to indicate successful initialization
}

// Function to find the element at position i in the list
Status Find(ListHeader* h, int i, ElemType* x) {
    Node* p;
    int j;
    if (i < 0 || i > h->n - 1) {  // Check if the index i is within valid range
        return 0;                 // Return 0 if the index is invalid
    }
    p = h->head->link;            // Set p to point to the first node (after the head)
    for (j = 0; j < i; j++) {     // Traverse the list to the ith node
        p = p->link;              // Move p to the next node
    }
    *x = p->element;              // Assign the element at the ith node to *x
    return 1;                     // Return 1 to indicate success
}

// Function to insert an element x at position i in the list
Status Insert(ListHeader* h, int i, ElemType x) {
    Node* p, * q;
    int j;
    if (i < -1 || i > h->n - 1) {  // Check if the index i is valid for insertion
        return 0;                  // Return 0 if the index is invalid
    }
    p = h->head;                   // Set p to the head node
    for (j = 0; j <= i; j++) {     // Move p to the ith node
        p = p->link;
    }
    q = (Node*)malloc(sizeof(Node));  // Allocate memory for the new node
    q->element = x;                    // Set the new node's element to x
    q->link = p->link;                 // Set the new node's link to point to the next node
    p->link = q;                       // Link the previous node to the new node
    h->n++;                            // Increment the number of elements in the list
    return 1;                          // Return 1 to indicate success
}

// Function to delete the element at position i in the list
Status Delete(ListHeader* h, int i) {
    int j;
    Node* p, * q;
    if (!h->n) {              // If the list is empty, return failure
        return 0;
        if (i < 0 || i > h->n - 1) {  // Check if the index i is valid for deletion
            return 0;
        }
    }
    q = h->head;                   // Set q to the head node
    for (j = 0; j < i; j++) {      // Move q to the node just before the ith node
        q = q->link;
    }
    p = q->link;                   // Set p to the ith node (the one to be deleted)
    q->link = q->link->link;       // Link the previous node to the next node, skipping the ith node
    free(p);                       // Free the memory of the deleted node
    h->n--;                        // Decrement the number of elements in the list
    return 1;                      // Return 1 to indicate success
}

// Function to output the elements of the list
Status Output(ListHeader* h) {
    Node* p;
    if (!h->n) {                   // If the list is empty, return failure
        return 0;
    }
    p = h->head->link;             // Set p to the first node (after the head)
    while (p) {                    // Traverse the list
        printf("%d ", p->element); // Print the element of the current node
        p = p->link;               // Move to the next node
    }
    printf("\n");                  // Print a newline after the list output
    return 1;                      // Return 1 to indicate success
}

// Function to destroy the list and free all allocated memory
void Destroy(ListHeader* h) {
    Node* p, * q;
    while (h->head->link) {        // While the list is not empty
        q = h->head->link;         // Set q to the first node
        p = h->head->link->link;   // Set p to the next node
        free(h->head->link);       // Free the memory of the current node
        h->head = q;               // Move the head pointer to the next node
    }
}

// Function to reverse the linked list without additional storage
Status Reverse(ListHeader* h) {
    if (!h->head->link || !h->head->link->link) {
        return 1;  // If the list is empty or has only one node, no need to reverse
    }

    Node* prev = NULL;        // Initialize the previous pointer to NULL
    Node* curr = h->head->link;  // Start from the first node (after the head)
    Node* next = NULL;        // This will hold the next node temporarily

    while (curr) {            // Traverse the list
        next = curr->link;    // Store the next node
        curr->link = prev;    // Reverse the link
        prev = curr;          // Move prev to the current node
        curr = next;          // Move curr to the next node
    }

    h->head->link = prev;     // Set the new head of the reversed list
    return 1;                 // Return success
}

// Main function to test the list functions (insert, delete, find, output)
int main() {
    int i, j, delPos, findPos, n, findResult;
    ListHeader list;  // Define a ListHeader to hold the list

    printf("Number of elements:\n");
    scanf_s("%d", &n);  // Input the number of elements in the list
    Init(&list);        // Initialize the list

    printf("Elements: \n");
    for (i = 0; i < n; i++) {
        scanf_s("%d", &j);          // Input each element
        Insert(&list, i - 1, j);    // Insert the element into the list
    }

    printf("Sequence list: ");
    Output(&list);  // Output the elements of the list
    printf("\n");

    printf("Delete element at this position: \n");
    scanf_s("%d", &delPos);         // Input the position of the element to delete
    Delete(&list, delPos);          // Delete the element at the specified position
    printf("Sequence list after deleting this element: ");
    Output(&list);                  // Output the list after deletion
    printf("\n");

    printf("Find element at this position: \n");
    scanf_s("%d", &findPos);        // Input the position of the element to find
    Find(&list, findPos, &findResult);  // Find the element at the specified position
    printf("This element: %d", findResult);  // Output the found element
    printf("\n");

    // Reverse the list
    Reverse(&list);
    printf("\nSequence list after reversing: \n");
    Output(&list);  // Output the reversed list

    Destroy(&list);  // Destroy the list and free the allocated memory

    return 0;        // Program ends successfully
}
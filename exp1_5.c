#include <stdio.h>
#include <stdlib.h>

// Define a structure for polynomial nodes
typedef struct PNode {
    int coef; // Coefficient of the polynomial term
    int exp;  // Exponent of the polynomial term
    struct PNode* link; // Pointer to the next node
} PNode;

// Define a structure for polynomial
typedef struct {
    struct PNode* head; // Head pointer of the polynomial
} Polynominal;

// Function to create a polynomial
void Create(Polynominal* p) {
    PNode* pn, * pre, * q; // Pointers for new node, previous node, and current node
    p->head = (PNode*)malloc(sizeof(PNode)); // Allocate head node
    p->head->exp = -1; // Initialize head node exponent
    p->head->link = p->head; // Point to itself

    printf("Enter the number of terms in the expression:\n");
    int nn = 0;
    scanf_s("%d", &nn); // Read number of terms

    // Loop to read each term of the polynomial
    for (int i = 0; i < nn; i++) {
        pn = (PNode*)malloc(sizeof(PNode)); // Allocate new node
        printf("\nEnter the coefficient:\n");
        scanf_s("%d", &pn->coef); // Read coefficient
        printf("Enter the exponent:\n");
        scanf_s("%d", &pn->exp); // Read exponent

        if (pn->exp == -1) break; // Stop if exponent is -1

        pre = p->head; // Set previous node to head
        q = p->head->link; // Set current node to the first node

        // Find the correct position to insert the new node
        while (q != p->head && q->exp > pn->exp) {
            pre = q; // Move previous pointer
            q = q->link; // Move current pointer
        }

        // If the exponent already exists, combine coefficients
        if (q != p->head && q->exp == pn->exp) {
            q->coef += pn->coef; // Combine coefficients
            if (q->coef == 0) { // If coefficient becomes zero
                pre->link = q->link; // Remove the node
                free(q); // Free memory
            }
            free(pn); // Free temporary node
        }
        else { // Insert new node
            pn->link = q; // Link new node to current node
            pre->link = pn; // Link previous node to new node
        }
    }
}

// Function to output the polynomial
void Output(Polynominal p) {
    printf("expression = ");
    PNode* q; // Pointer for traversal
    int flag = 1; // Flag for formatting
    q = p.head->link; // Start from the first node
    if (!q) { // If the list is empty
        return;
    }
    // Loop to print each term of the polynomial
    while (q != p.head) {
        if (!flag && (q->coef > 0)) printf("+"); // Print '+' for positive coefficients
        flag = 0; // Reset flag after first term
        if (q->coef == 0) { // Skip if coefficient is zero
            return;
        }
        if (q->coef != 1) { // Print coefficient if not 1
            printf("%d", q->coef);
        }

        // Print exponent part
        switch (q->exp) {
        case 0: break; // No variable for exponent 0
        case 1: printf("X"); break; // Print X for exponent 1
        default: printf("X^%d", q->exp); break; // Print X raised to exponent
        }
        q = q->link; // Move to the next node
    }
    printf("\n"); // New line after output
}

// Function to add two polynomials
void Add(Polynominal* px, Polynominal* qx) {
    PNode* p, * q, * q1 = qx->head, * temp; // Pointers for traversal
    p = px->head->link; // Start from the first node of first polynomial
    q = qx->head->link; // Start from the first node of second polynomial

    // Loop through first polynomial
    while (p != px->head) {
        q1 = qx->head; // Reset q1 to the head of second polynomial
        q = q1->link; // Start from the first node of second polynomial

        // Find position to add or combine terms
        while (q != qx->head && q->exp > p->exp) {
            q1 = q; // Move previous pointer
            q = q->link; // Move current pointer
        }

        // Combine coefficients if exponents match
        if (q != qx->head && p->exp == q->exp) {
            q->coef += p->coef; // Combine coefficients
            if (q->coef == 0) { // Remove node if coefficient is zero
                q1->link = q->link; // Link previous to next node
                free(q); // Free memory
                q = q1->link; // Update current pointer
            }
        }
        else { // Insert new term
            temp = (PNode*)malloc(sizeof(PNode)); // Allocate new node
            temp->coef = p->coef; // Set coefficient
            temp->exp = p->exp; // Set exponent
            temp->link = q1->link; // Link new node to next
            q1->link = temp; // Link previous to new node
        }
        p = p->link; // Move to the next node in first polynomial
    }

    // Combine duplicate exponents in the result
    q1 = qx->head; // Reset to head
    q = q1->link; // Start from the first node
    while (q != qx->head && q->link != qx->head) {
        if (q->exp == q->link->exp) { // If exponents match
            q->coef += q->link->coef; // Combine coefficients
            PNode* duplicate = q->link; // Duplicate node to be removed
            q->link = duplicate->link; // Link to next node
            free(duplicate); // Free memory
        }
        else {
            q1 = q; // Move previous pointer
            q = q->link; // Move current pointer
        }
    }
}

// Function to multiply two polynomials
void Multiply(Polynominal* px, Polynominal* qx) {
    Polynominal qx1, qx2; // Temporary polynomials for multiplication
    PNode* q1, * q2, * q3, * q4, * pre = (PNode*)malloc(sizeof(PNode)), * q; // Pointers for nodes
    qx1.head = (PNode*)malloc(sizeof(PNode)); // Allocate head for qx1
    qx1.head->exp = -1; // Initialize exponent
    qx1.head->link = qx1.head; // Point to itself
    q1 = px->head; // Start from the first node of first polynomial
    q2 = qx->head; // Start from the first node of second polynomial

    // Loop to multiply each term in the first polynomial with the second polynomial
    while (q2->exp != -1) {
        q3 = (PNode*)malloc(sizeof(PNode)); // Allocate new node for result
        q3->coef = q1->coef * q2->coef; // Multiply coefficients
        q3->exp = q1->exp + q2->exp; // Add exponents

        // Insert the new node into the result polynomial
        if (qx1.head->link->exp == -1) {
            q3->link = qx1.head->link; // Link to head
            qx1.head->link = q3; // Set as first node
            pre = qx1.head->link; // Update previous pointer
        }
        else {
            q3->link = qx1.head; // Link to head
            pre->link = q3; // Link previous to new node
            pre = pre->link; // Update previous pointer
        }

        q2 = q2->link; // Move to the next node in second polynomial
    }
    q1 = q1->link; // Move to the next node in first polynomial

    // Loop through remaining terms in first polynomial
    while (q1->exp != -1) {
        q2 = q2->link; // Reset to start of second polynomial
        qx2.head = (PNode*)malloc(sizeof(PNode)); // Allocate head for temporary polynomial
        qx2.head->exp = -1; // Initialize exponent
        qx2.head->link = qx2.head; // Point to itself

        // Multiply current term of first polynomial with all terms of the second polynomial
        while (q2->exp != -1) {
            q4 = (PNode*)malloc(sizeof(PNode)); // Allocate new node for result
            q4->coef = q1->coef * q2->coef; // Multiply coefficients
            q4->exp = q1->exp + q2->exp; // Add exponents
            // Insert the new node into the temporary polynomial
            if (qx2.head->link->exp == -1) {
                q4->link = qx2.head->link; // Link to head
                qx2.head->link = q4; // Set as first node
                pre = qx2.head->link; // Update previous pointer
            }
            else {
                q4->link = qx2.head; // Link to head
                pre->link = q4; // Link previous to new node
                pre = pre->link; // Update previous pointer
            }
            q2 = q2->link; // Move to the next node in second polynomial
        }
        Add(&qx2, &qx1); // Add temporary result to overall result
        q1 = q1->link; // Move to the next node in first polynomial
    }
    Output(qx1); // Output the final result
}

// Main function
int main() {
    Polynominal p, q; // Declare two polynomial variables
    int x; // Variable for user choice
    printf("Enter the first expression:\n");
    Create(&p); // Create the first polynomial
    Output(p); // Output the first polynomial
    printf("\n\nEnter the second expression:\n");
    Create(&q); // Create the second polynomial
    Output(q); // Output the second polynomial
    printf("\nEnter your choice:\n1: Addition   2: Multiplication\n");
    scanf_s("%d", &x); // Read user choice
    switch (x) {
    case 0: break; // No action for choice 0
    case 1: printf("\nAddition result:\n");
        Add(&p, &q); // Add the polynomials
        Output(q); // Output the result
        break;
    case 2: printf("\nMultiplication result:\n");
        Multiply(&p, &q); // Multiply the polynomials
        break;
    default: break; // No action for invalid choice
    }
    return 0; // Exit the program
}

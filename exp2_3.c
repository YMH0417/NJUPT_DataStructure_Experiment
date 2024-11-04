#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Huffman tree node structure definition
typedef struct hfmNode {
    int weight;                // Weight of the node
    char character;            // Character associated with the node
    struct hfmNode* left;      // Pointer to the left child
    struct hfmNode* right;     // Pointer to the right child
} HfmNode;

// Create a Huffman tree node
HfmNode* CreateHfmNode(int weight, char character) {
    HfmNode* node = (HfmNode*)malloc(sizeof(HfmNode)); // Allocate memory for the node
    node->weight = weight;          // Set the weight
    node->character = character;    // Set the character
    node->left = NULL;              // Initialize left child to NULL
    node->right = NULL;             // Initialize right child to NULL
    return node;                    // Return the newly created node
}

// Define comparison function for Huffman tree nodes (for priority queue)
int Compare(const void* a, const void* b) {
    return ((HfmNode*)a)->weight - ((HfmNode*)b)->weight; // Compare weights of two nodes
}

// Create Huffman tree
HfmNode* CreateHuffmanTree(HfmNode** nodes, int n) {
    while (n > 1) { // Continue until there is only one node left
        // Sort the nodes based on weight
        qsort(nodes, n, sizeof(HfmNode*), Compare);

        // Take the two nodes with the smallest weights
        HfmNode* left = nodes[0];   // First node
        HfmNode* right = nodes[1];  // Second node

        // Create a new parent node with weight as the sum of the two nodes
        HfmNode* parent = CreateHfmNode(left->weight + right->weight, '\0');
        parent->left = left;        // Set left child to the first node
        parent->right = right;      // Set right child to the second node

        // Replace the original nodes with the new parent node
        nodes[0] = parent;          // Place parent node at the front
        for (int i = 1; i < n - 1; i++) {
            nodes[i] = nodes[i + 1]; // Shift remaining nodes left
        }
        n--; // Decrease the number of nodes
    }

    return nodes[0]; // Return the root of the Huffman tree
}

// Print Huffman codes
void PrintHuffmanCodes(HfmNode* root, char* code, int length) {
    if (!root) return; // Base case: if the node is NULL, return

    // If it's a leaf node, print the code
    if (!root->left && !root->right) {
        code[length] = '\0'; // End the string
        printf("Character %c: %s\n", root->character, code); // Print character and its code
    }

    // Traverse left subtree
    code[length] = '0'; // Append '0' for left traversal
    PrintHuffmanCodes(root->left, code, length + 1);

    // Traverse right subtree
    code[length] = '1'; // Append '1' for right traversal
    PrintHuffmanCodes(root->right, code, length + 1);
}

// Decode Huffman codes
void DecodeHuffmanCodes(HfmNode* root, const char* encoded) {
    HfmNode* current = root; // Start at the root of the Huffman tree
    for (int i = 0; encoded[i] != '\0'; i++) { // Loop through the encoded string
        if (encoded[i] == '0') {
            current = current->left; // Move to left child for '0'
        }
        else {
            current = current->right; // Move to right child for '1'
        }

        // If it's a leaf node, output the character
        if (!current->left && !current->right) {
            printf("%c", current->character); // Print the character
            current = root; // Go back to the root for the next character
        }
    }
    printf("\n"); // Print newline after decoding
}

// Main function
int main() {
    int n;
    printf("Enter the number of characters: "); // Prompt user for number of characters
    scanf_s("%d", &n); // Read the number of characters

    char* characters = (char*)malloc(n * sizeof(char)); // Allocate memory for characters
    int* weights = (int*)malloc(n * sizeof(int)); // Allocate memory for weights

    // Input characters
    printf("Enter the characters: "); // Prompt user for characters
    scanf_s("%s", characters, n + 1); // Read characters (+1 to prevent overflow)

    // Input weights
    printf("Enter the weights for each character: "); // Prompt user for weights
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &weights[i]); // Read weights
    }

    // Create Huffman tree
    HfmNode** nodes = (HfmNode**)malloc(n * sizeof(HfmNode*)); // Allocate memory for nodes
    for (int i = 0; i < n; i++) {
        nodes[i] = CreateHfmNode(weights[i], characters[i]); // Create each node
    }
    HfmNode* root = CreateHuffmanTree(nodes, n); // Create the Huffman tree

    // Print Huffman codes
    char code[100]; // Array to store codes
    printf("\nHuffman Codes:\n"); // Print header
    PrintHuffmanCodes(root, code, 0); // Print the Huffman codes

    // Input encoded string and decode
    char encoded[100]; // Array for encoded input
    printf("\nEnter the binary string to decode: "); // Prompt for encoded string
    scanf_s("%s", encoded, sizeof(encoded)); // Read the encoded string
    printf("Decoded result: "); // Print header for decoded result
    DecodeHuffmanCodes(root, encoded); // Decode the encoded string

    return 0; // Exit program
}

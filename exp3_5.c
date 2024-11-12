#include <stdio.h>
#include <string.h>

// Variables to store the number of cities and bus routes
int n, m;

// Adjacency matrix to represent connections between cities
int s[50][50];

// Dijkstra's algorithm function to find the minimum number of transfers
int Dijkstra(int start, int end)
{
    int i = 0, j = 0, k = 0; // Loop counters and index variable
    int min; // Minimum distance
    int distance[100]; // Distance array to store distances from the start node
    int visited[100]; // Array to mark visited nodes

    // Initialize the distance and visited arrays with zeros
    memset(distance, 0, sizeof(distance));
    memset(visited, 0, sizeof(visited));

    // Set initial distances from start node; 1 means reachable, 9999 means unreachable
    for (i = 0; i < n; i++)
        distance[i] = s[start][i];

    // Loop to visit each node in the graph
    for (i = 1; i <= n - 1; i++)
    {
        min = 99999; // Initialize minimum to a large value
        for (j = 0; j < n; j++) {
            // Find the node with the minimum distance that has not been visited
            if (distance[j] < min && !visited[j])
            {
                k = j; // Update k to the current node index
                min = distance[j]; // Update minimum distance
            }
        }
        visited[k] = 1; // Mark the selected node as visited

        // Update distances for adjacent nodes
        for (j = 0; j < n; j++)
            // Find a shorter path if available
            if (distance[j] > distance[k] + s[k][j])
                distance[j] = distance[k] + s[k][j];
    }

    // Number of transfers is the number of visited stations - 1
    return distance[end] - 1;
}

int main()
{
    int i, j, a, b, ans; // Variables for loops and input/output
    memset(s, 0, sizeof(s)); // Initialize the adjacency matrix with zeros

    // Get the number of cities from the user
    printf("Enter the number of cities: ");
    scanf_s("%d", &n);

    // Initialize the adjacency matrix with distances
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (i == j)
                s[i][j] = 0; // Distance from a city to itself is 0
            else
                s[i][j] = 99999; // Unreachable cities have a large distance

    // Get the number of bus routes from the user
    printf("Enter the number of bus routes: ");
    scanf_s("%d", &m);

    // Get pairs of connected stations
    printf("Enter the two reachable stations:\n");
    for (i = 0; i < m; i++)
    {
        scanf_s("%d%d", &a, &b); // Read the two cities connected by a bus route
        s[a][b] = 1; // Mark the route as reachable (distance = 1)
    }

    // Get the start and end cities from the user
    printf("Enter the start and end points:\n");
    scanf_s("%d%d", &a, &b);

    // Calculate the minimum number of transfers needed
    ans = Dijkstra(a, b);

    // Output the result based on the number of transfers found
    if (ans == 99998)
        printf("Cannot reach destination.\n"); // If unreachable, print a message
    else if (ans > 0)
        printf("Minimum number of transfers: %d\n", ans); // Print the minimum number of transfers
    else if (ans == 0)
        printf("No transfer needed.\n"); // If no transfers are needed, print a message

    return 0; // End of program
}

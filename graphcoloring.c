#include <stdio.h>
#include <stdbool.h>

void greedyGraphColoring(int graph[][4], int numVertices) {
    int color[numVertices];  // Array to store the color assigned to each vertex
    const char *colorNames[] = {"R", "G", "B"}; // Array to hold color names

    // Assign the first color to the first vertex
    color[0] = 0;

    // Initialize all other vertices as unassigned
    for (int i = 1; i < numVertices; i++) {
        color[i] = -1;  // -1 indicates that no color is assigned yet
    }

    // Array to keep track of the colors that are unavailable for a vertex
    bool available[3];
    for (int i = 0; i < 3; i++) {
        available[i] = true;  // Initially, all colors are available
    }

    // Assign colors to the remaining vertices
    for (int u = 1; u < numVertices; u++) {
        // Mark the colors of adjacent vertices as unavailable
        for (int i = 0; i < numVertices; i++) {
            if (graph[u][i] == 1 && color[i] != -1) {
                available[color[i]] = false;
            }
        }

        // Find the first available color
        int cr;
        for (cr = 0; cr < 3; cr++) {  // Limit to 3 colors
            if (available[cr]) {
                break;
            }
        }

        color[u] = cr;  // Assign the found color to vertex u

        // Reset the values back to true for the next iteration
        for (int i = 0; i < numVertices; i++) {
            if (graph[u][i] == 1 && color[i] != -1) {
                available[color[i]] = true;
            }
        }
    }

    // Print the result
    printf("The color assigned to each vertex is as follows:\n");
    for (int i = 0; i < numVertices; i++) {
        printf("Vertex %d ---> Color %s\n", i, colorNames[color[i] % 3]);
    }

    // Ensure all colors are used at least once
    bool colorUsed[3] = {false, false, false};
    for (int i = 0; i < numVertices; i++) {
        colorUsed[color[i]] = true;
    }

    printf("\nSummary of colors used:\n");
    for (int i = 0; i < 3; i++) {
        printf("Color %s used: %s\n", colorNames[i], colorUsed[i] ? "Yes" : "No");
    }
}

// Driver code
int main() {
    // Adjacency matrix representation of the graph
    int graph[4][4] = {
        {0, 1, 1, 1},
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {1, 1, 1, 0}
    };

    int numVertices = 4;

    // Solve the graph coloring problem using the Greedy algorithm
    greedyGraphColoring(graph, numVertices);

    return 0;
}

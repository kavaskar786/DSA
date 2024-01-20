#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent an edge in the graph
typedef struct {
    int source;
    int destination;
    int weight;
} Edge;

// Structure to represent a node in the graph
typedef struct {
    int parent;
    int rank;
} Subset;

// Function declarations
void generateRandomGraph(Edge *edges, int numEdges, int numVertices);
void printMST(Edge *mstEdges, int numVertices);
void primMST(Edge *edges, int numEdges, int numVertices);
void kruskalMST(Edge *edges, int numEdges, int numVertices);
int find(Subset *subsets, int i);
void unionSets(Subset *subsets, int x, int y);

// Function to generate random input for the graph
void generateRandomGraph(Edge *edges, int numEdges, int numVertices) {
    for (int i = 0; i < numEdges; ++i) {
        edges[i].source = rand() % numVertices;
        edges[i].destination = rand() % numVertices;
        edges[i].weight = rand() % 100 + 1; // Random weight between 1 and 100
    }
}

// Function to print the edges in the MST
void printMST(Edge *mstEdges, int numVertices) {
    printf("Edges in Minimum Spanning Tree:\n");
    for (int i = 0; i < numVertices - 1; ++i) {
        printf("(%d, %d) - %d\n", mstEdges[i].source, mstEdges[i].destination, mstEdges[i].weight);
    }
}

// Prim's algorithm to find Minimum Spanning Tree
void primMST(Edge *edges, int numEdges, int numVertices) {
    Edge *mstEdges = (Edge *)malloc((numVertices - 1) * sizeof(Edge));
    int *key = (int *)malloc(numVertices * sizeof(int));
    bool *inMST = (bool *)malloc(numVertices * sizeof(bool));

    for (int i = 0; i < numVertices; ++i) {
        key[i] = INT_MAX;
        inMST[i] = false;
    }

    key[0] = 0;

    for (int count = 0; count < numVertices - 1; ++count) {
        int u = -1;

        for (int v = 0; v < numVertices; ++v) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        inMST[u] = true;

        for (int v = 0; v < numVertices; ++v) {
            if (!inMST[v] && edges[u * numVertices + v].weight < key[v]) {
                key[v] = edges[u * numVertices + v].weight;
                mstEdges[count] = edges[u * numVertices + v];
            }
        }
    }

    printMST(mstEdges, numVertices);

    free(mstEdges);
    free(key);
    free(inMST);
}

// Kruskal's algorithm to find Minimum Spanning Tree
void kruskalMST(Edge *edges, int numEdges, int numVertices) {
    Edge *mstEdges = (Edge *)malloc((numVertices - 1) * sizeof(Edge));
    Subset *subsets = (Subset *)malloc(numVertices * sizeof(Subset));

    // Initialize subsets
    for (int i = 0; i < numVertices; ++i) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    // Sort edges in ascending order of weight
    for (int i = 0; i < numEdges - 1; ++i) {
        for (int j = 0; j < numEdges - i - 1; ++j) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    int count = 0;
    int i = 0;

    // Construct MST
    while (count < numVertices - 1 && i < numEdges) {
        Edge nextEdge = edges[i++];

        int x = nextEdge.source;
        int y = nextEdge.destination;

        int xRoot = find(subsets, x);
        int yRoot = find(subsets, y);

        if (xRoot != yRoot) {
            mstEdges[count++] = nextEdge;
            unionSets(subsets, xRoot, yRoot);
        }
    }

    printMST(mstEdges, numVertices);

    free(mstEdges);
    free(subsets);
}

// Helper function to find the subset of a given element
int find(Subset *subsets, int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Helper function to perform union of two sets
void unionSets(Subset *subsets, int x, int y) {
    int xRoot = find(subsets, x);
    int yRoot = find(subsets, y);

    if (subsets[xRoot].rank < subsets[yRoot].rank) {
        subsets[xRoot].parent = yRoot;
    } else if (subsets[xRoot].rank > subsets[yRoot].rank) {
        subsets[yRoot].parent = xRoot;
    } else {
        subsets[yRoot].parent = xRoot;
        subsets[xRoot].rank++;
    }
}

int main() {
    int numVertices, numEdges;

    // Get input from the user
    printf("Enter the number of vertices in the hotel: ");
    scanf("%d", &numVertices);

    // Ensure the number of vertices is at least 2
    if (numVertices < 2) {
        printf("Invalid number of vertices. The hotel must have at least 2 rooms.\n");
        return 1;
    }

    numEdges = numVertices * (numVertices - 1) / 2; // Complete graph

    Edge *edges = (Edge *)malloc(numEdges * sizeof(Edge));

    // Generate random input for the graph
    generateRandomGraph(edges, numEdges, numVertices);

    int choice;

    do {
        // Display menu
        printf("\nMenu:\n");
        printf("1. Find Minimum Spanning Tree using Prim's Algorithm\n");
        printf("2. Find Minimum Spanning Tree using Kruskal's Algorithm\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                primMST(edges, numEdges, numVertices);
                break;
            case 2:
                kruskalMST(edges, numEdges, numVertices);
                break;
            case 3:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 3);

    free(edges);

    return 0;
}

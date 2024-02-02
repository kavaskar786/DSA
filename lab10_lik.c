#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define MAX_LOCATIONS 10

// Structure to represent an edge in the graph
typedef struct {
    int src, dest, weight;
} Edge;

// Structure to represent a graph
typedef struct {
    int V, E;
    Edge* edges;
} Graph;

// Function to create a graph with random edge weights
Graph* createRandomGraph(int numLocations);

// Function to print the edges of the MST
void printMSTEdges(Edge* mstEdges, int numLocations);

// Function to find the vertex with the minimum key value
int findMinKey(int* key, bool* mstSet, int numLocations);

// Function to find the MST using Prim's algorithm
void primMST(Graph* graph);

// Function to compare edges for sorting in Kruskal's algorithm
int compareEdges(const void* a, const void* b);

// Function to find the root of the subset containing a given element
int find(int parent[], int i);

// Function to perform union of two subsets
void unionSets(int parent[], int rank[], int x, int y);

// Function to find the MST using Kruskal's algorithm
void kruskalMST(Graph* graph);

int main() {
    srand(time(NULL));

    int choice, numLocations;
    printf("Enter the number of restaurant locations: ");
    scanf("%d", &numLocations);

    if (numLocations <= 0 || numLocations > MAX_LOCATIONS) {
        printf("Invalid number of locations. Exiting...\n");
        return 1;
    }

    Graph* graph = createRandomGraph(numLocations);

    do {
        printf("\nMenu:\n");
        printf("1. Find MST using Prim's Algorithm\n");
        printf("2. Find MST using Kruskal's Algorithm\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                primMST(graph);
                break;
            case 2:
                kruskalMST(graph);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 3);

    free(graph->edges);
    free(graph);

    return 0;
}

Graph* createRandomGraph(int numLocations) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = numLocations;
    graph->E = numLocations * (numLocations - 1) / 2; // Complete graph
    graph->edges = (Edge*)malloc(graph->E * sizeof(Edge));

    int edgeCount = 0;

    for (int i = 0; i < numLocations; ++i) {
        for (int j = i + 1; j < numLocations; ++j) {
            graph->edges[edgeCount].src = i;
            graph->edges[edgeCount].dest = j;
            graph->edges[edgeCount].weight = rand() % 20 + 1; // Random weight between 1 and 20
            ++edgeCount;
        }
    }

    return graph;
}

void printMSTEdges(Edge* mstEdges, int numLocations) {
    printf("\nMinimum Spanning Tree Edges:\n");
    for (int i = 0; i < numLocations - 1; ++i) {
        printf("Edge %d - %d : Weight %d\n", mstEdges[i].src, mstEdges[i].dest, mstEdges[i].weight);
    }
}

int findMinKey(int* key, bool* mstSet, int numLocations) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < numLocations; ++v) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

void primMST(Graph* graph) {
    int* parent = (int*)malloc(graph->V * sizeof(int));
    int* key = (int*)malloc(graph->V * sizeof(int));
    bool* mstSet = (bool*)malloc(graph->V * sizeof(bool));

    for (int i = 0; i < graph->V; ++i) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < graph->V - 1; ++count) {
        int u = findMinKey(key, mstSet, graph->V);
        mstSet[u] = true;

        for (int v = 0; v < graph->V; ++v) {
            if (graph->edges[u * graph->V + v].weight && !mstSet[v] && graph->edges[u * graph->V + v].weight < key[v]) {
                parent[v] = u;
                key[v] = graph->edges[u * graph->V + v].weight;
            }
        }
    }

    Edge* mstEdges = (Edge*)malloc((graph->V - 1) * sizeof(Edge));
    for (int i = 1; i < graph->V; ++i) {
        mstEdges[i - 1] = graph->edges[i * graph->V + parent[i]];
    }

    printMSTEdges(mstEdges, graph->V);

    free(parent);
    free(key);
    free(mstSet);
    free(mstEdges);
}

int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void unionSets(int parent[], int rank[], int x, int y) {
    int xRoot = find(parent, x);
    int yRoot = find(parent, y);

    if (rank[xRoot] < rank[yRoot])
        parent[xRoot] = yRoot;
    else if (rank[xRoot] > rank[yRoot])
        parent[yRoot] = xRoot;
    else {
        parent[yRoot] = xRoot;
        rank[xRoot]++;
    }
}

void kruskalMST(Graph* graph) {
    qsort(graph->edges, graph->E, sizeof(Edge), compareEdges);

    Edge* mstEdges = (Edge*)malloc((graph->V - 1) * sizeof(Edge));

    int* parent = (int*)malloc(graph->V * sizeof(int));
    int* rank = (int*)malloc(graph->V * sizeof(int));

    for (int i = 0; i < graph->V; ++i) {
        parent[i] = -1;
        rank[i] = 0;
    }

    int mstEdgeCount = 0;
    int i = 0;

    while (mstEdgeCount < graph->V - 1 && i < graph->E) {
        Edge nextEdge = graph->edges[i++];

        int x = find(parent, nextEdge.src);
        int y = find(parent, nextEdge.dest);

        if (x != y) {
            mstEdges[mstEdgeCount++] = nextEdge;
            unionSets(parent, rank, x, y);
        }
    }

    printMSTEdges(mstEdges, graph->V);

    free(mstEdges);
    free(parent);
    free(rank);
}

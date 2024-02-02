#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maximum number of hotels and infinity value
#define MAX_HOTELS 100
#define INF 999999

// Define structure for a hotel
typedef struct {
    int x, y;      // Coordinates of the hotel
    char name[50];  // Name of the hotel
} Hotel;

// Define structure for an edge between two hotels
typedef struct {
    int src, dest, weight;  // Source hotel, destination hotel, and distance between them
} Edge;

// Function to display the main menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Display Hotels\n");
    printf("2. Display Distances between Hotels\n");
    printf("3. Find Minimum Spanning Tree using Prim's Algorithm\n");
    printf("4. Find Minimum Spanning Tree using Kruskal's Algorithm\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

// Function to read hotel information from a file
void readHotelsFromFile(char *filename, Hotel hotels[], int *numHotels) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    *numHotels = 0;
    while (fscanf(file, "%s %d %d", hotels[*numHotels].name, &hotels[*numHotels].x, &hotels[*numHotels].y) != EOF) {
        (*numHotels)++;
    }

    fclose(file);
}

// Function to read edge information from a file
void readEdgesFromFile(char *filename, Edge edges[], int *numEdges) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    *numEdges = 0;
    while (fscanf(file, "%d %d %d", &edges[*numEdges].src, &edges[*numEdges].dest, &edges[*numEdges].weight) != EOF) {
        (*numEdges)++;
    }

    fclose(file);
}

// Function to display information about hotels
void displayHotels(Hotel hotels[], int numHotels) {
    printf("\nList of Hotels:\n");
    for (int i = 0; i < numHotels; i++) {
        printf("%s - Coordinates: (%d, %d)\n", hotels[i].name, hotels[i].x, hotels[i].y);
    }
}

// Function to display information about edges (distances) between hotels
void displayEdges(Hotel hotels[], Edge edges[], int numEdges) {
    printf("\nDistances between Hotels:\n");
    for (int i = 0; i < numEdges; i++) {
        printf("%s to %s: %d\n", hotels[edges[i].src].name, hotels[edges[i].dest].name, edges[i].weight);
    }
}

// Function to find the parent of a set in Union-Find data structure
int findParent(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return findParent(parent, parent[i]);
}

// Function to perform union operation in Union-Find data structure
void unionSets(int parent[], int x, int y) {
    int rootX = findParent(parent, x);
    int rootY = findParent(parent, y);
    parent[rootX] = rootY;
}

// Function to find Minimum Spanning Tree using Prim's Algorithm
void primMST(Hotel hotels[], Edge edges[], int numHotels, int numEdges) {
    int parent[MAX_HOTELS];
    int key[MAX_HOTELS];
    int inMST[MAX_HOTELS];

    // Initialize arrays
    for (int i = 0; i < numHotels; i++) {
        key[i] = INF;
        inMST[i] = 0;
        parent[i] = -1;
    }

    // Start with the first hotel
    key[0] = 0;

    // Iterate over all hotels
    for (int count = 0; count < numHotels - 1; count++) {
        int u = -1;

        // Find the hotel with the minimum key value
        for (int v = 0; v < numHotels; v++) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        // Include the selected hotel in the MST
        inMST[u] = 1;

        // Update key values of the adjacent hotels
        for (int v = 0; v < numHotels; v++) {
            if (edges[v].src == u && !inMST[edges[v].dest] && edges[v].weight < key[edges[v].dest]) {
                parent[edges[v].dest] = u;
                key[edges[v].dest] = edges[v].weight;
            }
        }
    }

    // Display the Minimum Spanning Tree
    printf("\nMinimum Spanning Tree using Prim's Algorithm:\n");
    for (int i = 1; i < numHotels; i++) {
        printf("%s to %s: %d\n", hotels[parent[i]].name, hotels[i].name, key[i]);
    }
}

// Function to compare edges for sorting in Kruskal's Algorithm
int compareEdges(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

// Function to find Minimum Spanning Tree using Kruskal's Algorithm
void kruskalMST(Hotel hotels[], Edge edges[], int numHotels, int numEdges) {
    // Sort edges based on weight
    qsort(edges, numEdges, sizeof(Edge), compareEdges);

    // Initialize Union-Find data structure
    int parent[MAX_HOTELS];
    for (int i = 0; i < numHotels; i++) {
        parent[i] = -1;
    }

    // Display the Minimum Spanning Tree
    printf("\nMinimum Spanning Tree using Kruskal's Algorithm:\n");
    for (int i = 0; i < numEdges; i++) {
        int rootX = findParent(parent, edges[i].src);
        int rootY = findParent(parent, edges[i].dest);

        // Include the edge in the MST if it doesn't create a cycle
        if (rootX != rootY) {
            printf("%s to %s: %d\n", hotels[edges[i].src].name, hotels[edges[i].dest].name, edges[i].weight);
            unionSets(parent, rootX, rootY);
        }
    }
}

// Main function
int main() {
    Hotel hotels[MAX_HOTELS];
    Edge edges[MAX_HOTELS * (MAX_HOTELS - 1) / 2];  // Maximum edges in a complete graph

    int numHotels, numEdges, choice;

    // Read hotels and edges from files
    readHotelsFromFile("hotels.txt", hotels, &numHotels);
    readEdgesFromFile("distances.txt", edges, &numEdges);

    // Menu-driven program loop
    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayHotels(hotels, numHotels);
                break;
            case 2:
                displayEdges(hotels, edges, numEdges);
                break;
            case 3:
                primMST(hotels, edges, numHotels, numEdges);
                break;
            case 4:
                kruskalMST(hotels, edges, numHotels, numEdges);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 5);

    return 0;
}

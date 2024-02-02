#include <stdio.h>
#include <stdlib.h>

// Structure to represent a room
typedef struct Room {
    int roomNumber;
    char guestName[50];
    int bedsAvailable;
    struct Room* next;
} Room;

// Structure to represent a node in a linked list
typedef struct Node {
    Room* room;
    struct Node* next;
} Node;

// Structure to represent a node in a queue
typedef struct QueueNode {
    Node* data;
    struct QueueNode* next;
} QueueNode;

// Structure to represent a queue
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Function to create a new room
Room* createRoom(int number, const char* name, int beds) {
    Room* newRoom = (Room*)malloc(sizeof(Room));
    newRoom->roomNumber = number;
    snprintf(newRoom->guestName, sizeof(newRoom->guestName), "%s", name);
    newRoom->bedsAvailable = beds;
    newRoom->next = NULL;
    return newRoom;
}

// Function to create a new node
Node* createNode(Room* room) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->room = room;
    newNode->next = NULL;
    return newNode;
}

// Function to add a room to the list
void addRoom(Room** head, int number, const char* name, int beds) {
    Room* newRoom = createRoom(number, name, beds);
    newRoom->next = *head;
    *head = newRoom;
}

// Function to enqueue a node to the queue
void enqueue(Queue* queue, Node* data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to dequeue a node from the queue
Node* dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }

    Node* data = queue->front->data;
    QueueNode* temp = queue->front;

    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return data;
}

// Function to display tree structure
void displayTreeStructure(Node* root, int level, int isLast) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < level - 1; i++) {
        printf(isLast ? "    " : "|   ");
    }

    if (level > 0) {
        printf(isLast ? "L-- " : "|-- ");
    }

    printf("%d - %s\n", root->room->roomNumber, root->room->guestName);

    displayTreeStructure(root->next, level + 1, 0);
    displayTreeStructure(root->next, level + 1, 1);
}

// Function to display BFS tree with counts
void displayBFSWithCounts(Node* bfsTree, int vertexCount, int edgeCount) {
    printf("\nBFS Tree\n");
    displayTreeStructure(bfsTree, 0, 1);
    printf("Vertex Count: %d\n", vertexCount);
    printf("Edge Count: %d\n", edgeCount);
}

// Function to display DFS tree with counts
void displayDFSWithCounts(Node* dfsTree, int vertexCount, int edgeCount) {
    printf("\nDFS Tree\n");
    displayTreeStructure(dfsTree, 0, 1);
    printf("Vertex Count: %d\n", vertexCount);
    printf("Edge Count: %d\n", edgeCount);
}

// Function to perform Breadth-First Search
void BFS(Room** rooms, int startRoom, Node** bfsTree, int* vertexCount, int* edgeCount) {
    Queue queue = { .front = NULL, .rear = NULL };
    int visited[100] = { 0 };

    Node* startNode = NULL;
    Room* currentRoom = *rooms;

    // Find the starting room
    while (currentRoom != NULL && currentRoom->roomNumber != startRoom) {
        currentRoom = currentRoom->next;
    }

    if (currentRoom != NULL) {
        startNode = createNode(currentRoom);
        visited[startRoom] = 1;
        enqueue(&queue, startNode);
    } else {
        printf("Room not found.\n");
        return;
    }

    *vertexCount = 0;
    *edgeCount = 0;

    while (queue.front != NULL) {
        Node* currentNode = dequeue(&queue);

        Room* adjRoom = *rooms;
        while (adjRoom != NULL) {
            if (adjRoom->roomNumber != currentNode->room->roomNumber &&
                adjRoom->bedsAvailable >= 1 && !visited[adjRoom->roomNumber]) {
                Node* adjNode = createNode(adjRoom);
                visited[adjRoom->roomNumber] = 1;
                enqueue(&queue, adjNode);

                if (*bfsTree == NULL) {
                    *bfsTree = adjNode;
                } else {
                    Node* temp = *bfsTree;
                    while (temp->next != NULL) {
                        temp = temp->next;
                    }
                    temp->next = adjNode;
                    *edgeCount += 1;
                }
                *vertexCount += 1;
            }
            adjRoom = adjRoom->next;
        }
    }
}

// Function to perform Depth-First Search
void DFSUtil(Room** rooms, int startRoom, int visited[100], Node** dfsTree, int* vertexCount, int* edgeCount) {
    visited[startRoom] = 1;

    Node* currentNode = NULL;
    Room* currentRoom = *rooms;

    // Find the starting room
    while (currentRoom != NULL && currentRoom->roomNumber != startRoom) {
        currentRoom = currentRoom->next;
    }

    if (currentRoom != NULL) {
        currentNode = createNode(currentRoom);
    } else {
        printf("Room not found.\n");
        return;
    }

    *vertexCount += 1;

    // Add to DFS tree
    if (*dfsTree == NULL) {
        *dfsTree = currentNode;
    } else {
        Node* temp = *dfsTree;
        while (temp->next != NULL) {
            temp = temp->next;
            *edgeCount += 1;
        }
        temp->next = currentNode;
    }

    Room* adjRoom = *rooms;
    while (adjRoom != NULL) {
        if (adjRoom->roomNumber != startRoom && adjRoom->bedsAvailable >= 1 && !visited[adjRoom->roomNumber]) {
            DFSUtil(rooms, adjRoom->roomNumber, visited, dfsTree, vertexCount, edgeCount);
        }
        adjRoom = adjRoom->next;
    }
}

// Function to perform Depth-First Search
void DFS(Room** rooms, int startRoom, Node** dfsTree, int* vertexCount, int* edgeCount) {
    int visited[100] = { 0 };
    *vertexCount = 0;
    *edgeCount = 0;
    DFSUtil(rooms, startRoom, visited, dfsTree, vertexCount, edgeCount);
}

// Function to display room details
void displayRooms(Room* rooms) {
    printf("\nRoom Details\n");
    printf("--------------------------------------------------------\n");
    printf("| Room Number  | Guest Name          | Beds Available  |\n");
    printf("--------------------------------------------------------\n");

    while (rooms != NULL) {
        printf("| %-14d| %-20s| %-16d|\n", rooms->roomNumber, rooms->guestName, rooms->bedsAvailable);
        rooms = rooms->next;
    }

    printf("--------------------------------------------------------\n");
}

int main() {
    Room* rooms = NULL;

    int choice;
    int startRoom;

    do {
        printf("\nHotel Management System\n");
        printf("1. Add a Room\n");
        printf("2. Display Room Details\n");
        printf("3. Perform Breadth-First Search\n");
        printf("4. Perform Depth-First Search\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int roomNumber, beds;
                char guestName[50];

                printf("Enter Room Number: ");
                scanf("%d", &roomNumber);

                printf("Enter Guest Name: ");
                scanf("%s", guestName);

                printf("Enter Beds Available: ");
                scanf("%d", &beds);

                addRoom(&rooms, roomNumber, guestName, beds);
                printf("Room added successfully!\n");
                break;
            }

            case 2:
                displayRooms(rooms);
                break;

            case 3:
                printf("Enter the starting room number: ");
                scanf("%d", &startRoom);
                Node* bfsTree = NULL;
                int bfsVertexCount, bfsEdgeCount;
                BFS(&rooms, startRoom, &bfsTree, &bfsVertexCount, &bfsEdgeCount);
                displayBFSWithCounts(bfsTree, bfsVertexCount, bfsEdgeCount);
                break;

            case 4:
                printf("Enter the starting room number: ");
                scanf("%d", &startRoom);
                Node* dfsTree = NULL;
                int dfsVertexCount, dfsEdgeCount;
                DFS(&rooms, startRoom, &dfsTree, &dfsVertexCount, &dfsEdgeCount);
                displayDFSWithCounts(dfsTree, dfsVertexCount, dfsEdgeCount);
                break;

            case 5:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    // Free allocated memory before exiting
    while (rooms != NULL) {
        Room* temp = rooms;
        rooms = rooms->next;
        free(temp);
    }

    return 0;
}

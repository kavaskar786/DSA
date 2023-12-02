#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for the linked list
typedef struct Node {
    int guestId;
    struct Node* next;
} Node;

// Queue structure
typedef struct {
    Node* front;
    Node* rear;
} Queue;

// Priority Queue structure
typedef struct {
    Node* front;
    Node* rear;
} PriorityQueue;

// Circular Queue structure
typedef struct {
    Node* front;
    Node* rear;
} CircularQueue;

// Function to initialize an empty queue
void initializeQueue(Queue* queue) {
    queue->front = queue->rear = NULL;
}

// Function to initialize an empty priority queue
void initializePriorityQueue(PriorityQueue* priorityQueue) {
    priorityQueue->front = priorityQueue->rear = NULL;
}

// Function to initialize an empty circular queue
void initializeCircularQueue(CircularQueue* circularQueue) {
    circularQueue->front = circularQueue->rear = NULL;
}

// Function to check if the queue is empty
bool isQueueEmpty(Queue* queue) {
    return (queue->front == NULL);
}

// Function to check if the priority queue is empty
bool isPriorityQueueEmpty(PriorityQueue* priorityQueue) {
    return (priorityQueue->front == NULL);
}

// Function to check if the circular queue is empty
bool isCircularQueueEmpty(CircularQueue* circularQueue) {
    return (circularQueue->front == NULL);
}

// Function to enqueue a guest in the normal queue
void enqueue(Queue* queue, int guestId) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->guestId = guestId;
    newNode->next = NULL;

    if (isQueueEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    printf("Guest %d has been successfully checked in.\n", guestId);
}

// Function to enqueue a guest in the priority queue based on guest priority
void enqueuePriority(PriorityQueue* priorityQueue, int guestId) {
    // Implementation of priority queue logic based on the guest's priority
    // (e.g., high priority guests are placed at the front)
    // For simplicity, let's assume guests with even IDs have high priority.

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->guestId = guestId;
    newNode->next = NULL;

    if (isPriorityQueueEmpty(priorityQueue) || guestId % 2 == 0) {
        // High priority guest or priority queue is empty
        newNode->next = priorityQueue->front;
        priorityQueue->front = newNode;

        if (priorityQueue->rear == NULL) {
            priorityQueue->rear = newNode;
        }
    } else {
        // Low priority guest
        priorityQueue->rear->next = newNode;
        priorityQueue->rear = newNode;
    }

    printf("Guest %d has been successfully checked in with priority.\n", guestId);
}

// Function to enqueue a guest in the circular queue
void enqueueCircular(CircularQueue* circularQueue, int guestId) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->guestId = guestId;
    newNode->next = NULL;

    if (isCircularQueueEmpty(circularQueue)) {
        circularQueue->front = circularQueue->rear = newNode;
        newNode->next = circularQueue->front; // Make it circular
    } else {
        newNode->next = circularQueue->front;
        circularQueue->rear->next = newNode;
        circularQueue->rear = newNode;
    }

    printf("Guest %d has been successfully checked in a circular queue.\n", guestId);
}

// Function to dequeue a guest from the normal queue
void dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty. No guests to check out.\n");
    } else {
        Node* temp = queue->front;
        queue->front = temp->next;

        printf("Guest %d has been checked out.\n", temp->guestId);

        free(temp);
    }
}

// Function to dequeue a guest from the priority queue
void dequeuePriority(PriorityQueue* priorityQueue) {
    if (isPriorityQueueEmpty(priorityQueue)) {
        printf("Priority Queue is empty. No guests to check out.\n");
    } else {
        Node* temp = priorityQueue->front;
        priorityQueue->front = temp->next;

        printf("Guest %d has been checked out from the Priority Queue.\n", temp->guestId);

        free(temp);
    }
}

// Function to dequeue a guest from the circular queue
void dequeueCircular(CircularQueue* circularQueue) {
    if (isCircularQueueEmpty(circularQueue)) {
        printf("Circular Queue is empty. No guests to check out.\n");
    } else {
        Node* temp = circularQueue->front;
        circularQueue->front = temp->next;

        printf("Guest %d has been checked out from the Circular Queue.\n", temp->guestId);

        free(temp);
    }
}

// Function to display the normal queue
void displayQueue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty.\n");
    } else {
        printf("Current Guest Queue:\n");
        Node* current = queue->front;
        while (current != NULL) {
            printf("Guest %d\n", current->guestId);
            current = current->next;
        }
    }
}

// Function to display the priority queue
void displayPriorityQueue(PriorityQueue* priorityQueue) {
    if (isPriorityQueueEmpty(priorityQueue)) {
        printf("Priority Queue is empty.\n");
    } else {
        printf("Current Priority Guest Queue:\n");
        Node* current = priorityQueue->front;
        while (current != NULL) {
            printf("Guest %d\n", current->guestId);
            current = current->next;
        }
    }
}

// Function to display the circular queue
void displayCircularQueue(CircularQueue* circularQueue) {
    if (isCircularQueueEmpty(circularQueue)) {
        printf("Circular Queue is empty.\n");
    } else {
        printf("Current Circular Guest Queue:\n");
        Node* current = circularQueue->front;
        do {
            printf("Guest %d\n", current->guestId);
            current = current->next;
        } while (current != circularQueue->front);
    }
}

int main() {
    // Initialize the queues
    Queue guestQueue;
    initializeQueue(&guestQueue);

    PriorityQueue priorityQueue;
    initializePriorityQueue(&priorityQueue);

    CircularQueue circularQueue;
    initializeCircularQueue(&circularQueue);

    int choice, guestId, queueType;

    do {
        // Display menu
        printf("\nHotel Management System\n");
        printf("1. Check-in a guest\n");
        printf("2. Check-out a guest\n");
        printf("3. Display guest queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Check-in a guest
                printf("Enter guest ID: ");
                scanf("%d", &guestId);

                // Ask for the type of queue to operate on
                printf("Select the type of queue to check in:\n");
                printf("1. Normal Queue\n");
                printf("2. Priority Queue\n");
                printf("3. Circular Queue\n");
                printf("Enter your choice: ");
                scanf("%d", &queueType);

                switch (queueType) {
                    case 1:
                        enqueue(&guestQueue, guestId);
                        break;
                    case 2:
                        enqueuePriority(&priorityQueue, guestId);
                        break;
                    case 3:
                        enqueueCircular(&circularQueue, guestId);
                        break;
                    default:
                        printf("Invalid queue type. Please enter a valid option.\n");
                }
                break;
            case 2:
                // Check-out a guest
                // Ask for the type of queue to operate on
                printf("Select the type of queue to check out from:\n");
                printf("1. Normal Queue\n");
                printf("2. Priority Queue\n");
                printf("3. Circular Queue\n");
                printf("Enter your choice: ");
                scanf("%d", &queueType);

                switch (queueType) {
                    case 1:
                        dequeue(&guestQueue);
                        break;
                    case 2:
                        dequeuePriority(&priorityQueue);
                        break;
                    case 3:
                        dequeueCircular(&circularQueue);
                        break;
                    default:
                        printf("Invalid queue type. Please enter a valid option.\n");
                }
                break;
            case 3:
                // Display guest queue
                // Ask for the type of queue to operate on
                printf("Select the type of queue to display:\n");
                printf("1. Normal Queue\n");
                printf("2. Priority Queue\n");
                printf("3. Circular Queue\n");
                printf("Enter your choice: ");
                scanf("%d", &queueType);

                switch (queueType) {
                    case 1:
                        displayQueue(&guestQueue);
                        break;
                    case 2:
                        displayPriorityQueue(&priorityQueue);
                        break;
                    case 3:
                        displayCircularQueue(&circularQueue);
                        break;
                    default:
                        printf("Invalid queue type. Please enter a valid option.\n");
                }
                break;
            case 4:
                // Exit
                printf("Exiting the program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 4);

    return 0;
}

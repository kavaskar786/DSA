#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Structure to represent a hotel room
typedef struct Room {
    int roomNumber;
    char guestName[50];
    struct Room *left, *right;
} Room;

// Function prototypes
Room* createRoom(int roomNumber, const char* guestName);
Room* insertRoomLevelOrder(Room* root, int roomNumber, const char* guestName);
void printInOrder(Room* root);
void printPreOrder(Room* root);
void printPostOrder(Room* root);
void displayTreeStructure(Room* root, int level);
void displayMenu();
void saveRoomsToFile(Room* root, const char* fileName);
Room* loadRoomsFromFile(const char* fileName);
void freeTree(Room* root);

int main() {
    Room* hotelRooms = NULL;
    char fileName[] = "hotel_data.txt";

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int roomNumber;
                char guestName[50];
                printf("Enter room number: ");
                scanf("%d", &roomNumber);
                printf("Enter guest name: ");
                scanf("%s", guestName);
                hotelRooms = insertRoomLevelOrder(hotelRooms, roomNumber, guestName);
                printf("Room added successfully.\n");
                break;
            }
            case 2:
                printf("In-order Traversal:\n");
                printInOrder(hotelRooms);
                printf("\n");
                break;
            case 3:
                printf("Pre-order Traversal:\n");
                printPreOrder(hotelRooms);
                printf("\n");
                break;
            case 4:
                printf("Post-order Traversal:\n");
                printPostOrder(hotelRooms);
                printf("\n");
                break;
            case 5:
                displayTreeStructure(hotelRooms, 0);
                break;
            case 6:
                saveRoomsToFile(hotelRooms, fileName);
                printf("Hotel rooms data saved to file.\n");
                break;
            case 7:
                hotelRooms = loadRoomsFromFile(fileName);
                if (hotelRooms != NULL) {
                    printf("Hotel rooms data loaded from file.\n");
                } else {
                    printf("Error loading data from file.\n");
                }
                break;
            case 8:
                freeTree(hotelRooms);
                printf("Memory freed. Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 8);

    return 0;
}

// Function to create a new hotel room
Room* createRoom(int roomNumber, const char* guestName) {
    Room* newRoom = (Room*)malloc(sizeof(Room));
    if (newRoom == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    newRoom->roomNumber = roomNumber;
    strcpy(newRoom->guestName, guestName);
    newRoom->left = newRoom->right = NULL;

    return newRoom;
}

// Function to insert a hotel room in level order
Room* insertRoomLevelOrder(Room* root, int roomNumber, const char* guestName) {
    if (root == NULL) {
        return createRoom(roomNumber, guestName);
    }

    // Create an array to hold the nodes at the last level
    Room** nodes = (Room**)malloc(sizeof(Room*) * 100);
    int front = -1, rear = -1;
    nodes[++rear] = root;

    while (front != rear) {
        Room* temp = nodes[++front];

        if (temp->left == NULL) {
            temp->left = createRoom(roomNumber, guestName);
            free(nodes);
            return root;
        } else {
            nodes[++rear] = temp->left;
        }

        if (temp->right == NULL) {
            temp->right = createRoom(roomNumber, guestName);
            free(nodes);
            return root;
        } else {
            nodes[++rear] = temp->right;
        }
    }

    free(nodes);
    return root;
}

// Function to perform in-order traversal
void printInOrder(Room* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("Room %d: %s\n", root->roomNumber, root->guestName);
        printInOrder(root->right);
    }
}

// Function to perform pre-order traversal
void printPreOrder(Room* root) {
    if (root != NULL) {
        printf("Room %d: %s\n", root->roomNumber, root->guestName);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

// Function to perform post-order traversal
void printPostOrder(Room* root) {
    if (root != NULL) {
        printPostOrder(root->left);
        printPostOrder(root->right);
        printf("Room %d: %s\n", root->roomNumber, root->guestName);
    }
}

// Function to display tree structure
void displayTreeStructure(Room* root, int level) {
    if (root != NULL) {
        displayTreeStructure(root->right, level + 1);
        for (int i = 0; i < level; i++) {
            printf("\t");
        }
        printf("Room %d: %s\n", root->roomNumber, root->guestName);
        displayTreeStructure(root->left, level + 1);
    }
}

// Function to display menu
void displayMenu() {
    printf("\n----- Hotel Management System Menu -----\n");
    printf("1. Add a new room\n");
    printf("2. Display rooms (In-order Traversal)\n");
    printf("3. Display rooms (Pre-order Traversal)\n");
    printf("4. Display rooms (Post-order Traversal)\n");
    printf("5. Display tree structure\n");
    printf("6. Save rooms data to file\n");
    printf("7. Load rooms data from file\n");
    printf("8. Exit\n");
}

// Function to save hotel rooms data to a file
void saveRoomsToFile(Room* root, const char* fileName) {
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file for writing. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    if (root != NULL) {
        fprintf(file, "%d %s\n", root->roomNumber, root->guestName);
        saveRoomsToFile(root->left, fileName);
        saveRoomsToFile(root->right, fileName);
    }

    fclose(file);
}

// Function to load hotel rooms data from a file
Room* loadRoomsFromFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file for reading. Returning NULL...\n");
        return NULL;
    }

    Room* root = NULL;
    int roomNumber;
    char guestName[50];

    while (fscanf(file, "%d %s", &roomNumber, guestName) == 2) {
        root = insertRoomLevelOrder(root, roomNumber, guestName);
    }

    fclose(file);
    return root;
}

// Function to free memory allocated for the tree
void freeTree(Room* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

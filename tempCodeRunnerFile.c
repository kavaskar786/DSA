#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure to represent a hotel room
typedef struct Room {
    int roomNumber;
    // Add other room details as needed
    struct Room *left;
    struct Room *right;
} Room;

// Function prototypes
Room *insert(Room *root, int roomNumber);
Room *deleteRoom(Room *root, int roomNumber);
Room *search(Room *root, int roomNumber);
int getHeight(Room *root);
void inorderTraversal(Room *root);
void preorderTraversal(Room *root);
void postorderTraversal(Room *root);
void displayMenu();

int main() {
    Room *root = NULL;
    srand(time(NULL)); // Seed for random number generation

    int choice, roomNumber;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Insert a room
                printf("Enter room number to insert: ");
                scanf("%d", &roomNumber);
                root = insert(root, roomNumber);
                break;

            case 2:
                // Delete a room
                printf("Enter room number to delete: ");
                scanf("%d", &roomNumber);
                root = deleteRoom(root, roomNumber);
                break;

            case 3:
                // Search for a room
                printf("Enter room number to search: ");
                scanf("%d", &roomNumber);
                Room *result = search(root, roomNumber);
                if (result != NULL) {
                    printf("Room %d found!\n", roomNumber);
                } else {
                    printf("Room %d not found!\n", roomNumber);
                }
                break;

            case 4:
                // Calculate height of the BST
                printf("Height of the BST: %d\n", getHeight(root));
                break;

            case 5:
                // Inorder traversal
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;

            case 6:
                // Preorder traversal
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;

            case 7:
                // Postorder traversal
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;

            case 8:
                // Exit the program
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 8);

    return 0;
}

// Function to insert a room into the BST
Room *insert(Room *root, int roomNumber) {
    if (root == NULL) {
        Room *newRoom = (Room *)malloc(sizeof(Room));
        newRoom->roomNumber = roomNumber;
        newRoom->left = newRoom->right = NULL;
        return newRoom;
    }

    if (roomNumber < root->roomNumber) {
        root->left = insert(root->left, roomNumber);
    } else if (roomNumber > root->roomNumber) {
        root->right = insert(root->right, roomNumber);
    }

    return root;
}

// Function to delete a room from the BST
Room *deleteRoom(Room *root, int roomNumber) {
    if (root == NULL) {
        return root;
    }

    if (roomNumber < root->roomNumber) {
        root->left = deleteRoom(root->left, roomNumber);
    } else if (roomNumber > root->roomNumber) {
        root->right = deleteRoom(root->right, roomNumber);
    } else {
        // Room found, perform deletion
        if (root->left == NULL) {
            Room *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Room *temp = root->left;
            free(root);
            return temp;
        }

        // Room with two children, find the inorder successor
        Room *temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        // Copy the inorder successor's data to this node
        root->roomNumber = temp->roomNumber;

        // Delete the inorder successor
        root->right = deleteRoom(root->right, temp->roomNumber);
    }

    return root;
}

// Function to search for a room in the BST
Room *search(Room *root, int roomNumber) {
    if (root == NULL || root->roomNumber == roomNumber) {
        return root;
    }

    if (roomNumber < root->roomNumber) {
        return search(root->left, roomNumber);
    }

    return search(root->right, roomNumber);
}

// Function to calculate the height of the BST
int getHeight(Room *root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// Function for inorder traversal of the BST
void inorderTraversal(Room *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->roomNumber);
        inorderTraversal(root->right);
    }
}

// Function for preorder traversal of the BST
void preorderTraversal(Room *root) {
    if (root != NULL) {
        printf("%d ", root->roomNumber);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Function for postorder traversal of the BST
void postorderTraversal(Room *root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->roomNumber);
    }
}

// Function to display menu
void displayMenu() {
    printf("\n===== Hotel Management System Menu =====\n");
    printf("1. Insert a Room\n");
    printf("2. Delete a Room\n");
    printf("3. Search for a Room\n");
    printf("4. Calculate Height of BST\n");
    printf("5. Inorder Traversal\n");
    printf("6. Preorder Traversal\n");
    printf("7. Postorder Traversal\n");
    printf("8. Exit\n");
}

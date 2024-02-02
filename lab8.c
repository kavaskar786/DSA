#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure to represent a restaurant table
typedef struct Table {
    int tableNumber;
    // Add other table details as needed
    struct Table *left;
    struct Table *right;
} Table;

// Function prototypes
Table *insert(Table *root, int tableNumber);
Table *deleteTable(Table *root, int tableNumber);
Table *search(Table *root, int tableNumber);
int getHeight(Table *root);
void inorderTraversal(Table *root);
void preorderTraversal(Table *root);
void postorderTraversal(Table *root);
void displayMenu();

int main() {
    Table *root = NULL;
    srand(time(NULL)); // Seed for random number generation

    int choice, tableNumber;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Insert a table
                printf("Enter table number to insert: ");
                scanf("%d", &tableNumber);
                root = insert(root, tableNumber);
                break;

            case 2:
                // Delete a table
                printf("Enter table number to delete: ");
                scanf("%d", &tableNumber);
                root = deleteTable(root, tableNumber);
                break;

            case 3:
                // Search for a table
                printf("Enter table number to search: ");
                scanf("%d", &tableNumber);
                Table *result = search(root, tableNumber);
                if (result != NULL) {
                    printf("Table %d found!\n", tableNumber);
                } else {
                    printf("Table %d not found!\n", tableNumber);
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

// Function to insert a table into the BST
Table *insert(Table *root, int tableNumber) {
    if (root == NULL) {
        Table *newTable = (Table *)malloc(sizeof(Table));
        newTable->tableNumber = tableNumber;
        newTable->left = newTable->right = NULL;
        return newTable;
    }

    if (tableNumber < root->tableNumber) {
        root->left = insert(root->left, tableNumber);
    } else if (tableNumber > root->tableNumber) {
        root->right = insert(root->right, tableNumber);
    }

    return root;
}

// Function to delete a table from the BST
Table *deleteTable(Table *root, int tableNumber) {
    if (root == NULL) {
        return root;
    }

    if (tableNumber < root->tableNumber) {
        root->left = deleteTable(root->left, tableNumber);
    } else if (tableNumber > root->tableNumber) {
        root->right = deleteTable(root->right, tableNumber);
    } else {
        // Table found, perform deletion
        if (root->left == NULL) {
            Table *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Table *temp = root->left;
            free(root);
            return temp;
        }

        // Table with two children, find the inorder successor
        Table *temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        // Copy the inorder successor's data to this node
        root->tableNumber = temp->tableNumber;

        // Delete the inorder successor
        root->right = deleteTable(root->right, temp->tableNumber);
    }

    return root;
}

// Function to search for a table in the BST
Table *search(Table *root, int tableNumber) {
    if (root == NULL || root->tableNumber == tableNumber) {
        return root;
    }

    if (tableNumber < root->tableNumber) {
        return search(root->left, tableNumber);
    }

    return search(root->right, tableNumber);
}

// Function to calculate the height of the BST
int getHeight(Table *root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// Function for inorder traversal of the BST
void inorderTraversal(Table *root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->tableNumber);
        inorderTraversal(root->right);
    }
}

// Function for preorder traversal of the BST
void preorderTraversal(Table *root) {
    if (root != NULL) {
        printf("%d ", root->tableNumber);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Function for postorder traversal of the BST
void postorderTraversal(Table *root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->tableNumber);
    }
}

// Function to display menu
void displayMenu() {
    printf("\n===== Restaurant Management System Menu =====\n");
    printf("1. Insert a Table\n");
    printf("2. Delete a Table\n");
    printf("3. Search for a Table\n");
    printf("4. Calculate Height of BST\n");
    printf("5. Inorder Traversal\n");
    printf("6. Preorder Traversal\n");
    printf("7. Postorder Traversal\n");
    printf("8. Exit\n");
}
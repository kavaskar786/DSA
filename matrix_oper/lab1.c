#include <stdio.h>
#include <string.h>

#define MAX_ROWS 2
#define MAX_COLS 2
#define MAX_NAME_LENGTH 50

// Define the structure for guest information
struct Guest {
    int guestId;
    char guestName[MAX_NAME_LENGTH];
    int roomNumber;
    double roomPrice; // Added roomPrice field
};

// Function prototypes
void displayMatrix(struct Guest (*matrix)[MAX_COLS], int rows, int cols);
void insertData(struct Guest (*matrix)[MAX_COLS], int rows, int cols, int guestId, const char *guestName, int roomNumber, double roomPrice);
void deleteData(struct Guest (*matrix)[MAX_COLS], int rows, int cols, int guestId);
int linearSearch(struct Guest (*matrix)[MAX_COLS], int rows, int cols, int guestId);
void matrixAddition(struct Guest (*matrixA)[MAX_COLS], struct Guest (*matrixB)[MAX_COLS], struct Guest (*result)[MAX_COLS], int rows, int cols);
void matrixMultiplication(struct Guest (*matrixA)[MAX_COLS], int (*members)[MAX_COLS], struct Guest (*matrixB)[MAX_COLS], struct Guest (*result)[MAX_COLS], int rowsA, int colsA, int rowsB, int colsB);

int main() {
    struct Guest hotelMatrix[MAX_ROWS][MAX_COLS];  // Declare matrix without initialization
    int membersMatrix[MAX_ROWS][MAX_COLS]; // Matrix to store the number of members staying
    int choice;

    // Initialize matrix with zeros
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            hotelMatrix[i][j].guestId = 0;
            strcpy(hotelMatrix[i][j].guestName, "");
            hotelMatrix[i][j].roomNumber = 0;
            hotelMatrix[i][j].roomPrice = 0.0;
            membersMatrix[i][j] = 0;
        }
    }

    do {
        // Display menu
        printf("\nHotel Management System Menu:\n");
        printf("1. Display Hotel Matrix\n");
        printf("2. Insert Guest\n");
        printf("3. Delete Guest\n");
        printf("4. Search for Guest\n");
        printf("5. Matrix Addition\n");
        printf("6. Matrix Multiplication\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Hotel Matrix:\n");
                displayMatrix(hotelMatrix, MAX_ROWS, MAX_COLS);
                break;
            case 2:
                {
                    int guestId, roomNumber;
                    char guestName[MAX_NAME_LENGTH];
                    double roomPrice;

                    printf("Enter Guest ID: ");
                    scanf("%d", &guestId);
                    printf("Enter Guest Name: ");
                    scanf("%s", guestName);
                    printf("Enter Room Number: ");
                    scanf("%d", &roomNumber);
                    printf("Enter Room Price: ");
                    scanf("%lf", &roomPrice);

                    insertData(hotelMatrix, MAX_ROWS, MAX_COLS, guestId, guestName, roomNumber, roomPrice);
                }
                break;
            case 3:
                {
                    int guestId;
                    printf("Enter Guest ID to delete: ");
                    scanf("%d", &guestId);
                    deleteData(hotelMatrix, MAX_ROWS, MAX_COLS, guestId);
                }
                break;
            case 4:
                {
                    int guestIdToSearch;
                    printf("Enter Guest ID to search: ");
                    scanf("%d", &guestIdToSearch);
                    int result = linearSearch(hotelMatrix, MAX_ROWS, MAX_COLS, guestIdToSearch);
                    if (result != -1) {
                        printf("Guest with ID %d found in room %d.\n", guestIdToSearch, result);
                    } else {
                        printf("Guest with ID %d not found.\n", guestIdToSearch);
                    }
                }
                break;
            case 5:
                {
                    struct Guest matrixA[MAX_ROWS][MAX_COLS];
                    struct Guest matrixB[MAX_ROWS][MAX_COLS];
                    struct Guest resultMatrix[MAX_ROWS][MAX_COLS];

                    // Input for Matrix A (Price)
                    printf("Enter room prices for Matrix A:\n");
                    for (int i = 0; i < MAX_ROWS; i++) {
                        for (int j = 0; j < MAX_COLS; j++) {
                            printf("Enter Room Price for position (%d, %d): ", i, j);
                            scanf("%lf", &matrixA[i][j].roomPrice);
                        }
                    }

                    // Input for Matrix B (Price)
                    printf("Enter room prices for Matrix B:\n");
                    for (int i = 0; i < MAX_ROWS; i++) {
                        for (int j = 0; j < MAX_COLS; j++) {
                            printf("Enter Room Price for position (%d, %d): ", i, j);
                            scanf("%lf", &matrixB[i][j].roomPrice);
                        }
                    }

                    matrixAddition(matrixA, matrixB, resultMatrix, MAX_ROWS, MAX_COLS);
                    printf("Matrix Addition Result:\n");
                    displayMatrix(resultMatrix, MAX_ROWS, MAX_COLS);
                }
                break;
            case 6:
                {
                    struct Guest matrixA[MAX_ROWS][MAX_COLS];
                    struct Guest matrixB[MAX_ROWS][MAX_COLS];
                    struct Guest resultMatrix[MAX_ROWS][MAX_COLS];

                    // Input for Matrix A (Members)
                    printf("Enter number of members staying for Matrix A:\n");
                    for (int i = 0; i < MAX_ROWS; i++) {
                        for (int j = 0; j < MAX_COLS; j++) {
                            printf("Enter number of members for position (%d, %d): ", i, j);
                            scanf("%d", &membersMatrix[i][j]);
                        }
                    }

                    // Input for Matrix B (Price)
                    printf("Enter room prices for Matrix B:\n");
                    for (int i = 0; i < MAX_ROWS; i++) {
                        for (int j = 0; j < MAX_COLS; j++) {
                            printf("Enter Room Price for position (%d, %d): ", i, j);
                            scanf("%lf", &matrixB[i][j].roomPrice);
                        }
                    }

                    matrixMultiplication(matrixA, membersMatrix, matrixB, resultMatrix, MAX_ROWS, MAX_COLS, MAX_ROWS, MAX_COLS);
                    printf("Matrix Multiplication Result:\n");
                    displayMatrix(resultMatrix, MAX_ROWS, MAX_COLS);
                }
                break;
            case 0:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 0);

    return 0;
}

void displayMatrix(struct Guest (*matrix)[MAX_COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Guest ID: %d, Name: %s, Room Number: %d, Room Price: %.2lf\t", matrix[i][j].guestId, matrix[i][j].guestName, matrix[i][j].roomNumber, matrix[i][j].roomPrice);
        }
        printf("\n");
    }
}

void insertData(struct Guest (*matrix)[MAX_COLS], int rows, int cols, int guestId, const char *guestName, int roomNumber, double roomPrice) {
    // Insert data into the first available position in the matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j].guestId == 0) {
                matrix[i][j].guestId = guestId;
                strcpy(matrix[i][j].guestName, guestName);
                matrix[i][j].roomNumber = roomNumber;
                matrix[i][j].roomPrice = roomPrice;
                printf("Guest inserted successfully.\n");
                return;
            }
        }
    }
    printf("Matrix is full. Cannot insert more guests.\n");
}

void deleteData(struct Guest (*matrix)[MAX_COLS], int rows, int cols, int guestId) {
    // Search for the guest and delete if found
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j].guestId == guestId) {
                matrix[i][j].guestId = 0;
                strcpy(matrix[i][j].guestName, "");
                matrix[i][j].roomNumber = 0;
                matrix[i][j].roomPrice = 0.0;
                printf("Guest with ID %d deleted successfully.\n", guestId);
                return;
            }
        }
    }
    printf("Guest with ID %d not found. Deletion failed.\n", guestId);
}

int linearSearch(struct Guest (*matrix)[MAX_COLS], int rows, int cols, int guestId) {
    // Search for the guest and return the room number if found
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j].guestId == guestId) {
                return matrix[i][j].roomNumber;
            }
        }
    }
    return -1; // Guest not found
}

void matrixAddition(struct Guest (*matrixA)[MAX_COLS], struct Guest (*matrixB)[MAX_COLS], struct Guest (*result)[MAX_COLS], int rows, int cols) {
    // Perform matrix addition
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j].roomPrice = matrixA[i][j].roomPrice + matrixB[i][j].roomPrice;
        }
    }
}

void matrixMultiplication(struct Guest (*matrixA)[MAX_COLS], int (*members)[MAX_COLS], struct Guest (*matrixB)[MAX_COLS], struct Guest (*result)[MAX_COLS], int rowsA, int colsA, int rowsB, int colsB) {
    // Perform matrix multiplication
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j].roomPrice = members[i][j] * matrixB[i][j].roomPrice;
        }
    }
}

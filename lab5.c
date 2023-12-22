#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define a structure for hotel rooms
struct HotelRoom {
    int roomNumber;
    char guestName[50];
};

// Function prototypes
int linearSearch(struct HotelRoom rooms[], int n, int roomNumber, int *elementComparisons, int *indexComparisons);
int sentinelSearch(struct HotelRoom rooms[], int n, int roomNumber, int *elementComparisons, int *indexComparisons);
int binarySearch(struct HotelRoom rooms[], int low, int high, int roomNumber, int *elementComparisons, int *indexComparisons);
void bubbleSort(struct HotelRoom rooms[], int n, int *comparisons, int *dataTransfers);
void insertionSort(struct HotelRoom rooms[], int n, int *comparisons, int *dataTransfers);
void displayRooms(struct HotelRoom rooms[], int n);
void generateRandomData(struct HotelRoom rooms[], int n);
void writeDataToFile(struct HotelRoom rooms[], int n, const char *fileName);
void readDataFromFile(struct HotelRoom rooms[], int n, const char *fileName);

int main() {
    // Scenario: Hotel Management
    // Each hotel room has a room number and a guest name.

    int n = 5; // Number of hotel rooms
    struct HotelRoom rooms[5]; // Array to store hotel room data

    // Generate random data for hotel rooms
    generateRandomData(rooms, n);

    // Write data to a file
    const char *fileName = "hotel_data.txt";
    writeDataToFile(rooms, n, fileName);

    // Read data from the file
    readDataFromFile(rooms, n, fileName);

    int roomNumber, elementComparisons, indexComparisons, comparisons, transfers;
    int choice;

    do {
        // Display menu
        printf("\nHotel Management System Menu\n");
        printf("1. Linear Search\n");
        printf("2. Sentinel Search\n");
        printf("3. Bubble Sort\n");
        printf("4. Insertion Sort\n");
        printf("5. Binary Search\n");
        printf("6. Display Hotel Rooms\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Linear Search
                printf("Enter room number to search: ");
                scanf("%d", &roomNumber);
                elementComparisons = indexComparisons = 0;
                int linearResult = linearSearch(rooms, n, roomNumber, &elementComparisons, &indexComparisons);
                printf("Linear Search Result:\nIndex: %d\nElement Comparisons: %d\nIndex Comparisons: %d\n",
                       linearResult, elementComparisons, indexComparisons);

                // Display the changed structure
                printf("Changed Structure after Linear Search:\n");
                displayRooms(rooms, n);
                break;

            case 2:
                // Sentinel Search
                printf("Enter room number to search: ");
                scanf("%d", &roomNumber);
                elementComparisons = indexComparisons = 0;
                int sentinelResult = sentinelSearch(rooms, n, roomNumber, &elementComparisons, &indexComparisons);
                printf("Sentinel Search Result:\nIndex: %d\nElement Comparisons: %d\nIndex Comparisons: %d\n",
                       sentinelResult, elementComparisons, indexComparisons);

                // Display the changed structure
                printf("Changed Structure after Sentinel Search:\n");
                displayRooms(rooms, n);
                break;

            case 3:
                // Bubble Sort
                comparisons = transfers = 0;
                bubbleSort(rooms, n, &comparisons, &transfers);
                printf("Bubble Sort Result:\nComparisons: %d\nData Transfers: %d\n", comparisons, transfers);

                // Display the changed structure
                printf("Changed Structure after Bubble Sort:\n");
                displayRooms(rooms, n);
                break;

            case 4:
                // Insertion Sort
                comparisons = transfers = 0;
                insertionSort(rooms, n, &comparisons, &transfers);
                printf("Insertion Sort Result:\nComparisons: %d\nData Transfers: %d\n", comparisons, transfers);

                // Display the changed structure
                printf("Changed Structure after Insertion Sort:\n");
                displayRooms(rooms, n);
                break;

            case 5:
                // Binary Search
                printf("Enter room number to search: ");
                scanf("%d", &roomNumber);
                elementComparisons = indexComparisons = 0;
                int binaryResult = binarySearch(rooms, 0, n - 1, roomNumber, &elementComparisons, &indexComparisons);
                printf("Binary Search Result:\nIndex: %d\nElement Comparisons: %d\nIndex Comparisons: %d\n",
                       binaryResult, elementComparisons, indexComparisons);

                // Display the changed structure
                printf("Changed Structure after Binary Search:\n");
                displayRooms(rooms, n);
                break;

            case 6:
                // Display Hotel Rooms
                displayRooms(rooms, n);
                break;

            case 7:
                // Exit
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 7);

    return 0;
}

// Function to perform linear search on hotel rooms
int linearSearch(struct HotelRoom rooms[], int n, int roomNumber, int *elementComparisons, int *indexComparisons) {
    for (int i = 0; i < n; i++) {
        (*elementComparisons)++;
        if (rooms[i].roomNumber == roomNumber) {
            (*indexComparisons)++;
            return i; // Room found, return the index
        }
    }
    return -1; // Room not found
}

// Function to perform sentinel search on hotel rooms
int sentinelSearch(struct HotelRoom rooms[], int n, int roomNumber, int *elementComparisons, int *indexComparisons) {
    // Create a sentinel room with the given room number
    struct HotelRoom sentinelRoom;
    sentinelRoom.roomNumber = roomNumber;

    // Set the last room as sentinel
    rooms[n - 1] = sentinelRoom;

    int i = 0;
    while (rooms[i].roomNumber != roomNumber) {
        (*elementComparisons)++;
        i++;
    }

    // Restore the last room
    if (i < n - 1 || rooms[n - 1].roomNumber == roomNumber) {
        (*indexComparisons)++;
        return i; // Room found, return the index
    }

    return -1; // Room not found
}

// Function to perform binary search on hotel rooms
int binarySearch(struct HotelRoom rooms[], int low, int high, int roomNumber, int *elementComparisons, int *indexComparisons) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        (*elementComparisons)++;

        if (rooms[mid].roomNumber == roomNumber) {
            (*indexComparisons)++;
            return mid; // Room found, return the index
        } else if (rooms[mid].roomNumber < roomNumber) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1; // Room not found
}

// Function to perform bubble sort on hotel rooms
void bubbleSort(struct HotelRoom rooms[], int n, int *comparisons, int *dataTransfers) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparisons)++;
            if (rooms[j].roomNumber > rooms[j + 1].roomNumber) {
                // Swap rooms if they are in the wrong order
                struct HotelRoom temp = rooms[j];
                rooms[j] = rooms[j + 1];
                rooms[j + 1] = temp;
                (*dataTransfers)++;
            }
        }
    }
}

// Function to perform insertion sort on hotel rooms
void insertionSort(struct HotelRoom rooms[], int n, int *comparisons, int *dataTransfers) {
    for (int i = 1; i < n; i++) {
        struct HotelRoom key = rooms[i];
        int j = i - 1;

        (*comparisons)++;
        while (j >= 0 && rooms[j].roomNumber > key.roomNumber) {
            // Move rooms greater than key to one position ahead
            rooms[j + 1] = rooms[j];
            j--;
            (*dataTransfers)++;
            (*comparisons)++;
        }

        // Insert the key at its correct position
        rooms[j + 1] = key;
        (*dataTransfers)++;
    }
}

// Function to display hotel rooms
void displayRooms(struct HotelRoom rooms[], int n) {
    printf("Hotel Rooms:\n");
    for (int i = 0; i < n; i++) {
        printf("Room %d: Guest: %s\n", rooms[i].roomNumber, rooms[i].guestName);
    }
}

// Function to generate random data for hotel rooms
void generateRandomData(struct HotelRoom rooms[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        rooms[i].roomNumber = rand() % 1000 + 100; // Room numbers between 100 and 109
        sprintf(rooms[i].guestName, "Guest%d", i + 1);
    }
}

// Function to write hotel room data to a file
void writeDataToFile(struct HotelRoom rooms[], int n, const char *fileName) {
    FILE *file = fopen(fileName, "w");
    if (file != NULL) {
        fwrite(rooms, sizeof(struct HotelRoom), n, file);
        fclose(file);
        printf("Data written to %s successfully.\n", fileName);
    } else {
        printf("Error opening %s for writing.\n", fileName);
    }
}

// Function to read hotel room data from a file
void readDataFromFile(struct HotelRoom rooms[], int n, const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file != NULL) {
        fread(rooms, sizeof(struct HotelRoom), n, file);
        fclose(file);
        printf("Data read from %s successfully.\n", fileName);
    } else {
        printf("Error opening %s for reading.\n", fileName);
    }
}

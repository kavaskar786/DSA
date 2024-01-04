#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define a structure to represent hotel information
struct Hotel {
    char name[50];
    int rating;
    double price;
};

// Function to generate random data for hotels
void generateRandomData(struct Hotel hotels[], int size) {
    srand(time(NULL));

    for (int i = 0; i < size; ++i) {
        sprintf(hotels[i].name, "Hotel%d", i + 1);
        hotels[i].rating = rand() % 5 + 1;          // Random rating between 1 and 5
        hotels[i].price = rand() % 1000 + 100.0;    // Random price between 100 and 1100
    }
}

// Function to print hotel information
void printHotels(struct Hotel hotels[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("Name: %s, Rating: %d, Price: %.2f\n", hotels[i].name, hotels[i].rating, hotels[i].price);
    }
}

// Merge Sort
int merge(struct Hotel arr[], int l, int m, int r, int *comparisons, int *transfers) {
    int n1 = m - l + 1;
    int n2 = r - m;

    struct Hotel L[n1], R[n2];
    int comparisons_local = 0;
    int transfers_local = 0;

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        comparisons_local++;
        if (L[i].rating <= R[j].rating) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
            transfers_local++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        transfers_local++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        transfers_local++;
    }

    *comparisons = comparisons_local;
    *transfers = transfers_local;
    return comparisons_local;
}

int mergeSort(struct Hotel arr[], int l, int r, int *comparisons, int *transfers) {
    int comparisons_local = 0;
    int transfers_local = 0;
    if (l < r) {
        int m = l + (r - l) / 2;
        comparisons_local += mergeSort(arr, l, m, comparisons, transfers);
        comparisons_local += mergeSort(arr, m + 1, r, comparisons, transfers);
        comparisons_local += merge(arr, l, m, r, comparisons, transfers);
    }
    return comparisons_local;
}

// Quick Sort
int partition(struct Hotel arr[], int low, int high, int *comparisons, int *transfers) {
    double pivot = arr[high].price;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        (*comparisons)++;
        if (arr[j].price < pivot) {
            i++;
            struct Hotel temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            (*transfers)++;
        }
    }

    struct Hotel temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

int quickSort(struct Hotel arr[], int low, int high, int *comparisons, int *transfers) {
    int pi;
    if (low < high) {
        pi = partition(arr, low, high, comparisons, transfers);
        quickSort(arr, low, pi - 1, comparisons, transfers);
        quickSort(arr, pi + 1, high, comparisons, transfers);
    }
    return *comparisons;
}

// Function to perform read and write operations in files
void writeToFile(struct Hotel hotels[], int size, const char *filename) {
    FILE *outFile = fopen(filename, "w");

    for (int i = 0; i < size; ++i) {
        fprintf(outFile, "%s %d %.2f\n", hotels[i].name, hotels[i].rating, hotels[i].price);
    }

    fclose(outFile);
}

void readFromFile(struct Hotel hotels[], int size, const char *filename) {
    FILE *inFile = fopen(filename, "r");

    for (int i = 0; i < size; ++i) {
        fscanf(inFile, "%s %d %lf", hotels[i].name, &hotels[i].rating, &hotels[i].price);
    }

    fclose(inFile);
}

// Function to display menu and get user choice
int getMenuChoice() {
    int choice;
    printf("\n1. Generate Random Data\n");
    printf("2. Display Randomly Generated Data\n");
    printf("3. Sort based on Rating (Merge Sort)\n");
    printf("4. Sort based on Price (Quick Sort)\n");
    printf("5. Display Sorted Data\n");
    printf("6. Write Data to File\n");
    printf("7. Read Data from File\n");
    printf("8. Compare Sorting Techniques\n");
    printf("9. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

int main() {
    const int size = 10;
    struct Hotel hotels[size];
    int mergeComparisons, quickComparisons;
    int mergeTransfers, quickTransfers;

    int userChoice;

    do {
        userChoice = getMenuChoice();

        switch (userChoice) {
        case 1:
            // Generate random data for hotels
            generateRandomData(hotels, size);
            printf("Random data generated successfully.\n");
            break;

        case 2:
            // Display randomly generated data
            printf("\nRandomly Generated Data:\n");
            printHotels(hotels, size);
            break;

        case 3:
            // Sorting using Merge Sort based on rating
            mergeComparisons = mergeSort(hotels, 0, size - 1, &mergeComparisons, &mergeTransfers);
            printf("\nHotels after Merge Sort based on rating:\n");
            printHotels(hotels, size);
            printf("Merge Sort Comparisons: %d\n", mergeComparisons);
            printf("Merge Sort Data Transfers: %d\n", mergeTransfers);
            break;

        case 4:
            // Sorting using Quick Sort based on price
            quickComparisons = 0;
            quickTransfers = 0;
            quickSort(hotels, 0, size - 1, &quickComparisons, &quickTransfers);
            printf("\nHotels after Quick Sort based on price:\n");
            printHotels(hotels, size);
            printf("Quick Sort Comparisons: %d\n", quickComparisons);
            printf("Quick Sort Data Transfers: %d\n", quickTransfers);
            break;

        case 5:
            // Display sorted data
            printf("\nSorted Data:\n");
            printHotels(hotels, size);
            break;

        case 6:
            // Write sorted data to a file
            writeToFile(hotels, size, "sorted_data.txt");
            printf("Sorted data written to file successfully.\n");
            break;

        case 7:
            // Read data from a file
            readFromFile(hotels, size, "sorted_data.txt");
            printf("Data read from file successfully.\n");
            break;

        case 8:
            // Compare sorting techniques
            printf("\nComparison of Sorting Techniques:\n");
            printf("Merge Sort Comparisons: %d\n", mergeComparisons);
            printf("Merge Sort Data Transfers: %d\n", mergeTransfers);
            printf("Quick Sort Comparisons: %d\n", quickComparisons);
            printf("Quick Sort Data Transfers: %d\n", quickTransfers);
            break;

        case 9:
            printf("Exiting program. Goodbye!\n");
            break;

        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (userChoice != 9);

    return 0;
}

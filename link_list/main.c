#include "linkedlist.h"
#include <stdio.h>

// Function to display the menu
void displayMenu() {
    printf("\nMENU:\n");
    printf("1. Singly Linked List\n");
    printf("2. Doubly Linked List\n");
    printf("3. Circular Linked List\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

// Function to display the linked list menu
void displayLinkedListMenu() {
    printf("\nLinked List Operations:\n");
    printf("1. Insert at Beginning\n");
    printf("2. Insert at End\n");
    printf("3. Display Rooms\n");
    printf("4. Search Room\n");
    printf("5. Delete Room\n");
    printf("6. Back to Main Menu\n");
    printf("Enter your choice: ");
}
void displayLinkedListMenu1() {
    printf("\nLinked List Operations:\n");
    printf("1. Insert in Circular List\n");
    printf("2. Display Rooms\n");
    printf("3. Search Room\n");
    printf("4. Delete Room\n");
    printf("5. Back to Main Menu\n");
    printf("Enter your choice: ");
}

int main() {
    int mainChoice;
    do {
        displayMenu();
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1: {
                // Singly Linked List
                struct HotelRoom* singlyLinkedList = NULL;
                int choice;
                do {
                    displayLinkedListMenu();
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1: {
                            // Insert at Beginning
                            int roomNumber;
                            char guestName[50];
                            int isReserved;

                            printf("Enter room number: ");
                            scanf("%d", &roomNumber);
                            printf("Enter guest name: ");
                            scanf("%s", guestName);
                            printf("Is the room reserved? (1 for Yes, 0 for No): ");
                            scanf("%d", &isReserved);

                            singlyLinkedList = insertAtBeginning(singlyLinkedList, roomNumber, guestName, isReserved);
                            printf("Room %d added to the beginning of the list.\n", roomNumber);
                            break;
                        }
                        case 2: {
                            // Insert at End
                            int roomNumber;
                            char guestName[50];
                            int isReserved;

                            printf("Enter room number: ");
                            scanf("%d", &roomNumber);
                            printf("Enter guest name: ");
                            scanf("%s", guestName);
                            printf("Is the room reserved? (1 for Yes, 0 for No): ");
                            scanf("%d", &isReserved);

                            singlyLinkedList = insertAtEnd(singlyLinkedList, roomNumber, guestName, isReserved);
                            printf("Room %d added to the end of the list.\n", roomNumber);
                            break;
                        }
                        case 3:
                            // Display Rooms
                            displayRooms(singlyLinkedList);
                            break;
                        case 4: {
                            // Search Room
                            int searchRoomNumber;
                            printf("Enter room number to search: ");
                            scanf("%d", &searchRoomNumber);
                            struct HotelRoom* foundRoom = searchRoom(singlyLinkedList, searchRoomNumber);
                            if (foundRoom != NULL) {
                                printf("Room %d found. Guest Name: %s\n", searchRoomNumber, foundRoom->guestName);
                            } else {
                                printf("Room %d not found.\n", searchRoomNumber);
                            }
                            break;
                        }
                        case 5: {
                            // Delete Room
                            int deleteRoomNumber;
                            printf("Enter room number to delete: ");
                            scanf("%d", &deleteRoomNumber);
                            singlyLinkedList = deleteRoom(singlyLinkedList, deleteRoomNumber);
                            printf("Room %d deleted from the list.\n", deleteRoomNumber);
                            break;
                        }
                        case 6:
                            // Back to Main Menu
                            freeList(singlyLinkedList);
                            break;
                        default:
                            printf("Invalid choice. Please enter a valid option.\n");
                    }
                } while (choice != 6);

                break;
            }
            case 2: {
                // Doubly Linked List
                struct HotelRoom* doublyLinkedList = NULL;
                int choice;
                do {
                    displayLinkedListMenu();
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1: {
                            // Insert at Beginning
                            int roomNumber;
                            char guestName[50];
                            int isReserved;

                            printf("Enter room number: ");
                            scanf("%d", &roomNumber);
                            printf("Enter guest name: ");
                            scanf("%s", guestName);
                            printf("Is the room reserved? (1 for Yes, 0 for No): ");
                            scanf("%d", &isReserved);

                            doublyLinkedList = insertAtBeginningDoubly(doublyLinkedList, roomNumber, guestName, isReserved);
                            printf("Room %d added to the beginning of the list.\n", roomNumber);
                            break;
                        }
                        case 2: {
                            // Insert at End
                            int roomNumber;
                            char guestName[50];
                            int isReserved;

                            printf("Enter room number: ");
                            scanf("%d", &roomNumber);
                            printf("Enter guest name: ");
                            scanf("%s", guestName);
                            printf("Is the room reserved? (1 for Yes, 0 for No): ");
                            scanf("%d", &isReserved);

                            doublyLinkedList = insertAtEndDoubly(doublyLinkedList, roomNumber, guestName, isReserved);
                            printf("Room %d added to the end of the list.\n", roomNumber);
                            break;
                        }
                        case 3:
                            // Display Rooms
                            displayRoomsDoubly(doublyLinkedList);
                            break;
                        case 4: {
                            // Search Room
                            int searchRoomNumber;
                            printf("Enter room number to search: ");
                            scanf("%d", &searchRoomNumber);
                            struct HotelRoom* foundRoom = searchRoomDoubly(doublyLinkedList, searchRoomNumber);
                            if (foundRoom != NULL) {
                                printf("Room %d found. Guest Name: %s\n", searchRoomNumber, foundRoom->guestName);
                            } else {
                                printf("Room %d not found.\n", searchRoomNumber);
                            }
                            break;
                        }
                        case 5: {
                            // Delete Room
                            int deleteRoomNumber;
                            printf("Enter room number to delete: ");
                            scanf("%d", &deleteRoomNumber);
                            doublyLinkedList = deleteRoomDoubly(doublyLinkedList, deleteRoomNumber);
                            printf("Room %d deleted from the list.\n", deleteRoomNumber);
                            break;
                        }
                        case 6:
                            // Back to Main Menu
                            freeListDoubly(doublyLinkedList);
                            break;
                        default:
                            printf("Invalid choice. Please enter a valid option.\n");
                    }
                } while (choice != 6);

                break;
            }
            case 3: {
                // Circular Linked List
                struct HotelRoom* circularLinkedList = NULL;
                int choice;
                do {
                    displayLinkedListMenu1();
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1: {
                            // Insert in Circular List
                            int roomNumber;
                            char guestName[50];
                            int isReserved;

                            printf("Enter room number: ");
                            scanf("%d", &roomNumber);
                            printf("Enter guest name: ");
                            scanf("%s", guestName);
                            printf("Is the room reserved? (1 for Yes, 0 for No): ");
                            scanf("%d", &isReserved);

                            circularLinkedList = insertInCircularList(circularLinkedList, roomNumber, guestName, isReserved);
                            printf("Room %d added to the circular list.\n", roomNumber);
                            break;
                        }
                        case 2:
                            // Display Rooms
                            displayRoomsCircular(circularLinkedList);
                            break;
                        case 3: {
                            // Search Room
                            int searchRoomNumber;
                            printf("Enter room number to search: ");
                            scanf("%d", &searchRoomNumber);
                            struct HotelRoom* foundRoom = searchRoomCircular(circularLinkedList, searchRoomNumber);
                            if (foundRoom != NULL) {
                                printf("Room %d found. Guest Name: %s\n", searchRoomNumber, foundRoom->guestName);
                            } else {
                                printf("Room %d not found.\n", searchRoomNumber);
                            }
                            break;
                        }
                        case 4: {
                            // Delete Room
                            int deleteRoomNumber;
                            printf("Enter room number to delete: ");
                            scanf("%d", &deleteRoomNumber);
                            circularLinkedList = deleteRoomCircular(circularLinkedList, deleteRoomNumber);
                            printf("Room %d deleted from the circular list.\n", deleteRoomNumber);
                            break;
                        }
                        case 5:
                            // Back to Main Menu
                            freeListCircular(circularLinkedList);
                            break;
                        default:
                            printf("Invalid choice. Please enter a valid option.\n");
                    }
                } while (choice != 5);

                break;
            }
            case 4:
                // Exit
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (mainChoice != 4);

    return 0;
}

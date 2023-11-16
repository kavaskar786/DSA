#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implementations for singly linked list functions

struct HotelRoom* createRoom(int roomNumber, const char* guestName, int isReserved) {
    struct HotelRoom* newRoom = (struct HotelRoom*)malloc(sizeof(struct HotelRoom));
    if (newRoom != NULL) {
        newRoom->roomNumber = roomNumber;
        strcpy(newRoom->guestName, guestName);
        newRoom->isReserved = isReserved;
        newRoom->next = NULL;
    }
    return newRoom;
}

struct HotelRoom* insertAtBeginning(struct HotelRoom* head, int roomNumber, const char* guestName, int isReserved) {
    struct HotelRoom* newRoom = createRoom(roomNumber, guestName, isReserved);
    if (newRoom != NULL) {
        newRoom->next = head;
        return newRoom;
    }
    return head;
}

struct HotelRoom* insertAtEnd(struct HotelRoom* head, int roomNumber, const char* guestName, int isReserved) {
    struct HotelRoom* newRoom = createRoom(roomNumber, guestName, isReserved);
    if (newRoom != NULL) {
        if (head == NULL) {
            return newRoom;
        }

        struct HotelRoom* current = head;
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = newRoom;
    }
    return head;
}

void displayRooms(struct HotelRoom* head) {
    printf("Room Number\tGuest Name\tReservation Status\n");
    struct HotelRoom* current = head;
    while (current != NULL) {
        printf("%d\t\t%s\t\t%s\n", current->roomNumber, current->guestName, (current->isReserved) ? "Reserved" : "Not Reserved");
        current = current->next;
    }
    printf("\n");
}

struct HotelRoom* searchRoom(struct HotelRoom* head, int roomNumber) {
    struct HotelRoom* current = head;
    while (current != NULL) {
        if (current->roomNumber == roomNumber) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct HotelRoom* deleteRoom(struct HotelRoom* head, int roomNumber) {
    struct HotelRoom* current = head;
    struct HotelRoom* prev = NULL;

    while (current != NULL) {
        if (current->roomNumber == roomNumber) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                // If the node to be deleted is the head
                head = current->next;
            }

            // Free the memory occupied by the deleted node
            free(current);
            return head;
        }

        prev = current;
        current = current->next;
    }

    printf("Room %d not found.\n", roomNumber);
    return head;
}

void freeList(struct HotelRoom* head) {
    struct HotelRoom* current = head;
    struct HotelRoom* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

// Implementations for doubly linked list functions

struct HotelRoom* createRoomDoubly(int roomNumber, const char* guestName, int isReserved) {
    struct HotelRoom* newRoom = (struct HotelRoom*)malloc(sizeof(struct HotelRoom));
    if (newRoom != NULL) {
        newRoom->roomNumber = roomNumber;
        strcpy(newRoom->guestName, guestName);
        newRoom->isReserved = isReserved;
        newRoom->next = NULL;
        newRoom->prev = NULL;
    }
    return newRoom;
}

struct HotelRoom* insertAtBeginningDoubly(struct HotelRoom* head, int roomNumber, const char* guestName, int isReserved) {
    struct HotelRoom* newRoom = createRoomDoubly(roomNumber, guestName, isReserved);
    if (newRoom != NULL) {
        newRoom->next = head;
        if (head != NULL) {
            head->prev = newRoom;
        }
        return newRoom;
    }
    return head;
}

struct HotelRoom* insertAtEndDoubly(struct HotelRoom* head, int roomNumber, const char* guestName, int isReserved) {
    struct HotelRoom* newRoom = createRoomDoubly(roomNumber, guestName, isReserved);
    if (newRoom != NULL) {
        if (head == NULL) {
            return newRoom;
        }

        struct HotelRoom* current = head;
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = newRoom;
        newRoom->prev = current;
    }
    return head;
}

void displayRoomsDoubly(struct HotelRoom* head) {
    printf("Room Number\tGuest Name\tReservation Status\n");
    struct HotelRoom* current = head;
    while (current != NULL) {
        printf("%d\t\t%s\t\t%s\n", current->roomNumber, current->guestName, (current->isReserved) ? "Reserved" : "Not Reserved");
        current = current->next;
    }
    printf("\n");
}

struct HotelRoom* searchRoomDoubly(struct HotelRoom* head, int roomNumber) {
    struct HotelRoom* current = head;
    while (current != NULL) {
        if (current->roomNumber == roomNumber) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct HotelRoom* deleteRoomDoubly(struct HotelRoom* head, int roomNumber) {
    struct HotelRoom* current = head;
    while (current != NULL) {
        if (current->roomNumber == roomNumber) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
                if (current->next != NULL) {
                    current->next->prev = current->prev;
                }
            } else {
                // If the node to be deleted is the head
                head = current->next;
                if (head != NULL) {
                    head->prev = NULL;
                }
            }

            // Free the memory occupied by the deleted node
            free(current);
            return head;
        }
        current = current->next;
    }

    printf("Room %d not found.\n", roomNumber);
    return head;
}

void freeListDoubly(struct HotelRoom* head) {
    struct HotelRoom* current = head;
    struct HotelRoom* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

// Implementations for circular linked list functions

struct HotelRoom* createRoomCircular(int roomNumber, const char* guestName, int isReserved) {
    struct HotelRoom* newRoom = (struct HotelRoom*)malloc(sizeof(struct HotelRoom));
    if (newRoom != NULL) {
        newRoom->roomNumber = roomNumber;
        strcpy(newRoom->guestName, guestName);
        newRoom->isReserved = isReserved;
        newRoom->next = NULL;
    }
    return newRoom;
}

struct HotelRoom* insertInCircularList(struct HotelRoom* head, int roomNumber, const char* guestName, int isReserved) {
    struct HotelRoom* newRoom = createRoomCircular(roomNumber, guestName, isReserved);
    if (newRoom != NULL) {
        if (head == NULL) {
            newRoom->next = newRoom; // Point to itself for the circular list
            return newRoom;
        }

        struct HotelRoom* current = head;
        while (current->next != head) {
            current = current->next;
        }

        current->next = newRoom;
        newRoom->next = head;
        return head;
    }
    return head;
}

void displayRoomsCircular(struct HotelRoom* head) {
    printf("Room Number\tGuest Name\tReservation Status\n");
    if (head != NULL) {
        struct HotelRoom* current = head;
        do {
            printf("%d\t\t%s\t\t%s\n", current->roomNumber, current->guestName, (current->isReserved) ? "Reserved" : "Not Reserved");
            current = current->next;
        } while (current != head);
    }
    printf("\n");
}

struct HotelRoom* searchRoomCircular(struct HotelRoom* head, int roomNumber) {
    if (head != NULL) {
        struct HotelRoom* current = head;
        do {
            if (current->roomNumber == roomNumber) {
                return current;
            }
            current = current->next;
        } while (current != head);
    }
    return NULL;
}

struct HotelRoom* deleteRoomCircular(struct HotelRoom* head, int roomNumber) {
    if (head != NULL) {
        struct HotelRoom* current = head;
        struct HotelRoom* prev = NULL;

        do {
            if (current->roomNumber == roomNumber) {
                if (prev != NULL) {
                    prev->next = current->next;
                    if (current == head) {
                        head = prev->next; // Update head if the first node is deleted
                    }
                } else {
                    // If the node to be deleted is the head
                    struct HotelRoom* last = head;
                    while (last->next != head) {
                        last = last->next;
                    }
                    if (last == head) {
                        head = NULL; // If only one node is present, set head to NULL
                    } else {
                        head = current->next; // Update head to the next node
                        last->next = head; // Update the last node's next pointer
                    }

                    // Free the memory occupied by the deleted node
                    free(current);
                    return head;
                }
            }

            prev = current;
            current = current->next;
        } while (current != head);
    }

    printf("Room %d not found.\n", roomNumber);
    return head;
}

void freeListCircular(struct HotelRoom* head) {
    if (head != NULL) {
        struct HotelRoom* current = head;
        struct HotelRoom* next;

        do {
            next = current->next;
            free(current);
            current = next;
        } while (current != head);
    }
}

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Define the structure for a hotel room
struct HotelRoom {
    int roomNumber;
    char guestName[50];
    int isReserved;
    struct HotelRoom* next;
    struct HotelRoom* prev;  // For doubly linked list
};

// Function prototypes for singly linked list
struct HotelRoom* createRoom(int roomNumber, const char* guestName, int isReserved);
struct HotelRoom* insertAtBeginning(struct HotelRoom* head, int roomNumber, const char* guestName, int isReserved);
struct HotelRoom* insertAtEnd(struct HotelRoom* head, int roomNumber, const char* guestName, int isReserved);
void displayRooms(struct HotelRoom* head);
struct HotelRoom* searchRoom(struct HotelRoom* head, int roomNumber);
struct HotelRoom* deleteRoom(struct HotelRoom* head, int roomNumber);
void freeList(struct HotelRoom* head);

// Function prototypes for doubly linked list
struct HotelRoom* createRoomDoubly(int roomNumber, const char* guestName, int isReserved);
struct HotelRoom* insertAtBeginningDoubly(struct HotelRoom* head, int roomNumber, const char* guestName, int isReserved);
struct HotelRoom* insertAtEndDoubly(struct HotelRoom* head, int roomNumber, const char* guestName, int isReserved);
void displayRoomsDoubly(struct HotelRoom* head);
struct HotelRoom* searchRoomDoubly(struct HotelRoom* head, int roomNumber);
struct HotelRoom* deleteRoomDoubly(struct HotelRoom* head, int roomNumber);
void freeListDoubly(struct HotelRoom* head);

// Function prototypes for circular linked list
struct HotelRoom* createRoomCircular(int roomNumber, const char* guestName, int isReserved);
struct HotelRoom* insertInCircularList(struct HotelRoom* head, int roomNumber, const char* guestName, int isReserved);
void displayRoomsCircular(struct HotelRoom* head);
struct HotelRoom* searchRoomCircular(struct HotelRoom* head, int roomNumber);
struct HotelRoom* deleteRoomCircular(struct HotelRoom* head, int roomNumber);
void freeListCircular(struct HotelRoom* head);

#endif

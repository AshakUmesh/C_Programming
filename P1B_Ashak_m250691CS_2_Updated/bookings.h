#ifndef BOOKINGS_H
#define BOOKINGS_H

struct passenger {
    char name[50];
    char mobileno[11];  
    char boarding_point[50];
    char dropping_point[50];
};

struct bus {
    char busid[20];
    char driver[50];
    int capacity;
    char boarding_point[50];
    char dropping_point[50];
    struct passenger people[10]; 
    int passengerCount;          
    int isFull;                  
    struct bus *next; 
};

struct booking {
    struct passenger person;
    char busId[20];
    struct booking *prev, *next; 
};

// Global waiting list pointers
extern struct booking *waitHead;
extern struct booking *waitTail;

// Function prototypes
int isValidBusId(const char *busId);
void addBus(struct bus **head1, int n);
void displayBuses(struct bus *head);
void BookTicket(struct bus *head);
void CancelTicket(struct bus *head, char* busId, char* mobile);


#endif

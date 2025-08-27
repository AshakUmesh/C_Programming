#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

 
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
void displayBuses(struct bus *head) {
    if (!head) {
        printf("No buses available.\n");
        return;
    }
    printf("\n--- Bus List ---\n");
    struct bus *temp = head;
    while (temp != NULL) {
        printf("Bus ID: %s | Driver: %s | Capacity: %d | From %s to %s | isFull=%d\n",
               temp->busid, temp->driver, temp->capacity,
               temp->boarding_point, temp->dropping_point, temp->isFull);
        printf("Passengers (%d):\n", temp->passengerCount);
        for (int i = 0; i < temp->passengerCount; i++) {
            printf("   %s | %s | %s -> %s\n",
                   temp->people[i].name,
                   temp->people[i].mobileno,
                   temp->people[i].boarding_point,
                   temp->people[i].dropping_point);
        }
        temp = temp->next;
    }
}
struct booking *waitHead = NULL, *waitTail = NULL; 

int isValidBusId(const char *busId) {
    if (strlen(busId) != 10) return 0;
    if (!isalpha(busId[0]) || !isalpha(busId[1])) return 0;
    if (!isdigit(busId[2]) || !isdigit(busId[3])) return 0;
    if (!isalpha(busId[4]) || !isalpha(busId[5])) return 0;
    for (int i = 6; i < 10; i++) {
        if (!isdigit(busId[i])) return 0;
    }
    return 1; 
}

void addBus(struct bus *head1, int n) {
    for (int i = 0; i < n; i++) {
        struct bus *newnode = (struct bus*)malloc(sizeof(struct bus));
        if (!newnode) {
            printf("Memory allocation failed!\n");
            return;
        }

        printf("Enter bus id: ");
        scanf("%s", &newnode->busid);
        if (!isValidBusId(newnode->busid)) {
            printf("Invalid bus ID format. Please enter a valid bus ID.\n");
            free(newnode);
            i--; 
            continue;
        }

        printf("Enter driver name: ");
        scanf("%s", newnode->driver);
        printf("Enter capacity (<=10): ");
        scanf("%d", &newnode->capacity);
        if(newnode->capacity>10){
            free(newnode);
            i--;
            continue;
        }
        printf("Enter boarding point: ");
        scanf("%s", newnode->boarding_point);
        printf("Enter dropping point: ");
        scanf("%s", newnode->dropping_point);

        newnode->passengerCount = 0; 
        newnode->isFull = 0; 
        newnode->next = NULL;

        if (head1 == NULL) {
            head1 = newnode;  
        } else {
            struct bus *temp = head1;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newnode;
        }

        printf("Bus %s added successfully!\n", newnode->busid);
    }
}

void enqueueWaiting(struct passenger p, char *busId) {
    struct booking *node = (struct booking*)malloc(sizeof(struct booking));
    node->person = p;
    strcpy(node->busId, busId);
    node->prev = waitTail;
    node->next = NULL;
    if (!waitHead) {
        waitHead = waitTail = node;
    } else {
        waitTail->next = node;
        waitTail = node;
    }
    printf("Passenger %s added to waiting list for Bus %s\n", p.name, busId);
}

struct booking* dequeueWaiting(char *busId) {
    struct booking *curr = waitHead;
    while (curr) {
        if (strcmp(curr->busId, busId) == 0) {
            if (curr->prev) curr->prev->next = curr->next;
            else waitHead = curr->next;
            if (curr->next) curr->next->prev = curr->prev;
            else waitTail = curr->prev;
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}


void BookTicket(struct bus *head) {
    struct passenger p;
    printf("Enter passenger name: ");
    scanf("%s", p.name);
    printf("Enter mobile number: ");
    scanf("%s", p.mobileno);
    printf("Enter boarding point: ");
    scanf("%s", p.boarding_point);
    printf("Enter dropping point: ");
    scanf("%s", p.dropping_point);

    struct bus *temp = head;
    while (temp) {
        if (strcmp(temp->boarding_point, p.boarding_point) == 0 &&
            strcmp(temp->dropping_point, p.dropping_point) == 0) {
            
            if (temp->passengerCount < temp->capacity) {
                temp->people[temp->passengerCount++] = p;
                if (temp->passengerCount == temp->capacity) temp->isFull = 1; 
                printf("Ticket booked in Bus %s\n", temp->busid);
            } else {
                enqueueWaiting(p, temp->busid); // NEW
            }
            return;
        }
        temp = temp->next;
    }
    printf("BUS NOT FOUND\n");
}

void CancelTicket(struct bus *head, char* busId, char* mobile) {
    struct bus *temp = head;
    while (temp) {
        if (strcmp(temp->busid, busId) == 0) {
            for (int i = 0; i < temp->passengerCount; i++) {
                if (strcmp(temp->people[i].mobileno, mobile) == 0) {
                    for (int j = i; j < temp->passengerCount - 1; j++) {
                        temp->people[j] = temp->people[j + 1];
                    }
                    temp->passengerCount--;
                    temp->isFull = 0; // NEW
                    printf("Ticket cancelled for mobile number %s in Bus %s\n", mobile, busId);

                    // NEW: check waiting list
                    struct booking *wb = dequeueWaiting(busId);
                    if (wb) {
                        temp->people[temp->passengerCount++] = wb->person;
                        if (temp->passengerCount == temp->capacity) temp->isFull = 1;
                        printf("%s moved from waiting list to Bus %s\n", wb->person.name, busId);
                        free(wb);
                    }
                    return;
                }
            }
            printf("BOOKING NOT FOUND\n");
            return;
        }
        temp = temp->next;
    }
    printf("No bus found with ID %s\n", busId);
}
void listPassengers(struct bus *head, char* busId) {
    struct bus *temp = head;
    while (temp) {
        if (strcmp(temp->busid, busId) == 0) {
            printf("Passengers in Bus %s:\n", busId);
            for (int i = 0; i < temp->passengerCount; i++) {
                printf("   %s | %s | %s -> %s\n",
                       temp->people[i].name,
                       temp->people[i].mobileno,
                       temp->people[i].boarding_point,
                       temp->people[i].dropping_point);
            }
            return;
        }
        temp = temp->next;
    }
    printf("No bus found with ID %s\n", busId);
}

void countBookings(struct bus *head, char* busId) {
    int count = 0;
    struct booking *curr = waitHead;
    while (curr) {
        if (strcmp(curr->busId, busId) == 0) count++;
        curr = curr->next;
    }
    printf("Waiting list for Bus %s: %d passengers\n", busId, count);
}

int main(){
    struct bus *head1 = NULL;
    int n;
    printf("Add Number of Buses: ");
    scanf("%d", &n);
    addBus(head1, n);
    int choice;
    do {
        printf("\n1. Display Buses\n2. Book Ticket\n3. Cancel Ticket\n4. List Passengers\n5. Count Waiting List\n6. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayBuses(head1);
                break;

            case 2:
                BookTicket(head1);
                break;

            case 3: {   
                char busid[20], mobile[11];
                printf("Enter The Bus ID to Cancel Ticket: ");
                scanf("%s", busid);
                printf("Enter The Mobile Number: ");
                scanf("%s", mobile);
                CancelTicket(head1, busid, mobile); 
                break;
            }

            case 4: {   
                char busid[20];
                printf("Enter The Bus ID: ");
                scanf("%s", busid);
                listPassengers(head1, busid);
                break;
            }

            case 5: {   
                char busid[20];
                printf("Enter The Bus ID: ");
                scanf("%s", busid);
                countBookings(head1, busid);
                break;
            }

            case 6:
                printf("Program Terminated.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 6);

    return 0;
}



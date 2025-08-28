#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bookings.h"

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

void addBus(struct bus **head1, int n) {
    for (int i = 0; i < n; i++) {
        struct bus *newnode = (struct bus*)malloc(sizeof(struct bus));
        if (!newnode) {
            printf("Memory allocation failed!\n");
            return;
        }

        printf("Enter bus id: ");
        scanf("%s", newnode->busid);
        if (!isValidBusId(newnode->busid)) {
            printf("Invalid bus ID format.\n");
            free(newnode);
            i--; 
            continue;
        }

        printf("Enter driver name: ");
        scanf("%s", newnode->driver);
        printf("Enter capacity (<=10): ");
        scanf("%d", &newnode->capacity);
        if(newnode->capacity > 10){
            printf("Capacity too large!\n");
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

        if (*head1 == NULL) {
            *head1 = newnode;  
        } else {
            struct bus *temp = *head1;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newnode;
        }

        printf("Bus %s added successfully!\n", newnode->busid);
    }
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
                enqueueWaiting(p, temp->busid);
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
                    temp->isFull = 0; 
                    printf("Ticket cancelled for mobile number %s in Bus %s\n", mobile, busId);

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

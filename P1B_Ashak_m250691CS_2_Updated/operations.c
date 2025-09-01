#include <stdio.h>
#include <string.h>
#include "operations.h"
#include "bookings.h"

extern struct booking *waitHead;

void displayBuses(struct bus *head) {
    if (!head) {
        printf("No buses available.\n");
        return;
    }
    struct bus *temp = head;
    while (temp != NULL) {
        printf("%s,%d,%s,%s,%s\n",
       temp->busid, temp->capacity, temp->driver,
       temp->boarding_point, temp->dropping_point);
    }
}

void listPassengers(struct bus *head, char* busId) {
    struct bus *temp = head;
    while (temp) {
        if (strcmp(temp->busid, busId) == 0) {
            for (int i = 0; i < temp->passengerCount; i++) {
                printf("%s,%s,%s,%s\n",
                       temp->people[i].name,
                       temp->people[i].mobileno,
                       temp->people[i].boarding_point,
                       temp->people[i].dropping_point);
            }
            return;
        }
        temp = temp->next;
    }
}

void countBookings(struct bus *head, char* busId) {
    int count = 0;
    struct booking *curr = waitHead;
    while (curr) {
        if (strcmp(curr->busId, busId) == 0) count++;
        curr = curr->next;
    }
    printf("%d\n",count);
}

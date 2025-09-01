#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "bookings.h"

void displayBuses(struct bus *head);
void listPassengers(struct bus *head, char* busId);
void countBookings(struct bus *head, char* busId);

#endif

#include <stdio.h>
#include "bookings.h"
#include "operations.h"

int main() {
    struct bus *head1 = NULL;
    int n;
    scanf("%d", &n);
    addBus(&head1, n);
    displayBuses(head1);
    char choice;
    int value=1;
    do {
        
        scanf(" %c", &choice);
        
        switch (choice) {
            case 'a':
                addBus(&head1,value);
                break;
            case 'b':
                BookTicket(head1);
                break;
            case 'c': {   
                char busid[20], mobile[11];
                scanf(" %[^,],%s",busid,mobile);
                CancelTicket(head1, busid, mobile); 
                break;
            }
            case 'l': {   
                char busid[20];
                scanf(" %s", busid);
                listPassengers(head1, busid);
                break; 
            }
            case 'k': {   
                char busid[20];
                scanf(" %s", busid);
                countBookings(head1, busid);
                break;
            }
            case 'e':
                printf("Program Terminated\n");
                break;
            default:
                break;
        }
    } while (choice != 'e');

    return 0;
}

#include <stdio.h>
#include "bookings.h"
#include "operations.h"

int main() {
    struct bus *head1 = NULL;
    int n;
    printf("Add Number of Buses: ");
    scanf("%d", &n);
    addBus(&head1, n);

    int choice;
    int value=1;
    do {
        printf("\n1. Display Buses\n2. Book Ticket\n3. Cancel Ticket\n4. List Passengers\n5. Count Waiting List \n6.Add Bus\n7. Exit\nEnter choice: ");
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
                addBus(&head1,value);
                break;
            case 7:
                printf("Program Terminated.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 7);

    return 0;
}

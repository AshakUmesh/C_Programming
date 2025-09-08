#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *head = NULL;

void insertnode(int num) {
    for (int i = 0; i < num; i++) {
        int value;
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &value);

        struct node *new = malloc(sizeof(struct node));
        new->data = value;
        new->next = NULL;

        if (head == NULL) {
            head = new;
        } else {
            struct node *temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new;
        }
    }
}

void printnode() {
    struct node *temp = head;
    if (temp == NULL) {
        printf("Linked List Empty\n");
        return;
    }
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void insertBegin() {
    int value;
    printf("Enter value to insert at beginning: ");
    scanf("%d", &value);

    struct node *new = malloc(sizeof(struct node));
    new->data = value;
    new->next = head;
    head = new;
}

void insertposition() {
    int pos, value;
    printf("Enter position (0 for beginning): ");
    scanf("%d", &pos);
    printf("Enter value: ");
    scanf("%d", &value);

    struct node *new = malloc(sizeof(struct node));
    new->data = value;
    new->next = NULL;

    if (pos == 0) {
        new->next = head;
        head = new;
        return;
    }

    struct node *temp = head;
    for (int i = 0; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Invalid position!\n");
        free(new);
        return;
    }

    new->next = temp->next;
    temp->next = new;
}

void deleteposition(){
    int pos;
    printf("Enter position (0 for beginning): ");
    scanf("%d", &pos);
    if(head == NULL){return;}
     if (pos == 0) {
        struct node *temp = head;
        head = head->next;
        free(temp);
        printf("Deleted node at position 0\n");
        return;
    }
    struct node *temp = head;
    for (int i = 0; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
     if (temp == NULL || temp->next == NULL) {
        printf("Invalid position!\n");
        return;
    }
    struct node *delete = temp->next;
    temp->next = delete->next;
    free(delete);

}

void reverselist(){
    if(head==NULL){return;}
    struct node * prev = NULL;
    struct node * curr = head;
    struct node * next = NULL;
    while (curr != NULL) {
        next = curr->next;   
        curr->next = prev;  
        prev = curr;         
        curr = next;        
    }
    head = prev; 
}

void reverselistprint_recursion(struct node * head){
    if(head==NULL){return;}
    reverselistprint_recursion(head->next);
    printf("%d->",head->data);
}


int main() {
    int choice, num;
    printf("Enter total number of entries: ");
    scanf("%d", &num);
    insertnode(num);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Print Nodes\n");
        printf("2. Insert at Beginning\n");
        printf("3. Insert at Position\n");
        printf("4. Delete at Position\n");
        printf("5. Reverse The String\n");
         printf("6. Reverse The String using Recurssion\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printnode();
                break;
            case 2:
                insertBegin();
                break;
            case 3:
                insertposition();
                break;
            case 4:
                deleteposition();
                break;
            case 5:
                reverselist();
                break;
            case 6:
                reverselistprint_recursion(head);
                break;
            case 7:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}

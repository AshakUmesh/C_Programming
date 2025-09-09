#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node * next;
    struct node * prev;
};

struct node * head = NULL;
struct node * tail = NULL;

void printnode(){
    if(head==NULL){printf("Linked List Empty\n");return;}
    struct node * temp = head;
    while(temp!=NULL){printf("%d->",temp->data); temp = temp->next;}
    printf("NULL\n");
}

void insertBegin(){
    int value;
    struct node * new = malloc(sizeof(struct node));
    printf("Enter the data\n");
    scanf("%d",&value);
    new->data = value;
    new->next=NULL;
    new->prev=NULL;
    if(head==NULL){head=new;tail=new;}
    else{
    new->next=head;
    head->prev=new;
    head=new;
    }
}
void insertposition() {
    int value, pos;
    printf("Enter the data: ");
    scanf("%d", &value);
    printf("Enter the position to insert (1-based index): ");
    scanf("%d", &pos);
    struct node *new = malloc(sizeof(struct node));
    if (new == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    new->data = value;
    new->next = NULL;
    new->prev = NULL;
    if (head == NULL) {
        if (pos != 1) {
            printf("Invalid position! List is empty, only position 1 is valid.\n");
            free(new);
            return;
        }
        head = tail = new;
        return;
    }
    if (pos == 1) {
        new->next = head;
        head->prev = new;
        head = new;
        return;
    }
    struct node *temp = head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Invalid position!\n");
        free(new);
        return;
    }
    if (temp->next == NULL) {
        temp->next = new;
        new->prev = temp;
        tail = new;
    }
    else {
        new->next = temp->next;
        new->prev = temp;
        temp->next->prev = new;
        temp->next = new;
    }
}

void deleteposition() {
    int pos;
    printf("Enter the position: ");
    scanf("%d", &pos);
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    struct node *temp = head;
    if (pos == 1) {
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        } else {
            tail = NULL; 
        }
        free(temp);
        return;
    }
    for (int i = 1; i < pos && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Invalid position!\n");
        return;
    }
    if (temp->next == NULL) {
        tail = temp->prev;
        tail->next = NULL;
        free(temp);
    }
    else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
    }
}


void reverselist(){
    if(tail==NULL){return;}
    struct node * temp=tail;
    while(temp!=NULL){
        printf("%d->",temp->data);
        temp=temp->prev;
    }
    printf("NULL\n");
}
void insertnode(int num){
    struct node * temp = head;
    int value;
    for(int i=0;i<num;i++){
        struct node * new = malloc(sizeof(struct node));
        printf("Enter the data\n");
        scanf("%d",&value);
        new->data = value;
        new->next=NULL;
        new->prev=NULL;
        if(head==NULL){head=new;tail=new;}
       else{
        tail->next=new;
        new->prev=tail;
        tail=new;
    }
}
}

int main(){
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
        printf("5. Reverse print Linked List \n");
        printf("6. Exit\n");
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
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}






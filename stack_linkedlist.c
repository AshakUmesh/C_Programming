#include <stdio.h>
#include <stdlib.h>
struct node{
    int data;
    struct node * next;
};
struct node * head = NULL;
struct node * tail = NULL;

void push(){
    int value;
    struct node * new = malloc(sizeof(struct node));
    printf("Enter the value ");
    scanf("%d",&value);
    new->data=value;
    new->next=NULL;
    if(head==NULL){head=new;}
    else{
       new->next=head;
       head=new;
    }
}

void pop() {
    if (head == NULL) { 
        printf("Stack Empty\n"); 
        return; 
    }
    if (head == tail) {
        printf("Popped %d\n", head->data);
        free(head);
        head = tail = NULL;
        return;
    }
    struct node *temp = head;
    printf("Popped %d\n", head->data);
    head=head->next;
    free(temp);
}


void print(){
    if(head==NULL){printf("Stack Empty\n");}
    else{
        struct node *temp=head;
        while(temp!=NULL){
            printf("%d\n",temp->data);
            temp=temp->next;
        }
    }
}



void main(){
    int choice;
    int start=1;
    while(start){
        printf("1.Push\n2.Pop\n3.Print\n4.Exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:push();
                break;
            case 2:pop();
                break;
            case 3:print();
                break;
            case 4:start=0;
                break;
            default:printf("Invalid Entry\n");
        }

    }
}
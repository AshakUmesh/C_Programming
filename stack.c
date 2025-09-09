#include <stdio.h>
#include <stdlib.h>
int stack[50];
int top=-1;
void push(){
    int value;
    ++top;
    if(top>=50){printf("stack is full\n");}
    else{
        printf("Enter the value ");
        scanf("%d",&value);
        stack[top]=value;
    }
}

void pop(){
    if(top==-1){printf("Stack Empty\n");}
    else{
    printf("Popped %d\n",stack[top]);
    top--;}
}

void print(){
    if(top==-1){print("Stack Empty\n");}
    for(int i=0;i<=top;i++){
        printf("%d \n",stack[i]);
    }
}

int main(){
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
            default:printf("Invalid Entry");
        }

    }



}
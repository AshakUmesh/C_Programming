#include <stdio.h>
#include <stdlib.h>
#include<string.h>
char stack[50];
int top=-1;

void print(char * reverse){
    printf("%s \n",reverse);   
}

void push(char * string){
    for(int i = 0;i<strlen(string);i++)
    {
    stack[++top]=string[i];
    }
}


void pop(){
    char reverse[50];
    int i=0;
    if(top==-1){printf("Stack Empty\n");return;}
    while(top != -1){
    reverse[i++]=stack[top--];    
}
    reverse[i]='\0';
    print(reverse);

}



int main(){
    char string[50];
    printf("Enter the string ");
    fgets(string,sizeof(string),stdin);
    push(string);
    pop();
    }




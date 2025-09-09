#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

int top = -1;
int stack[50];
void push(int num){
    stack[++top]=num;
}

int pop(){
   return stack[top--];
}

int  evaluatePostfix(char * exp){
    for(int i=0;exp[i]!='\0';i++){
        char c = exp[i];

        if(c == ' '){continue;}

        if(isdigit(c)){
            int value;
            value=atoi(&c);
            push(value);
        }
        else {
            int value1= pop();
            int value2=pop();
            if(c=='*'){push(value1*value2);}
            if(c=='+'){push(value1+value2);}
            if(c=='-'){push(value2-value1);}
            if(c=='/'){push(value2/value1);}
        }
    }
    return pop();
}

int main(){
    char exp[] = "2 3 + 4 *";
    printf("Postfix Evaluation: %d\n", evaluatePostfix(exp));
   

}
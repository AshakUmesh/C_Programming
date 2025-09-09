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

int evaluatePrefix(char *exp) {
    int len = strlen(exp);

    for (int i = len - 1; i >= 0; i--) {
        char c = exp[i];

        if (c == ' ') continue;

        if (isdigit(c)) {
            push(c - '0');
        } else {
            int val1 = pop();
            int val2 = pop();
            switch (c) {
                case '+': push(val1 + val2); break;
                case '-': push(val1 - val2); break;
                case '*': push(val1 * val2); break;
                case '/': push(val1 / val2); break;
            }
        }
    }
    return pop();
}


int main(){
    char prefixExp[]  = "* + 2 3 4";
    char exp[] = "2 3 + 4 *";
    printf("Postfix Evaluation: %d\n", evaluatePostfix(exp));
    top = -1;
    printf("Prefix Evaluation: %d\n", evaluatePrefix(prefixExp));

}
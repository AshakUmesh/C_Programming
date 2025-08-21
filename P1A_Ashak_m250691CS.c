#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Bus{
    char registration_no[11];
    char driver_name[20];
    char route[20];
    int capacity;
    double fuel_level;
    double mileage;
};

char *getDriver(struct Bus *n[], char name[], int num);
int main(int argc, char *argv[]) {
    int num=0,i=0;
    printf("File Name: %s\n", argv[1]);
    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    
    
    char buffer[200];
    while(fgets(buffer, sizeof(buffer), fp)) {
        num++;
    }
    printf("Total Records: %d\n", num);
    rewind(fp);
    
    struct Bus *ptrs[num]; 
    char first[25], last[25];
    while(fgets(buffer,sizeof(buffer), fp)) {
       ptrs[i] = malloc(sizeof(struct Bus));
       char *tokens[10];   
       int tokCount = 0;
       char *tok = strtok(buffer, " \t\n");   
    while (tok && tokCount < 10) {
    tokens[tokCount++] = tok;         
    tok = strtok(NULL, " \t\n");  
    }    
    if(tokCount==6){
        strcpy(ptrs[i]->registration_no, tokens[0]); 
        strcpy(ptrs[i]->driver_name, tokens[1]);     
        strcpy(ptrs[i]->route, tokens[2]);           
        ptrs[i]->capacity = atoi(tokens[3]);         
        ptrs[i]->fuel_level = atof(tokens[4]);       
        ptrs[i]->mileage = atof(tokens[5]);
    }
    else if(tokCount==7){
        strcpy(ptrs[i]->registration_no, tokens[0]);
        snprintf(ptrs[i]->driver_name, sizeof(ptrs[i]->driver_name),
                 "%s %s", tokens[1], tokens[2]);
        strcpy(ptrs[i]->route, tokens[3]);
        ptrs[i]->capacity = atoi(tokens[4]);
        ptrs[i]->fuel_level = atof(tokens[5]);
        ptrs[i]->mileage = atof(tokens[6]);
    }
    else {
        printf("Invalid line: %s\n", buffer);
        free(ptrs[i]);
        continue;
    }
    printf("Saved : %s | %s | %s | %d | %.2f | %.2f\n",
           ptrs[i]->registration_no,
           ptrs[i]->driver_name,
           ptrs[i]->route,
           ptrs[i]->capacity,
           ptrs[i]->fuel_level,
           ptrs[i]->mileage);

    i++;

    }

    fclose(fp);

    printf("Enter the registration number to search: ");
    scanf("%s",buffer);
    char *driver = getDriver(ptrs, buffer, num);
    printf("Name of the driver: %s\n", driver);


    return 0;    
}


char *getDriver(struct Bus *n[], char name[], int num) {
    for (int i = 0; i < num; i++) {
        if (strcmp(n[i]->registration_no, name) == 0) {
            return n[i]->driver_name;
        }
    }
    return "Not Found";
}
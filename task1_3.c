#include<stdio.h>
#include<string.h>
typedef struct {
    char registration_no[10];
    char driver_name[20];
    char route[20];
    int capacity;
    double fuel_level;
    double mileage;
} Bus;

void createFleet(Bus data[], int num);
void getDriver(Bus data[],char registrationno[],int num);
void createFile(Bus data[],int num);

void main(){		
	int num;
    printf("Enter number of buses: ");
    scanf("%d", &num);
	Bus data[num];
	createFleet(data, num);
	printf("enter the registration number of bus to know driver details");
	char res[20];
	scanf("%s",res);
	getDriver(data,res,num);
	createFile(data,num);
	char buffer[200];
	FILE *fp=fopen("File.txt","r");
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    printf("%s", buffer);
	}
}

void createFleet(Bus data[], int num) {
for(int i=0;i<num;i++){
	printf("\nEnter details for Bus %d:\n", i+1);
    printf("Registration No: ");
	scanf("%s", data[i].registration_no);
	printf("Driver Name: ");
	scanf("%s", data[i].driver_name);
	printf("Route: ");
	scanf("%s", data[i].route);
	printf("Capacity: ");
    scanf("%d", &data[i].capacity);
    printf("Fuel Level (litres): ");
    scanf("%lf", &data[i].fuel_level);
    printf("Mileage (km/l): ");
    scanf("%lf", &data[i].mileage);
	
}	
}

void getDriver(Bus data[],char registrationno[],int num){
	for(int i=0;i<num;i++){
	if(strcmp(data[i].registration_no, registrationno) == 0){
		printf("%s",data[i].driver_name);
	}
	else{
		printf("Registartion ID Invalid");
	}
	}
}

void createFile(Bus data[],int num){
	FILE *fp=fopen("File.txt","w");
	for(int i=0;i<num;i++){
	fprintf(fp,"%s,%s,%s,%d,%f,%f\n",data[i].registration_no,data[i].driver_name,data[i].route,data[i].capacity,data[i].fuel_level,data[i].mileage);
	}
	fclose(fp);
}
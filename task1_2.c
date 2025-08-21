#include<stdio.h>
#include<string.h>
void main(){
int n, i;
printf("Enter the number of buses: ");
scanf("%d", &n);
int busIDs[n];

printf("Enter the 4-digit vehicle ID for each bus:\n");
for (i = 0; i < n; i++) {
printf("Bus %d ID: ", i + 1);
scanf("%d", &busIDs[i]);
if (busIDs[i] < 1000 || busIDs[i] > 9999) {
printf("Invalid ID! Must be 4 digits.\n");
i--;}
}
printf("\nFleet Vehicle IDs:\n");
for (i = 0; i < n; i++) {
printf("Bus %d: %d\n", i + 1, busIDs[i]);
}
char code[]="KA05AB";
printf("%s",code);

char id[4];
char vechilecode[n][10];
for(int i=0;i<n;i++){
	 sprintf(vechilecode[i], "%s%d", code, busIDs[i]);
}

for(int i=0;i<n;i++){
	printf("%s",vechilecode[i]);
}



}
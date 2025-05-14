#include<stdio.h>
#include<windows.h>
#include<string.h>

#define accntNumLength 10
#define MAX 100


typedef struct {
    float nKilowatt;
    float nHours;
    float kwperhr;
} KWperHr;

typedef struct {
    char fname[30];
    char lname[30];
} NAME;

typedef struct {
    char street[50];
    char city[30];
    char zip[10];
} ADDR;

typedef struct{
	int Month;
	int Year;
	int day;
}DATES;


typedef struct {
	int prevbalance;
    int Billcode;
    char accntNum[accntNumLength + 1];
    NAME accntName;
    ADDR address;
    DATES dates;
    KWperHr previousReading;
    KWperHr currentReading;
    float bill;
} ELEXBILL;


ELEXBILL getInput();

void deleteRecord(ELEXBILL bills[], int *n);
void edito(ELEXBILL bills[], int n);  
void display(ELEXBILL e);	
void printAll(ELEXBILL bills[], int n);
int searchIndex(ELEXBILL bills[], int n, char accNum[]);
void create(ELEXBILL bills[], int *n);
void userSearch(ELEXBILL bills[], int n);
void CheckBalance(ELEXBILL bills[], int n);
void searchBillCode(ELEXBILL bills[], int n);
void displayPowerMeteringInfo(ELEXBILL bills[], int n);
void saveToFile(ELEXBILL bills[], int n);
int loadFromFile(ELEXBILL bills[]);


int main() {
    ELEXBILL bills[MAX];
    int n = 0;
    int choice;
    
    n = loadFromFile(bills);

    do {
        printf("\n--- Electricity Bill System ---\n");
        printf("1. Admin Mode (Create Record)\n");
        printf("2. Search for an Account\n");
        printf("3. Print All Accounts\n");
        printf("4. Edit Account\n");
        printf("5. Delete Account\n");
        printf("6. Search Bill Code\n");
        printf("7. Print Payment Details\n");
        printf("8. Check Balance\n");
        printf("9. Save Records to File\n");
        
        
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            	system("cls");
                create(bills, &n);
                break;
            case 2:
            	system("cls");
                userSearch(bills, n);
                break;
            case 3:
            	system("cls");
                printAll(bills, n);
                break;
            case 4:
            	system("cls");
                edito(bills, n);
                break;
            case 5:
            	system("cls");
                deleteRecord(bills, &n);
                break;
            case 6:
            	system("cls");
                searchBillCode(bills, n);
                break;
            case 7:
            	system("cls");
                displayPowerMeteringInfo(bills,n);
                break;
			case 8:
				system("cls");
				CheckBalance(bills, n);
				break;
			case 9:
				system("cls");
			    saveToFile(bills, n);
			    break;
            case 0:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);
	
	saveToFile(bills, n);
	
    return 0;
}

ELEXBILL getInput() {
    ELEXBILL e;

    printf("Enter Billcode: ");
    scanf("%d", &e.Billcode);

    printf("Enter Account Number: ");
    scanf("%s", e.accntNum);

    printf("Enter First Name: ");
    scanf("%s", e.accntName.fname);

    printf("Enter Last Name: ");
    scanf("%s", e.accntName.lname);
    
    printf("Enter Current Month, day and year(in mm/dd/yyyy format spaced): ");
    scanf("%d %d %d", &e.dates.Month, &e.dates.day, &e.dates.Year);

    printf("Enter Street: ");
    scanf(" %[^\n]", e.address.street);

    printf("Enter City: ");
    scanf("%s", e.address.city);

    printf("Enter Zip Code: ");
    scanf("%s", e.address.zip);
    
    printf("Enter Previous Balance if Fully paid input 0: ");
    scanf("%d", &e.prevbalance);

    printf("Enter Previous Reading (kWh and hours): ");
    scanf("%f %f", &e.previousReading.nKilowatt, &e.previousReading.nHours);
    e.previousReading.kwperhr = e.previousReading.nKilowatt / e.previousReading.nHours;

    printf("Enter Current Reading (kWh and hours): ");
    scanf("%f %f", &e.currentReading.nKilowatt, &e.currentReading.nHours);
    e.currentReading.kwperhr = e.currentReading.nKilowatt / e.currentReading.nHours;

    e.bill = (e.currentReading.nKilowatt - e.previousReading.nKilowatt) * 10.50;

    return e;
}

void display(ELEXBILL e) {
	
	
    printf("\n--- Electricity Bill Details ---\n");
    printf("Bill Code: %d\n", e.Billcode);
    printf("Account Number: %s\n", e.accntNum);
    printf("Name: %s %s\n", e.accntName.fname, e.accntName.lname);
    printf("Recorded on:");
    switch(e.dates.Month){
    	case 1:
    		printf(" January ");
    		break;
    	case 2:
    		printf(" February ");
    		break;
    	case 3:
    		printf(" March ");
    		break;
    	case 4:
    		printf(" April ");
    		break;
    	case 5:
    		printf(" May ");
    		break;
    	case 6:
    			printf(" June ");
    		break;
    	case 7:
    			printf(" July ");
    		break;
    	case 8:
    			printf(" August ");
    		break;
    	case 9:
    			printf(" September ");
    		break;
    	case 10:
    			printf(" October ");
    		break;
    	case 11:
    			printf(" November ");
    		break;
    	case 12:
    			printf(" December ");
    		break;
    	default:
    		printf("??????");
    		break;
	}
    printf("/ %d / %d\n", e.dates.day, e.dates.Year);
    printf("Address: %s, %s, %s\n", e.address.street, e.address.city, e.address.zip);
    printf("Previous Reading: %.2f kWh / %.2f hrs = %.2f kw/hr\n", e.previousReading.nKilowatt, e.previousReading.nHours, e.previousReading.kwperhr);
    printf("Current Reading: %.2f kWh / %.2f hrs = %.2f kw/hr\n", e.currentReading.nKilowatt, e.currentReading.nHours, e.currentReading.kwperhr);
    printf("Total Bill: PHP %.2f\n", e.bill);
}

void printAll(ELEXBILL bills[], int n) {
    if (n == 0) {
        printf("No records to show.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        display(bills[i]);
    }
}

int searchIndex(ELEXBILL bills[], int n, char accNum[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(bills[i].accntNum, accNum) == 0) {
            return i;
        }
    }
    return -1;
}

void userSearch(ELEXBILL bills[], int n) {
    char accNum[accntNumLength + 1];
    printf("Enter Account Number to search: ");
    scanf("%s", accNum);

    int index = searchIndex(bills, n, accNum);
    if (index != -1) {
        display(bills[index]);
    } else {
        printf("Account not found.\n");
    }
}

int searchByBillCode(ELEXBILL bills[], int n, int billCode) {
    for (int i = 0; i < n; i++) {
        if (bills[i].Billcode == billCode) {
            return i;
        }
    }
    return -1;
}

void searchBillCode(ELEXBILL bills[], int n) {
    int billCode;
    printf("Enter Bill Code to search: ");
    scanf("%d", &billCode);

    int index = searchByBillCode(bills, n, billCode);
    if (index != -1) {
        display(bills[index]);
    } else {
        printf("Bill Code not found.\n");
    }
}

void deleteRecord(ELEXBILL bills[], int *n){
	
    if (*n == 0) {
	    printf("No records to delete.\n");
	    return;
	}

	char accNum[accntNumLength + 1];
	printf("Enter Account Number to delete: ");
	scanf("%s", accNum);
	
	int index = searchIndex(bills, *n, accNum);
	
	if (index == -1) {
	    printf("Account not found.\n");
	    return;
	}
	
	for (int i = index; i < *n - 1; i++) {
		bills[i] = bills[i + 1];
	}
	
	(*n)--;
	printf("Account successfully deleted.\n");
}

void displayPowerMeteringInfo(ELEXBILL bills[], int n) {
    char lookfor[accntNumLength+1];

    if (n == 0) {
        printf("No records available.\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%s", lookfor);

    int index = searchIndex(bills, n, lookfor);
    if (index != -1) {
        system("cls");
        printf("\n=========================================================\n");
        printf("|             POWER METERING INFORMATION               \n");
        printf("=========================================================\n");
        printf("| Account Number   : %-20s \n", bills[index].accntNum);
        printf("| Account Name     : %-10s %-10s  \n", bills[index].accntName.fname, bills[index].accntName.lname);
        printf("| Address         : %-15s, %-10s, %-6s \n", 
               bills[index].address.street, 
               bills[index].address.city, 
               bills[index].address.zip);
        printf("=========================================================\n");
        printf("| Previous Reading                                      \n");
        printf("| Kilowatt       : %-10.2f     Hours   : %-10.2f 		\n", bills[index].previousReading.nKilowatt, bills[index].previousReading.nHours);
        printf("| kW per hr      : %-10.2f                     			\n", bills[index].previousReading.kwperhr);
        printf("=========================================================\n");
        printf("| Current Reading                                       \n");
        printf("| Kilowatt       : %-10.2f     Hours   : %-10.2f 		\n", bills[index].currentReading.nKilowatt, bills[index].currentReading.nHours);
        printf("| kW per hr      : %-10.2f                     			\n", bills[index].currentReading.kwperhr);
        printf("=========================================================\n");
        printf("| Total Bill     : PHP %-10.2f                          \n", bills[index].bill);
        printf("=========================================================\n");
    } else {
        printf("Account not found.\n");
    }
}


void edito(ELEXBILL bills[], int n){
    ELEXBILL changes;
    char lookfor[accntNumLength+1];
    char cont;
    int choices;
    if (n == 0) {
        printf("No records to edit.\n");
        return;
    }

    do {
       printf("Enter Account Number : ");
       scanf("%s", lookfor);


       int index = searchIndex(bills, n, lookfor);
       if (index != -1) {

        printf("What values would you like to change?");
        printf("\n\n1. BILLCODE"); 
        printf("\n\n2. ACCOUNT NUMBER");
        printf("\n\n3. ACCOUNT NAME");
        printf("\n\n4. STREET"); 
        printf("\n\n5. CITY");
        printf("\n\n6. ZIP CODE"); 
        printf("\n\n7. PREVIOUS READING");
        printf("\n\n8. CURRENT READING \n :");
        scanf(" %d", &choices);
        switch (choices) {
            case 1:
            	system("cls");
                printf("Enter New Billcode: ");
                scanf("%d", &changes.Billcode);
                bills[index].Billcode = changes.Billcode;

                break;
            case 2:
            	system("cls");
                printf("Enter New Account Number: ");
                scanf("%s", changes.accntNum);

                strncpy(bills[index].accntNum, changes.accntNum, accntNumLength);
                bills[index].accntNum[accntNumLength - 1] = '\0';
              
                break;
            case 3:
            	system("cls");
                printf("Enter First Name: ");
                scanf("%s", changes.accntName.fname);
                printf("Enter Last Name: ");
                scanf("%s", changes.accntName.lname);

                strncpy(bills[index].accntName.fname, changes.accntName.fname, accntNumLength);
                bills[index].accntName.fname[accntNumLength - 1] = '\0';

                strncpy(bills[index].accntName.lname, changes.accntName.lname, accntNumLength);
                bills[index].accntName.lname[accntNumLength - 1] = '\0';
             
                break;
            case 4:
            	system("cls");
                printf("Enter Street: ");
                scanf("%s", changes.address.street);

                strncpy(bills[index].address.street, changes.address.street, accntNumLength);
                bills[index].address.street[accntNumLength - 1] = '\0';
                
                break;
            case 5:
            	system("cls");
                printf("Enter City: ");
                scanf("%s", changes.address.city);

                strncpy(bills[index].address.city, changes.address.city, accntNumLength);
                bills[index].address.city[accntNumLength - 1] = '\0';
              
                break;
            case 6:
            	system("cls");
                printf("Enter ZIPCODE: ");
                scanf("%s", changes.address.zip);

                strncpy(bills[index].address.zip, changes.address.zip, accntNumLength);
                bills[index].address.zip[accntNumLength - 1] = '\0';
             
                break;
            case 7:
                system("cls");
                printf("Enter Previous Reading(both kwh and h spaced): ");
                scanf("%f %f", &changes.previousReading.nKilowatt, &changes.previousReading.nHours);
                changes.previousReading.kwperhr = changes.previousReading.nKilowatt / changes.previousReading.nHours;

                bills[index].previousReading.nHours = changes.previousReading.nHours;
                bills[index].previousReading.nKilowatt = changes.previousReading.nKilowatt;
                bills[index].previousReading.kwperhr = changes.previousReading.kwperhr;
                bills[index].bill = (bills[index].currentReading.nKilowatt - bills[index].previousReading.nKilowatt) * 10.50;

                break;
            case 8:
                system("cls");
                printf("Enter Current Reading(both kwh and h spaced): ");
                scanf("%f %f", &changes.currentReading.nKilowatt, &changes.currentReading.nHours);
                changes.currentReading.kwperhr = changes.currentReading.nKilowatt / changes.currentReading.nHours;

                bills[index].currentReading.nHours = changes.currentReading.nHours;
                bills[index].currentReading.nKilowatt = changes.currentReading.nKilowatt;
                bills[index].currentReading.kwperhr = changes.currentReading.kwperhr;
                bills[index].bill = (bills[index].currentReading.nKilowatt - bills[index].previousReading.nKilowatt) * 10.50;

                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

       } else {
           printf("Account not found.\n");
       }

        printf("Change another value from the record? (y/n): ");
        scanf(" %c", &cont);
    } while (cont == 'y' || cont == 'Y');

}

void CheckBalance(ELEXBILL bills[], int n){
	char accNum[accntNumLength + 1];
    printf("Enter Account Number to check balance: ");
    scanf("%s", accNum);

    int index = searchIndex(bills, n, accNum);
    if (index != -1 && bills[index].prevbalance == 0) {
        printf("Congrats you have no DUE PAYMENT!\n");
    } else if(bills[index].prevbalance > 0){
    	printf("Warning you have a previous balance of: %d and new a balance of: %.2f, Please pay on time!\n", bills[index].prevbalance, bills[index].bill);
	} else {
        printf("Account not found.\n");
    }
}

void create(ELEXBILL bills[], int *n) {
    char cont;
    do {
        if (*n >= MAX) {
            printf("Maximum number of records reached.\n");
            return;
        }

        bills[*n] = getInput();
        (*n)++;
        saveToFile(bills, *n); 

        printf("Record added and saved. Add another? (y/n): ");
        scanf(" %c", &cont);
    } while (cont == 'y' || cont == 'Y');
}

void saveToFile(ELEXBILL bills[], int n) {
    FILE *fp = fopen("bills.dat", "wb");
    if (fp == NULL) {
        printf("Error saving data to file.\n");
        return;
    }

    fwrite(&n, sizeof(int), 1, fp);          
    fwrite(bills, sizeof(ELEXBILL), n, fp);    
    fclose(fp);
    printf("Records successfully saved to file.\n");
}

int loadFromFile(ELEXBILL bills[]) {
    FILE *fp = fopen("bills.dat", "rb");
    int n = 0;

    if (fp == NULL) {
        printf("No existing data file found. Starting fresh.\n");
        return 0;
    }

    fread(&n, sizeof(int), 1, fp);
    fread(bills, sizeof(ELEXBILL), n, fp);
    fclose(fp);

    printf("%d record(s) loaded from file.\n", n);
    return n;
}

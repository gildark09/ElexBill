#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX 100
#define accntNumLength 10

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

typedef struct {
    int Billcode;
    char accntNum[accntNumLength + 1];
    NAME accntName;
    ADDR address;
    KWperHr previousReading;
    KWperHr currentReading;
    float bill;
} ELEXBILL;

ELEXBILL getInput();
void display(ELEXBILL e);
void printAll(ELEXBILL bills[], int n);
int search(ELEXBILL bills[], int n, char accNum[]);
void adminMode(ELEXBILL bills[], int *n);
void userSearch(ELEXBILL bills[], int n);

int main() {
    ELEXBILL bills[MAX];
    int n = 0;
    int choice;

    do {
        printf("\n--- Electricity Bill System ---\n");
        printf("1. Admin Mode (Add Record)\n");
        printf("2. Search for an Account\n");
        printf("3. Print All Accounts\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            	system("cls");
                adminMode(bills, &n);
                break;
            case 2:
            	system("cls");
                userSearch(bills, n);
                break;
            case 3:
            	system("cls");
                printAll(bills, n);
                break;
            case 0:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

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

    printf("Enter Street: ");
    scanf(" %[^\n]", e.address.street);

    printf("Enter City: ");
    scanf("%s", e.address.city);

    printf("Enter Zip Code: ");
    scanf("%s", e.address.zip);

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

int search(ELEXBILL bills[], int n, char accNum[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(bills[i].accntNum, accNum) == 0) {
            return i;
        }
    }
    return -1;
}

void adminMode(ELEXBILL bills[], int *n) {
    char cont;
    do {
        bills[*n] = getInput();
        (*n)++;

        printf("Add another record? (y/n): ");
        scanf(" %c", &cont);
    } while (cont == 'y' || cont == 'Y');
}

void userSearch(ELEXBILL bills[], int n) {
    char accNum[accntNumLength + 1];
    printf("Enter Account Number to search: ");
    scanf("%s", accNum);

    int index = search(bills, n, accNum);
    if (index != -1) {
        display(bills[index]);
    } else {
        printf("Account not found.\n");
    }
}


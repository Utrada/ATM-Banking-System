/*
Name : Trada Utsav
Roll No : 2
Div : 1-MCA-A

---------------------
ATM Banking System
Features:
1. Admin Login
2. Create Account
3. View Accounts
4. Withdraw
5. Delete Acccount
6. Exit
-------------------------------
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

struct Account {
    long int  accNo;
    char name[50];
    float balance;
};

void createAccount();
void viewAccounts();
void deposit();
void withdraw();
void deleteAccount();
int login();
void menu();

void main() {
    int choice;
    clrscr();

    if (!login()) {
	printf("\nAccess Denied.\n");
	return;
    }

    while (1) {
	menu();
	printf("\nEnter your choice: ");
	scanf("%d", &choice);

	switch (choice) {
	    case 1: createAccount(); break;
	    case 2: viewAccounts(); break;
	    case 3: deposit(); break;
	    case 4: withdraw(); break;
	    case 5: deleteAccount(); break;
	    case 6:
		printf("\nThank you for using the ATM System!\n");
		printf("Press any key to continue...");
		getch();
		exit(0);
	    default: printf("Invalid choice. Try again.\n");
	}

	getch();
    }
}

int login() {
    char user[20], pass[20];
    printf("==== ATM SYSTEM LOGIN ====\n");
    printf("Username: ");
    scanf("%s", user);
    printf("Password: ");
    scanf("%s", pass);

    if (strcmp(user, "admin") == 0 && strcmp(pass, "1234") == 0) {
	printf("\nLogin Successful!\n");
	return 1;
    } else {
	printf("\nWrong credentials!\n");
	return 0;
    }
}

void menu() {
    clrscr();
    printf("====== ATM MAIN MENU ======\n");
    printf("1. Create Account\n");
    printf("2. View All Accounts\n");
    printf("3. Deposit Money\n");
    printf("4. Withdraw Money\n");
    printf("5. Delete Account\n");
    printf("6. Exit\n");
}

void createAccount() {
    struct Account acc;
    FILE *fp = fopen("atmdata.txt", "a");

    if (!fp) {
	printf("File error.\n");
	return;
    }

    printf("\nEnter Account Number: ");
    scanf("%ld", &acc.accNo);
    fflush(stdin);
    printf("Enter Account Holder Name: ");
    gets(acc.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fprintf(fp, "%ld|%s|%.2f\n", acc.accNo, acc.name, acc.balance);
    fclose(fp);
    printf("Account created successfully.\n");
}

void viewAccounts() {
    struct Account acc;
    FILE *fp = fopen("atmdata.txt", "r");

    if (!fp) {
	printf("No data found.\n");
	return;
    }

    printf("\nList of Accounts:\n");
    printf("---------------------------\n");

    while (fscanf(fp, "%ld|%[^|]|%f\n", &acc.accNo, acc.name, &acc.balance) == 3) {
	printf("Acc No: %ld\nName: %s\nBalance: %.2f\n", acc.accNo, acc.name, acc.balance);
	printf("---------------------------\n");
    }

    fclose(fp);
}

void deposit() {
    int accNo, found = 0;
    float amount;
    struct Account acc;
    FILE *fp = fopen("atmdata.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
	printf("File error.\n");
	return;
    }

    printf("Enter Account Number: ");
    scanf("%ld", &accNo);

    while (fscanf(fp, "%ld|%[^|]|%f\n", &acc.accNo, acc.name, &acc.balance) == 3) {
	if (acc.accNo == accNo) {
	    printf("Enter amount to deposit: ");
	    scanf("%f", &amount);
	    acc.balance += amount;
	    found = 1;
	}
	fprintf(temp, "%ld|%s|%.2f\n", acc.accNo, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);

    remove("atmdata.txt");
    rename("temp.txt", "atmdata.txt");

    if (found)
	printf("Deposit successful.\n");
    else
	printf("Account not found.\n");
}

void withdraw() {
    int accNo, found = 0;
    float amount;
    struct Account acc;
    FILE *fp = fopen("atmdata.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
	printf("File error.\n");
	return;
    }

    printf("Enter Account Number: ");
    scanf("%ld", &accNo);

    while (fscanf(fp, "%ld|%[^|]|%f\n", &acc.accNo, acc.name, &acc.balance) == 3) {
	if (acc.accNo == accNo) {
	    printf("Enter amount to withdraw: ");
	    scanf("%f", &amount);

	    if (amount > acc.balance) {
		printf("Insufficient balance.\n");
	    } else {
		acc.balance -= amount;
		printf("Withdrawal successful. Remaining balance: %.2f\n", acc.balance);
	    }

	    found = 1;
	}
	fprintf(temp, "%ld|%s|%.2f\n", acc.accNo, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);

    remove("atmdata.txt");
    rename("temp.txt", "atmdata.txt");

    if (!found)
	printf("Account not found.\n");
}

void deleteAccount() {
    int accNo, found = 0;
    struct Account acc;
    FILE *fp = fopen("atmdata.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
	printf("File error.\n");
	return;
    }

    printf("Enter Account Number to delete: ");
    scanf("%ld", &accNo);

    // Read each record from file
    while (fscanf(fp, "%ld|%[^|]|%f\n", &acc.accNo, acc.name, &acc.balance) == 3) {
	if (acc.accNo == accNo) {
	    found = 1; // Mark account as found but do not write it to temp file
	} else {
	    fprintf(temp, "%ld|%s|%.2f\n", acc.accNo, acc.name, acc.balance); // Keep other records
	}
    }

    fclose(fp);
    fclose(temp);

    remove("atmdata.txt");           // Delete old file
    rename("temp.txt", "atmdata.txt"); // Rename temp to original

    if (found)
	printf("Account deleted successfully.\n");
    else
	printf("Account not found.\n");
}

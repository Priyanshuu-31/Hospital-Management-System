#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "billing.h"
#include "doctor.h"
#include "consoleui.h"

#define MAX_BILLS 100

struct BillStack {
    struct Bill bills[MAX_BILLS];
    int top;
};

static struct BillStack billStack = {.top = -1};

float getDoctorConsultationFee(char *name) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Doctor *temp = hashTable[i];
        while (temp != NULL) {
            if (strcmp(temp->name, name) == 0) {
                return temp->consultationFee;
            }
            temp = temp->next;
        }
    }
    return -1; // Not found
}

void pushBill(struct Bill b) {
    if (billStack.top < MAX_BILLS - 1) {
        billStack.bills[++billStack.top] = b;
    } else {
        gotoxy(10, 13); printf("Billing stack is full!\n");
    }
}

void displayLastBill() {
    if (billStack.top == -1) {
        gotoxy(10, 13); printf("No bills available to display.\n");
        return;
    }
    struct Bill b = billStack.bills[billStack.top--];

    clearScreen();
    gotoxy(10, 2); printf("======= LAST BILL RECEIPT =======");
    gotoxy(10, 4); printf("Bill ID: %d", b.billID);
    gotoxy(10, 5); printf("Patient Name: %s", b.patientName);
    gotoxy(10, 6); printf("Doctor: %s", b.doctorName);
    gotoxy(10, 7); printf("Consultation Fee: %.2f", b.consultationFee);
    gotoxy(10, 8); printf("Medicine Cost: %.2f", b.medicineCost);
    gotoxy(10, 9); printf("Lab Charges: %.2f", b.labCharges);
    gotoxy(10, 10); printf("------------------------------");
    gotoxy(10, 11); printf("Total Amount: %.2f", b.total);
    gotoxy(10, 13); printf("(Bill popped from stack)\n");
    pauseScreen();
}

void generateBill() {
    struct Bill b;
    clearScreen();
    gotoxy(10, 2); printf("Enter Bill ID: ");
    scanf("%d", &b.billID);
    getchar();

    gotoxy(10, 3); printf("Enter Patient Name: ");
    fgets(b.patientName, sizeof(b.patientName), stdin);
    b.patientName[strcspn(b.patientName, "\n")] = '\0';

    gotoxy(10, 4); printf("Enter Doctor Name: ");
    fgets(b.doctorName, sizeof(b.doctorName), stdin);
    b.doctorName[strcspn(b.doctorName, "\n")] = '\0';

    b.consultationFee = getDoctorConsultationFee(b.doctorName);
    if (b.consultationFee < 0) {
        gotoxy(10, 6); printf("Doctor not found. Please register first.\n");
        pauseScreen();
        return;
    }

    gotoxy(10, 5); printf("Enter Medicine Cost: ");
    scanf("%f", &b.medicineCost);
    gotoxy(10, 6); printf("Enter Lab Charges: ");
    scanf("%f", &b.labCharges);

    b.total = b.consultationFee + b.medicineCost + b.labCharges;
    pushBill(b);

    clearScreen();
    gotoxy(10, 2); printf("======= BILL RECEIPT =======");
    gotoxy(10, 4); printf("Bill ID: %d", b.billID);
    gotoxy(10, 5); printf("Patient Name: %s", b.patientName);
    gotoxy(10, 6); printf("Doctor: %s", b.doctorName);
    gotoxy(10, 7); printf("Consultation Fee: %.2f", b.consultationFee);
    gotoxy(10, 8); printf("Medicine Cost: %.2f", b.medicineCost);
    gotoxy(10, 9); printf("Lab Charges: %.2f", b.labCharges);
    gotoxy(10, 10); printf("------------------------------");
    gotoxy(10, 11); printf("Total Amount: %.2f", b.total);
    gotoxy(10, 13); printf("Thank you! Get well soon.\n");
    pauseScreen();
}

void billingModule() {
    int choice;
    do {
        clearScreen();
        gotoxy(30, 2); printf("=== Billing & Payment Module ===");
        gotoxy(30, 5); printf("1. Generate Bill");
        gotoxy(30, 6); printf("2. View Last Bill (Pop from Stack)");
        gotoxy(30, 7); printf("0. Back to Main Menu");
        gotoxy(30, 9); printf("Enter your choice: ");
        scanf("%d", &choice);

        clearScreen();
        switch (choice) {
            case 1: generateBill(); break;
            case 2: displayLastBill(); break;
            case 0: gotoxy(10, 5); printf("Returning to Main Menu...\n"); break;
            default: gotoxy(10, 5); printf("Invalid choice. Try again.\n");
        }
        pauseScreen();
    } while (choice != 0);
}

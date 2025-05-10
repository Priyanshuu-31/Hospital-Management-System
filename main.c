// main.c
#include <stdio.h>
#include "doctor.h"

void doctorModule() {
    int choice;
    do {
        printf("\n--- Doctor Management Module ---\n");
        printf("1. Add Doctor\n");
        printf("2. List Doctors\n");
        printf("3. Search Doctor by ID\n");
        printf("4. Delete Doctor by ID\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addDoctor(); break;
            case 2: listDoctors(); break;
            case 3: searchDoctorByID(); break;
            case 4: deleteDoctorByID(); break;
            case 0: printf("Returning to Main Menu...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);
}

int main() {
    int mainChoice;
    do {
        printf("\n===== Hospital Management System =====\n");
        printf("1. Patient Management Module\n");
        printf("2. Doctor Management Module\n");
        printf("3. Appointment Module\n");
        printf("4. Billing & Payment Module\n");
        printf("5. Medical Records & Report Module\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &mainChoice);

        switch (mainChoice) {
            case 1:
                printf("Patient Management Module not implemented yet.\n");
                break;
            case 2:
                doctorModule();
                break;
            case 3:
                printf("Appointment Module not implemented yet.\n");
                break;
            case 4:
                printf("Billing & Payment Module not implemented yet.\n");
                break;
            case 5:
                printf("Medical Records & Report Module not implemented yet.\n");
                break;
            case 0:
                printf("Exiting Hospital Management System.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (mainChoice != 0);

    return 0;
}

#include <stdio.h>
#include "doctor.h"
#include "medicalrecord.h"
#include "appointments.h"
#include "consoleui.h"
#include "billing.h"
#include "patient.h"

int main() {
    int mainChoice;
    MedicalRecord* root = NULL;

    do {
        clearScreen();
        gotoxy(25, 2); printf("===== Hospital Management System =====");
        gotoxy(25, 5); printf("1. Patient Management Module");
        gotoxy(25, 6); printf("2. Doctor Management Module");
        gotoxy(25, 7); printf("3. Appointment Module");
        gotoxy(25, 8); printf("4. Billing & Payment Module");
        gotoxy(25, 9); printf("5. Medical Records & Report Module");
        gotoxy(25, 10); printf("0. Exit");
        gotoxy(25, 12); printf("Enter your choice: ");
        scanf("%d", &mainChoice);

        clearScreen();
        switch (mainChoice) {
            case 1:
                patientModule();
                break;
            case 2:
                doctorModule();
                break;
            case 3:
                appointmentModule();
                break;
            case 4:
                billingModule();
                break;
            case 5:
                root = medicalRecordModule(root);
                break;
            case 0:
                gotoxy(10, 5); printf("Exiting Hospital Management System.\n");
                break;
            default:
                gotoxy(10, 5); printf("Invalid choice. Try again.\n");
        }
        pauseScreen();
    } while (mainChoice != 0);

    return 0;
}

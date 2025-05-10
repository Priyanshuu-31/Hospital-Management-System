#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"
#include "consoleui.h"

struct Patient* patientTable[TABLE_SIZE] = {NULL};

int patientHash(int id) {
    return id % TABLE_SIZE;
}

int isPatientRegistered(const char *name) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Patient* temp = patientTable[i];
        while (temp != NULL) {
            if (strcmp(temp->name, name) == 0) {
                return 1;  // Patient found
            }
            temp = temp->next;
        }
    }
    return 0;  // Not found
}

void addPatient() {
    struct Patient* newPatient = (struct Patient*)malloc(sizeof(struct Patient));

    gotoxy(10, 2); printf("Enter Patient ID: ");
    scanf("%d", &newPatient->id);
    getchar();

    gotoxy(10, 3); printf("Enter Name: ");
    fgets(newPatient->name, sizeof(newPatient->name), stdin);
    newPatient->name[strcspn(newPatient->name, "\n")] = '\0';

    gotoxy(10, 4); printf("Enter Age: ");
    scanf("%d", &newPatient->age);
    getchar();

    gotoxy(10, 5); printf("Enter Gender: ");
    fgets(newPatient->gender, sizeof(newPatient->gender), stdin);
    newPatient->gender[strcspn(newPatient->gender, "\n")] = '\0';

    gotoxy(10, 6); printf("Enter Contact Number: ");
    fgets(newPatient->contact, sizeof(newPatient->contact), stdin);
    newPatient->contact[strcspn(newPatient->contact, "\n")] = '\0';

    int index = patientHash(newPatient->id);
    newPatient->next = patientTable[index];
    patientTable[index] = newPatient;

    gotoxy(10, 8); printf("Patient added successfully.\n");
}

void listPatients() {
    gotoxy(5, 2); printf("=== List of Patients ===\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Patient* temp = patientTable[i];
        while (temp != NULL) {
            printf("ID: %d | Name: %s | Age: %d | Gender: %s | Contact: %s\n",
                   temp->id, temp->name, temp->age, temp->gender, temp->contact);
            temp = temp->next;
        }
    }
}

void searchPatientByID() {
    int id;
    gotoxy(10, 2); printf("Enter Patient ID to search: ");
    scanf("%d", &id);
    int index = patientHash(id);
    struct Patient* temp = patientTable[index];
    while (temp != NULL) {
        if (temp->id == id) {
            gotoxy(10, 4); printf("Patient found: %s | Age: %d | Gender: %s | Contact: %s\n",
                   temp->name, temp->age, temp->gender, temp->contact);
            return;
        }
        temp = temp->next;
    }
    gotoxy(10, 4); printf("Patient not found.\n");
}

void deletePatientByID() {
    int id;
    gotoxy(10, 2); printf("Enter Patient ID to delete: ");
    scanf("%d", &id);
    int index = patientHash(id);
    struct Patient *temp = patientTable[index], *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        gotoxy(10, 4); printf("Patient not found.\n");
        return;
    }
    if (prev == NULL)
        patientTable[index] = temp->next;
    else
        prev->next = temp->next;
    free(temp);
    gotoxy(10, 4); printf("Patient deleted successfully.\n");
}

void patientModule() {
    int choice;
    do {
        clearScreen();
        gotoxy(30, 2); printf("=== Patient Management Module ===");
        gotoxy(30, 5); printf("1. Add Patient");
        gotoxy(30, 6); printf("2. List Patients");
        gotoxy(30, 7); printf("3. Search Patient by ID");
        gotoxy(30, 8); printf("4. Delete Patient by ID");
        gotoxy(30, 9); printf("0. Back to Main Menu");
        gotoxy(30, 11); printf("Enter your choice: ");
        scanf("%d", &choice);

        clearScreen();
        switch (choice) {
            case 1: addPatient(); break;
            case 2: listPatients(); break;
            case 3: searchPatientByID(); break;
            case 4: deletePatientByID(); break;
            case 0: gotoxy(10, 5); printf("Returning to Main Menu...\n"); break;
            default: gotoxy(10, 5); printf("Invalid choice. Try again.\n");
        }
        pauseScreen();
    } while (choice != 0);
}

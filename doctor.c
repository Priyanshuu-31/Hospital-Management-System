// ✅ FIXED & CLEAN: doctor.c using your own consoleui.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doctor.h"
#include "consoleui.h"  // Use your shared UI file

struct Doctor* hashTable[TABLE_SIZE] = {NULL};

int hashFunction(int id) {
    return id % TABLE_SIZE;
}

void addDoctor() {
    struct Doctor* newDoctor = (struct Doctor*)malloc(sizeof(struct Doctor));
    gotoxy(10, 2); printf("Enter Doctor ID: ");
    scanf("%d", &newDoctor->id);
    getchar();

    gotoxy(10, 3); printf("Enter Doctor Name: ");
    fgets(newDoctor->name, sizeof(newDoctor->name), stdin);
    newDoctor->name[strcspn(newDoctor->name, "\n")] = 0;

    gotoxy(10, 4); printf("Enter Specialty: ");
    fgets(newDoctor->specialty, sizeof(newDoctor->specialty), stdin);
    newDoctor->specialty[strcspn(newDoctor->specialty, "\n")] = 0;

    gotoxy(10, 5); printf("Enter Availability: ");
    fgets(newDoctor->availability, sizeof(newDoctor->availability), stdin);
    newDoctor->availability[strcspn(newDoctor->availability, "\n")] = 0;

    newDoctor->next = NULL;
    int index = hashFunction(newDoctor->id);
    newDoctor->next = hashTable[index];
    hashTable[index] = newDoctor;

    gotoxy(10, 7); printf("Doctor added successfully.\n");
}

void listDoctors() {
    gotoxy(5, 2); printf("=== List of Doctors ===\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Doctor* temp = hashTable[i];
        while (temp != NULL) {
            printf("ID: %d | Name: %s | Specialty: %s | Availability: %s\n",
                   temp->id, temp->name, temp->specialty, temp->availability);
            temp = temp->next;
        }
    }
}

void searchDoctorByID() {
    int id;
    gotoxy(10, 2); printf("Enter Doctor ID to search: ");
    scanf("%d", &id);
    int index = hashFunction(id);
    struct Doctor* temp = hashTable[index];
    while (temp != NULL) {
        if (temp->id == id) {
            gotoxy(10, 4); printf("Doctor found: %s (%s) - Available: %s\n",
                   temp->name, temp->specialty, temp->availability);
            return;
        }
        temp = temp->next;
    }
    gotoxy(10, 4); printf("Doctor not found.\n");
}

void deleteDoctorByID() {
    int id;
    gotoxy(10, 2); printf("Enter Doctor ID to delete: ");
    scanf("%d", &id);
    int index = hashFunction(id);
    struct Doctor *temp = hashTable[index], *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        gotoxy(10, 4); printf("Doctor not found.\n");
        return;
    }
    if (prev == NULL)
        hashTable[index] = temp->next;
    else
        prev->next = temp->next;
    free(temp);
    gotoxy(10, 4); printf("Doctor deleted successfully.\n");
}

void doctorModule() {
    int choice;
    do {
        clearScreen();
        gotoxy(30, 2); printf("=== Doctor Management Module ===");
        gotoxy(30, 5); printf("1. Add Doctor");
        gotoxy(30, 6); printf("2. List Doctors");
        gotoxy(30, 7); printf("3. Search Doctor by ID");
        gotoxy(30, 8); printf("4. Delete Doctor by ID");
        gotoxy(30, 9); printf("0. Back to Main Menu");
        gotoxy(30, 11); printf("Enter your choice: ");
        scanf("%d", &choice);

        clearScreen();
        switch (choice) {
            case 1: addDoctor(); break;
            case 2: listDoctors(); break;
            case 3: searchDoctorByID(); break;
            case 4: deleteDoctorByID(); break;
            case 0: gotoxy(10, 5); printf("Returning to Main Menu...\n"); break;
            default: gotoxy(10, 5); printf("Invalid choice. Try again.\n");
        }
        pauseScreen();
    } while (choice != 0);
}

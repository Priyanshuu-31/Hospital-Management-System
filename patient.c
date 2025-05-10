#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"
#include "consoleui.h"

Patient* addPatient(Patient* start) {
    Patient *newPatient, *ptr;
    newPatient = (Patient*)malloc(sizeof(Patient));
    
    if (newPatient == NULL) {
        gotoxy(10, 10); printf("Memory Allocation Failed\n");
        pauseScreen();
        return start;
    }

    clearScreen();
    gotoxy(30, 2); printf("===== ADD NEW PATIENT =====");
    
    // Get patient details
    gotoxy(10, 4); printf("Patient Name: ");
    fgets(newPatient->name, MAX_PATIENT_NAME, stdin);
    newPatient->name[strcspn(newPatient->name, "\n")] = '\0';
    
    gotoxy(10, 5); printf("Age: ");
    scanf("%d", &newPatient->age);
    getchar();
    
    gotoxy(10, 6); printf("Blood Group: ");
    fgets(newPatient->bloodGroup, 4, stdin);
    newPatient->bloodGroup[strcspn(newPatient->bloodGroup, "\n")] = '\0';
    
    gotoxy(10, 7); printf("Gender (M/F/Other): ");
    fgets(newPatient->gender, 10, stdin);
    newPatient->gender[strcspn(newPatient->gender, "\n")] = '\0';
    
    gotoxy(10, 8); printf("Contact Number: ");
    fgets(newPatient->contact, MAX_CONTACT, stdin);
    newPatient->contact[strcspn(newPatient->contact, "\n")] = '\0';
    
    strcpy(newPatient->status, "Active");
    
    // Add to list
    if (start == NULL) {
        newPatient->id = 1;
        newPatient->next = NULL;
        gotoxy(10, 12); printf("Patient added successfully! ID: 1");
    } else {
        ptr = start;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        newPatient->id = ptr->id + 1;
        newPatient->next = NULL;
        ptr->next = newPatient;
        gotoxy(10, 12); printf("Patient added successfully! ID: %d", newPatient->id);
    }
    
    pauseScreen();
    return start;
}

Patient* deletePatient(Patient* start) {
    int id;
    Patient *ptr, *prev = NULL;
    
    clearScreen();
    gotoxy(30, 2); printf("===== DELETE PATIENT =====");
    gotoxy(10, 4); printf("Enter Patient ID to delete: ");
    scanf("%d", &id);
    getchar();
    
    ptr = start;
    while (ptr != NULL && ptr->id != id) {
        prev = ptr;
        ptr = ptr->next;
    }
    
    if (ptr == NULL) {
        gotoxy(10, 6); printf("Patient with ID %d not found!", id);
    } else {
        if (prev == NULL) {
            start = ptr->next;
        } else {
            prev->next = ptr->next;
        }
        free(ptr);
        gotoxy(10, 6); printf("Patient with ID %d deleted successfully!", id);
    }
    
    pauseScreen();
    return start;
}

void searchPatient(Patient* start) {
    int id;
    Patient* ptr;
    
    clearScreen();
    gotoxy(30, 2); printf("===== SEARCH PATIENT =====");
    gotoxy(10, 4); printf("Enter Patient ID to search: ");
    scanf("%d", &id);
    getchar();
    
    ptr = start;
    while (ptr != NULL && ptr->id != id) {
        ptr = ptr->next;
    }
    
    if (ptr == NULL) {
        gotoxy(10, 6); printf("Patient not found!");
    } else {
        gotoxy(10, 6);  printf("ID: %d", ptr->id);
        gotoxy(10, 7);  printf("Name: %s", ptr->name);
        gotoxy(10, 8);  printf("Age: %d", ptr->age);
        gotoxy(10, 9);  printf("Blood Group: %s", ptr->bloodGroup);
        gotoxy(10, 10); printf("Gender: %s", ptr->gender);
        gotoxy(10, 11); printf("Contact: %s", ptr->contact);
        gotoxy(10, 12); printf("Status: %s", ptr->status);
    }
    
    pauseScreen();
}

Patient* updatePatient(Patient* start) {
    int id, choice;
    Patient* ptr;
    char newValue[100];
    
    clearScreen();
    gotoxy(30, 2); printf("===== UPDATE PATIENT =====");
    gotoxy(10, 4); printf("Enter Patient ID to update: ");
    scanf("%d", &id);
    getchar();
    
    ptr = start;
    while (ptr != NULL && ptr->id != id) {
        ptr = ptr->next;
    }
    
    if (ptr == NULL) {
        gotoxy(10, 6); printf("Patient not found!");
        pauseScreen();
        return start;
    }
    
    do {
        clearScreen();
        gotoxy(30, 2); printf("===== UPDATE PATIENT %d =====", id);
        gotoxy(10, 4); printf("Current Details:");
        gotoxy(10, 5); printf("1. Name: %s", ptr->name);
        gotoxy(10, 6); printf("2. Age: %d", ptr->age);
        gotoxy(10, 7); printf("3. Blood Group: %s", ptr->bloodGroup);
        gotoxy(10, 8); printf("4. Gender: %s", ptr->gender);
        gotoxy(10, 9); printf("5. Contact: %s", ptr->contact);
        gotoxy(10, 10); printf("6. Status: %s", ptr->status);
        gotoxy(10, 12); printf("0. Back to Menu");
        gotoxy(10, 14); printf("Select field to update (1-6): ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                gotoxy(10, 16); printf("Enter new name: ");
                fgets(newValue, MAX_PATIENT_NAME, stdin);
                newValue[strcspn(newValue, "\n")] = '\0';
                strcpy(ptr->name, newValue);
                break;
            case 2:
                gotoxy(10, 16); printf("Enter new age: ");
                scanf("%d", &ptr->age);
                getchar();
                break;
            // ... similar cases for other fields
            case 6:
                gotoxy(10, 16); printf("Enter new status: ");
                fgets(newValue, MAX_STATUS, stdin);
                newValue[strcspn(newValue, "\n")] = '\0';
                strcpy(ptr->status, newValue);
                break;
            case 0:
                break;
            default:
                gotoxy(10, 16); printf("Invalid choice!");
                pauseScreen();
        }
    } while (choice != 0);
    
    return start;
}

void listPatients(Patient* start) {
    Patient* ptr = start;
    int yPos = 4;
    
    clearScreen();
    gotoxy(30, 2); printf("===== PATIENT LIST =====");
    
    if (ptr == NULL) {
        gotoxy(10, 4); printf("No patients in the system!");
        pauseScreen();
        return;
    }
    
    gotoxy(5, 4); printf("ID");
    gotoxy(10, 4); printf("Name");
    gotoxy(30, 4); printf("Age");
    gotoxy(40, 4); printf("Contact");
    gotoxy(60, 4); printf("Status");
    
    while (ptr != NULL) {
        yPos++;
        gotoxy(5, yPos); printf("%d", ptr->id);
        gotoxy(10, yPos); printf("%s", ptr->name);
        gotoxy(30, yPos); printf("%d", ptr->age);
        gotoxy(40, yPos); printf("%s", ptr->contact);
        gotoxy(60, yPos); printf("%s", ptr->status);
        ptr = ptr->next;
        
        if (yPos >= 24) {  // Pagination
            gotoxy(10, yPos+2); printf("-- Press any key to continue --");
            getchar();
            clearScreen();
            yPos = 2;
        }
    }
    
    pauseScreen();
}

void patientModule() {
    Patient* patients = NULL;
    int choice;
    
    do {
        clearScreen();
        gotoxy(25, 2); printf("===== PATIENT MANAGEMENT =====");
        gotoxy(25, 5); printf("1. Add New Patient");
        gotoxy(25, 6); printf("2. Search Patient");
        gotoxy(25, 7); printf("3. Update Patient");
        gotoxy(25, 8); printf("4. Delete Patient");
        gotoxy(25, 9); printf("5. List All Patients");
        gotoxy(25, 10); printf("0. Back to Main Menu");
        gotoxy(25, 12); printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1: patients = addPatient(patients); break;
            case 2: searchPatient(patients); break;
            case 3: patients = updatePatient(patients); break;
            case 4: patients = deletePatient(patients); break;
            case 5: listPatients(patients); break;
            case 0: break;
            default:
                gotoxy(25, 14); printf("Invalid choice! Try again.");
                pauseScreen();
        }
    } while (choice != 0);
    
    // Optional: Add cleanup code here to free all patient memory
}
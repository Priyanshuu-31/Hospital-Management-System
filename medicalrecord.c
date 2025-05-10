// ✅ FIXED & CLEAN: medicalrecord.c using your console UI
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "medicalrecord.h"
#include "consoleui.h"

MedicalRecord* createRecord(int id, char name[], char diagnosis[], char treatment[], char report[]) {
    MedicalRecord* newNode = (MedicalRecord*)malloc(sizeof(MedicalRecord));
    newNode->recordID = id;
    strcpy(newNode->patientName, name);
    strcpy(newNode->diagnosis, diagnosis);
    strcpy(newNode->treatment, treatment);
    strcpy(newNode->labReport, report);
    newNode->left = newNode->right = NULL;
    return newNode;
}

MedicalRecord* insertRecord(MedicalRecord* root, int id, char name[], char diagnosis[], char treatment[], char report[]) {
    if (root == NULL) return createRecord(id, name, diagnosis, treatment, report);

    if (id < root->recordID)
        root->left = insertRecord(root->left, id, name, diagnosis, treatment, report);
    else if (id > root->recordID)
        root->right = insertRecord(root->right, id, name, diagnosis, treatment, report);
    else
        gotoxy(10, 10); printf("Record with ID %d already exists.\n", id);

    return root;
}

void displayInOrder(MedicalRecord* root) {
    if (root == NULL) return;
    displayInOrder(root->left);
    printf("\nRecord ID: %d\n", root->recordID);
    printf("Patient: %s\n", root->patientName);
    printf("Diagnosis: %s\n", root->diagnosis);
    printf("Treatment: %s\n", root->treatment);
    printf("Lab Report: %s\n", root->labReport);
    displayInOrder(root->right);
}

MedicalRecord* searchRecord(MedicalRecord* root, int id) {
    if (root == NULL || root->recordID == id)
        return root;
    if (id < root->recordID)
        return searchRecord(root->left, id);
    else
        return searchRecord(root->right, id);
}

MedicalRecord* medicalRecordModule(MedicalRecord* root) {
    int choice, id;
    char name[100], diagnosis[100], treatment[100], report[100];

    do {
        clearScreen();
        gotoxy(30, 2);  printf("=== Medical Records Module ===");
        gotoxy(30, 5);  printf("1. Add Medical Record");
        gotoxy(30, 6);  printf("2. Search Record by ID");
        gotoxy(30, 7);  printf("3. Display All Records");
        gotoxy(30, 8);  printf("0. Back to Main Menu");
        gotoxy(30, 10); printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        clearScreen();
        switch (choice) {
            case 1:
                gotoxy(10, 2); printf("Enter Record ID: ");
                scanf("%d", &id); getchar();
                gotoxy(10, 3); printf("Enter Patient Name: ");
                fgets(name, sizeof(name), stdin); name[strcspn(name, "\n")] = 0;
                gotoxy(10, 4); printf("Enter Diagnosis: ");
                fgets(diagnosis, sizeof(diagnosis), stdin); diagnosis[strcspn(diagnosis, "\n")] = 0;
                gotoxy(10, 5); printf("Enter Treatment: ");
                fgets(treatment, sizeof(treatment), stdin); treatment[strcspn(treatment, "\n")] = 0;
                gotoxy(10, 6); printf("Enter Lab Report Info: ");
                fgets(report, sizeof(report), stdin); report[strcspn(report, "\n")] = 0;
                root = insertRecord(root, id, name, diagnosis, treatment, report);
                break;

            case 2:
                gotoxy(10, 2); printf("Enter Record ID to search: ");
                scanf("%d", &id);
                MedicalRecord* found = searchRecord(root, id);
                if (found) {
                    gotoxy(10, 4); printf("Patient: %s", found->patientName);
                    gotoxy(10, 5); printf("Diagnosis: %s", found->diagnosis);
                    gotoxy(10, 6); printf("Treatment: %s", found->treatment);
                    gotoxy(10, 7); printf("Lab Report: %s", found->labReport);
                } else {
                    gotoxy(10, 4); printf("Record with ID %d not found.", id);
                }
                break;

            case 3:
                gotoxy(5, 2); printf("All Medical Records (In-Order):\n");
                displayInOrder(root);
                break;

            case 0:
                gotoxy(10, 5); printf("Returning to Main Menu...\n");
                break;

            default:
                gotoxy(10, 5); printf("Invalid choice. Try again.\n");
        }
        pauseScreen();
    } while (choice != 0);

    return root;
}

// medicalrecord.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "medicalrecord.h"

// Create a new node
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

// Insert into BST
MedicalRecord* insertRecord(MedicalRecord* root, int id, char name[], char diagnosis[], char treatment[], char report[]) {
    if (root == NULL) return createRecord(id, name, diagnosis, treatment, report);

    if (id < root->recordID)
        root->left = insertRecord(root->left, id, name, diagnosis, treatment, report);
    else if (id > root->recordID)
        root->right = insertRecord(root->right, id, name, diagnosis, treatment, report);
    else
        printf("Record with ID %d already exists.\n", id);

    return root;
}

// In-order traversal
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

// Search by ID
MedicalRecord* searchRecord(MedicalRecord* root, int id) {
    if (root == NULL || root->recordID == id)
        return root;

    if (id < root->recordID)
        return searchRecord(root->left, id);
    else
        return searchRecord(root->right, id);
}

// Menu Function for Integration
MedicalRecord* medicalRecordModule(MedicalRecord* root) {
    int choice, id;
    char name[100], diagnosis[100], treatment[100], report[100];

    do {
        printf("\n--- Medical Records & Report Module ---\n");
        printf("1. Add Medical Record\n");
        printf("2. Search Record\n");
        printf("3. Display All Records\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Record ID: ");
                scanf("%d", &id);
                printf("Enter Patient Name: ");
                scanf(" %[^\n]", name);
                printf("Enter Diagnosis: ");
                scanf(" %[^\n]", diagnosis);
                printf("Enter Treatment: ");
                scanf(" %[^\n]", treatment);
                printf("Enter Lab Report Info: ");
                scanf(" %[^\n]", report);
                root = insertRecord(root, id, name, diagnosis, treatment, report);
                break;

            case 2: {
                printf("Enter Record ID to search: ");
                scanf("%d", &id);
                MedicalRecord* found = searchRecord(root, id);
                if (found) {
                    printf("\nRecord Found:\n");
                    printf("Patient: %s\n", found->patientName);
                    printf("Diagnosis: %s\n", found->diagnosis);
                    printf("Treatment: %s\n", found->treatment);
                    printf("Lab Report: %s\n", found->labReport);
                } else {
                    printf("Record with ID %d not found.\n", id);
                }
                break;
            }

            case 3:
                printf("\nAll Medical Records (In-Order):\n");
                displayInOrder(root);
                break;

            case 0:
                printf("Returning to Main Menu...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return root;
}

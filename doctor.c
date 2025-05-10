// doctor.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doctor.h"

struct Doctor* hashTable[TABLE_SIZE] = {NULL};

int hashFunction(int id) {
    return id % TABLE_SIZE;
}

void addDoctor() {
    struct Doctor* newDoctor = (struct Doctor*)malloc(sizeof(struct Doctor));
    printf("Enter Doctor ID: ");
    scanf("%d", &newDoctor->id);
    getchar();
    printf("Enter Doctor Name: ");
    fgets(newDoctor->name, sizeof(newDoctor->name), stdin);
    newDoctor->name[strcspn(newDoctor->name, "\n")] = 0;
    printf("Enter Specialty: ");
    fgets(newDoctor->specialty, sizeof(newDoctor->specialty), stdin);
    newDoctor->specialty[strcspn(newDoctor->specialty, "\n")] = 0;
    printf("Enter Availability: ");
    fgets(newDoctor->availability, sizeof(newDoctor->availability), stdin);
    newDoctor->availability[strcspn(newDoctor->availability, "\n")] = 0;
    newDoctor->next = NULL;
    int index = hashFunction(newDoctor->id);
    newDoctor->next = hashTable[index];
    hashTable[index] = newDoctor;
}

void listDoctors() {
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
    printf("Enter Doctor ID to search: ");
    scanf("%d", &id);
    int index = hashFunction(id);
    struct Doctor* temp = hashTable[index];
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Doctor found: %s (%s) - Available: %s\n",
                   temp->name, temp->specialty, temp->availability);
            return;
        }
        temp = temp->next;
    }
    printf("Doctor not found.\n");
}

void deleteDoctorByID() {
    int id;
    printf("Enter Doctor ID to delete: ");
    scanf("%d", &id);
    int index = hashFunction(id);
    struct Doctor *temp = hashTable[index], *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Doctor not found.\n");
        return;
    }
    if (prev == NULL)
        hashTable[index] = temp->next;
    else
        prev->next = temp->next;
    free(temp);
    printf("Doctor deleted successfully.\n");
}

// ✅ FIXED & UPDATED: appointments.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "appointments.h"
#include "doctor.h"  // Ensure this has extern hashTable declaration

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isFull(Queue *q) {
    return q->rear == MAX - 1;
}

int isEmpty(Queue *q) {
    return q->front == -1 || q->front > q->rear;
}

// 🔍 Retrieve doctor availability
int getDoctorAvailability(char *name, char *availability) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Doctor* temp = hashTable[i];
        while (temp != NULL) {
            if (strcmp(temp->name, name) == 0) {
                strcpy(availability, temp->availability);
                return 1;
            }
            temp = temp->next;
        }
    }
    return 0;
}

void bookAppointment(Queue *q) {
    if (isFull(q)) {
        printf("Appointment queue is full!\n");
        return;
    }

    Appointment a;
    printf("Enter Appointment ID: ");
    scanf("%d", &a.id);
    getchar();

    printf("Enter Patient Name: ");
    fgets(a.patientName, sizeof(a.patientName), stdin);
    a.patientName[strcspn(a.patientName, "\n")] = '\0';

    printf("Enter Doctor Name: ");
    fgets(a.doctorName, sizeof(a.doctorName), stdin);
    a.doctorName[strcspn(a.doctorName, "\n")] = '\0';

    if (!getDoctorAvailability(a.doctorName, a.time)) {
        printf("Doctor not found or has no availability set.\n");
        return;
    }

    printf("Enter Date (dd-mm-yyyy): ");
    scanf("%s", a.date);
    // a.time is already filled from doctor availability

    if (isEmpty(q)) {
        q->front = 0;
    }
    q->appointments[++q->rear] = a;
    printf("Appointment booked successfully! Time: %s\n", a.time);
}

void cancelAppointment(Queue *q) {
    if (isEmpty(q)) {
        printf("No appointments to cancel.\n");
        return;
    }

    Appointment a = q->appointments[q->front++];
    printf("Canceled appointment for %s with Dr. %s on %s at %s.\n",
           a.patientName, a.doctorName, a.date, a.time);
}

void listAppointments(Queue *q) {
    if (isEmpty(q)) {
        printf("No appointments scheduled.\n");
        return;
    }

    printf("\nScheduled Appointments:\n");
    printf("-------------------------------------------------------------\n");
    for (int i = q->front; i <= q->rear; i++) {
        Appointment a = q->appointments[i];
        printf("ID: %d | Patient: %s | Doctor: %s | Date: %s | Time: %s\n",
               a.id, a.patientName, a.doctorName, a.date, a.time);
    }
    printf("-------------------------------------------------------------\n");
}

void appointmentModule() {
    Queue q;
    initQueue(&q);
    int choice;

    do {
        printf("\n--- Appointment Scheduling Module ---\n");
        printf("1. Book Appointment\n");
        printf("2. Cancel Appointment\n");
        printf("3. List Appointments\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: bookAppointment(&q); break;
            case 2: cancelAppointment(&q); break;
            case 3: listAppointments(&q); break;
            case 0: printf("Returning to Main Menu...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);
}

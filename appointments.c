// appointments.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "appointments.h"

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isFull(Queue *q) {
    return q->rear == MAX - 1;
}

int isEmpty(Queue *q) {
    return q->front == -1 || q->front > q->rear;
}

void bookAppointment(Queue *q) {
    if (isFull(q)) {
        printf("Appointment queue is full!\n");
        return;
    }

    Appointment a;
    printf("Enter Appointment ID: ");
    scanf("%d", &a.id);
    printf("Enter Patient Name: ");
    scanf(" %[^\n]", a.patientName);
    printf("Enter Doctor Name: ");
    scanf(" %[^\n]", a.doctorName);
    printf("Enter Date (dd-mm-yyyy): ");
    scanf("%s", a.date);
    printf("Enter Time (hh:mm): ");
    scanf("%s", a.time);

    if (isEmpty(q)) {
        q->front = 0;
    }
    q->appointments[++q->rear] = a;
    printf("Appointment booked successfully!\n");
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

// 👇 This replaces the old main() for modular use
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

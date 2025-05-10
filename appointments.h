// appointments.h
#ifndef APPOINTMENTS_H
#define APPOINTMENTS_H

#define MAX 100

typedef struct {
    int id;
    char patientName[100];
    char doctorName[100];
    char date[15];  // Format: "dd-mm-yyyy"
    char time[10];  // Format: "hh:mm"
} Appointment;

typedef struct {
    Appointment appointments[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q);
int isFull(Queue *q);
int isEmpty(Queue *q);
void bookAppointment(Queue *q);
void cancelAppointment(Queue *q);
void listAppointments(Queue *q);
void appointmentModule();  // 👈 Add this for main menu integration

#endif

// patient.h
#ifndef PATIENT_H
#define PATIENT_H

#define TABLE_SIZE 10

struct Patient {
    int id;
    char name[100];
    char gender[10];
    int age;
    char contact[15];
    struct Patient* next;
};

extern struct Patient* patientHashTable[TABLE_SIZE];

int isPatientRegistered(const char *name);

void patientModule();  // Keep your module function too

#endif

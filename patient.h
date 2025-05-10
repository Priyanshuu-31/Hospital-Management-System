// patient.h
#ifndef PATIENT_H
#define PATIENT_H

#include "consoleui.h"  // For consistent UI functions

#define MAX_PATIENT_NAME 100
#define MAX_CONTACT 15
#define MAX_STATUS 25

typedef struct PatientNode {
    int id;
    char name[MAX_PATIENT_NAME];
    char bloodGroup[4];
    char gender[10];
    int age;
    char contact[MAX_CONTACT];
    char status[MAX_STATUS];
    struct PatientNode* next;
} Patient;

// Initialize patient list
void initPatientList();

// Core patient operations
Patient* addPatient(Patient* start);
Patient* deletePatient(Patient* start);
Patient* updatePatient(Patient* start);
void searchPatient(Patient* start);
void listPatients(Patient* start);

// Module interface
void patientModule();

#endif
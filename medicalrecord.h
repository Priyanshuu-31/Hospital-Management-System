// medicalrecord.h
#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H

typedef struct MedicalRecord {
    int recordID;
    char patientName[100];
    char diagnosis[100];
    char treatment[100];
    char labReport[100];
    struct MedicalRecord *left, *right;
} MedicalRecord;

MedicalRecord* createRecord(int id, char name[], char diagnosis[], char treatment[], char report[]);
MedicalRecord* insertRecord(MedicalRecord* root, int id, char name[], char diagnosis[], char treatment[], char report[]);
void displayInOrder(MedicalRecord* root);
MedicalRecord* searchRecord(MedicalRecord* root, int id);
MedicalRecord* medicalRecordModule(MedicalRecord* root);  // Add this line

#endif

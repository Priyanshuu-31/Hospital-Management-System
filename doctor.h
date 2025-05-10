#ifndef DOCTOR_H
#define DOCTOR_H

#define TABLE_SIZE 10

struct Doctor {
    int id;
    char name[100];
    char specialty[100];
    char availability[100];
    struct Doctor* next;
};

extern struct Doctor* hashTable[TABLE_SIZE];

void addDoctor();
void listDoctors();
void searchDoctorByID();
void deleteDoctorByID();
void doctorModule();  // ✅ This must be here

#endif

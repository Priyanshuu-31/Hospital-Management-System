// doctor.h
#ifndef DOCTOR_H
#define DOCTOR_H

#define TABLE_SIZE 10

struct Doctor {
    int id;
    char name[50];
    char specialty[50];
    char availability[50];
    struct Doctor* next;
};

// Function declarations
void addDoctor();
void listDoctors();
void searchDoctorByID();
void deleteDoctorByID();

#endif

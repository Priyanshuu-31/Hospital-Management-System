#ifndef BILLING_H
#define BILLING_H

struct Bill {
    int billID;
    char patientName[100];
    char doctorName[100];
    float consultationFee;
    float medicineCost;
    float labCharges;
    float total;
};

void generateBill();
void displayLastBill();
void billingModule();

#endif

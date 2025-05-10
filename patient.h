#ifndef PATIENT_H
#define PATIENT_H

#define MAX 100

// Defining structure for a Node
typedef struct node{
    // Patient Info
    int ID;
    char name[MAX];
    char blood_grp[4];
    char gender[10];
    int age;
    char contact_no[11];
    // Medical Info
    char status[25];
    // Node Link
    struct node *next;
} node;

// Function Prototypes
node *create_ll_at_end(node *start);
node *delete_node(node *start);
node *update_node(node *start);
node *search_node(node *start);

#endif // PATIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"

// Function to add a node to the end of the list
node *create_ll_at_end(node *start){
    node *new_node, *ptr;
    char name_val[MAX];
    char bg[4];
    int age_temp;
    char cntct[11];
    char gen[10];

    // Allocating Memory
    new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL){
        printf("Memory Allocation Failed\n");
        return start;
    }

    getchar(); // Clear input buffer

    // Getting Patient Details
    printf("Enter the Patient's Name:");
    fgets(name_val, MAX, stdin);
    name_val[strcspn(name_val, "\n")] = 0;
    strcpy(new_node->name, name_val);

    printf("Age:");
    scanf("%d", &age_temp);
    new_node->age = age_temp;

    getchar();

    printf("Blood Group:");
    fgets(bg, 4, stdin);
    bg[strcspn(bg, "\n")] = 0;
    strcpy(new_node->blood_grp, bg);

    printf("Gender(Male/Female/Non-Binary):");
    fgets(gen, 10, stdin);
    gen[strcspn(gen, "\n")] = 0;
    strcpy(new_node->gender, gen);

    printf("Contact Number:");
    fgets(cntct, 11, stdin);
    cntct[strcspn(cntct, "\n")] = 0;
    strcpy(new_node->contact_no, cntct);
    
    strcpy(new_node->status, "Undergoing Treatment");

    // If first Node
    if (start == NULL){
        new_node->next = NULL;
        new_node->ID = 1;
        start = new_node;
        return start;
    }

    // If not the first node
    ptr = start;
    int i = 1;
    while (ptr->next != NULL){
        ptr = ptr->next;
        i++;
    }
    ptr->next = new_node;
    new_node->next = NULL;
    new_node->ID = i + 1;
    return start;
}

// Function to delete a node based on ID
node *delete_node(node *start){
    node *ptr, *prev = NULL;
    int val;
    printf("Enter the ID for Deletion:");
    scanf("%d", &val);

    ptr = start;
    while (ptr != NULL && ptr->ID != val){
        prev = ptr;
        ptr = ptr->next;
    }

    if (ptr == NULL){
        printf("ID not Found\n");
        return start;
    }

    // if it's the first node
    if (ptr == start){
        start = start->next;
        free(ptr);
        printf("Record Deleted\n");
        return start;
    }

    // if not the first node
    prev->next = ptr->next;
    free(ptr);
    printf("Record Deleted\n");
    return start;
}

// Function to update a patient's details
node *update_node(node *start){
    node *ptr;
    int ID_val, option;
    char new_status[25], new_name[MAX];

    // Asking for the ID to Search
    while (1){
        printf("\nEnter the ID of the Record (Enter -1 to Exit):");
        scanf("%d", &ID_val);

        if (ID_val == -1){
            printf("Exiting...\n");
            break;
        }

        ptr = start;
        while (ptr != NULL && ptr->ID != ID_val){
            ptr = ptr->next;
        }

        if (ptr == NULL){
            printf("Record not Found\n");
            continue;
        }

        // Required Updation Menu
        while (1){
            printf("\nWhat to Update?:\n 1.Name \n 2.Status \n 3.Contact Number \n 4.Exit\n");
            scanf("%d", &option);
            getchar();

            if (option == 1){ // Updating Name
                printf("\nEnter the New Name:");
                fgets(new_name, MAX, stdin);
                new_name[strcspn(new_name, "\n")] = 0;
                strcpy(ptr->name, new_name);
                printf("Name Updated\n");
            }
        
            else if (option == 2){ // Updating Status
                int status_op;
                printf("\nEnter the status:\n 1.Undergoing Treatment \n 2.Discharged \n 3.Exit\n ");
                scanf("%d", &status_op);
                getchar();

                while (1){
                    if (status_op == 1){
                        strcpy(ptr->status, "Undergoing Treatment");
                        printf("Set to 'Undergoing Treatment'\n");
                        break;
                    }
                    else if (status_op == 2){
                        strcpy(ptr->status, "Discharged");
                        printf("Set to 'Discharged'\n");
                        break;
                    }
                    else if (status_op == 3){
                        printf("Exiting...\n");
                        break;
                    }
                    else{
                        printf("Enter a valid option!\n");
                    }
                }
            }
            
            else if (option == 3){
                char new_cntct[11];
                printf("Enter the New Contact Number:");
                fgets(new_cntct, 11, stdin);
                new_cntct[strcspn(new_cntct, "\n")] = 0;
                strcpy(ptr->contact_no, new_cntct);
                printf("Contact Number Updated..\n");
            }
            
            else if (option == 4){
                printf("Exiting...\n");
                break;
            }

            else{
                printf("Invalid Option\n");
            }
        }
    }
    return start;
}

// Function to search for a node by ID
node *search_node(node *start){
    node *ptr;
    int search_ID;
    printf("Enter the ID to be Searched:");
    scanf("%d", &search_ID);

    ptr = start;
    while (ptr != NULL && ptr->ID != search_ID){
        ptr = ptr->next;
    }

    if (ptr == NULL){
        printf("Record Not Found\n");
        return start;
    }

    printf("\nID\t Name\t Age\t BloodGroup\t Gender\t ContactNo.\t Status\n");
    printf("%d \t %s \t %d\t %s \t %s \t %s \t %s\n", ptr->ID, ptr->name, ptr->age, ptr->blood_grp, ptr->gender, ptr->contact_no, ptr->status);
    return start;
}

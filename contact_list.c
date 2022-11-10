#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "contact_list.h"
#include "contact.h"
#include "utils.h"

static CONTACT_T *bucket_list[26];

void init_contact_list(void) {

    for(int n = 0; n < 26; n++) {
        bucket_list[n] = NULL;
    }
}

void insert_contact(CONTACT_T *contact) {

    CONTACT_T *curr, *prev;
    NAME_T lname1, lname2;

    int bucket = (*contact).last_name[0] - 'A';
    curr = bucket_list[bucket];

    if(curr == NULL) {
        bucket_list[bucket] = contact;
    }
    else if((strcmp(contact->last_name, curr->last_name)) < 0) {
        contact->next = curr;
        bucket_list[bucket] = contact;
    }
    else {
        curr = bucket_list[bucket];
        prev = NULL;
        while(curr != NULL) {
            int result;
            result = strcmp(contact->last_name, curr->last_name);
            if(result < 0) {
                contact->next = curr;
                prev->next = contact;
                break;
            }
            if(curr->next == NULL) {
                curr->next = contact;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    }
}

void print_contact_list(char mode) {

    CONTACT_T *curr;
    int count = 0;

    for(int n = 0; n < 26; n++) {
        curr = bucket_list[n];
        while(curr != NULL) {
            print_contact(curr, mode);
            curr = curr->next;
            count++;
        }
    }
    if(count == 0) {
        printf("No contacts in list\n");
    }
    printf("\n");
}

CONTACT_T *find_contact(NAME_T last_name, NAME_T first_name) {

    CONTACT_T *curr;
    NAME_T lname, fname, lname2, fname2;

    strcpy(lname, last_name);
    strcpy(fname, first_name);
    
    int bucket = lname[0] - 'A';
    curr = bucket_list[bucket];

    while(curr != NULL) {
        strcpy(lname2, curr->last_name);
        strcpy(fname2, curr->first_name);
        upper(lname2);
        upper(fname2);
        if((strcmp(fname, fname2) == 0) && (strcmp(lname, lname2) == 0)) {
            return curr;
        }
        curr = curr->next;
    }
    return curr;
}

CONTACT_T *get_next_contact(char letter) {

    static CONTACT_T *curr;

    int bucket = letter - 'A';
    if(curr == NULL) {
        curr = bucket_list[bucket];
        return curr;
    }
    curr = curr->next;
    return curr;
}

void print_state_contacts(char state[], char mode) {

    CONTACT_T *curr;
    int count = 0;

    for(int n = 0; n < 26; n++) {
        curr = bucket_list[n];
        while(curr != NULL) {
            if((strcmp(state, curr->state)) == 0) {
                print_contact(curr, mode);
                count++;
            }
            curr = curr->next; 
        }
    }
    if(count == 0) {
        printf("No contacts found\n\n");
    }
}

void free_contact_list(void) {

    CONTACT_T *tmp, *curr;

    for(int n = 0; n < 26; n++) {
        curr = bucket_list[n];
        while(curr != NULL) {
            tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
}

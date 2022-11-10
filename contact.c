#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "contact.h"
#include "contact_list.h"

CONTACT_T *create_contact(CONTACT_T *contact) {

    CONTACT_T *new_contact = (CONTACT_T *)malloc(sizeof(CONTACT_T));

    strcpy(new_contact->first_name, (*contact).first_name);
    strcpy(new_contact->last_name, (*contact).last_name);
    strcpy(new_contact->co_name, (*contact).co_name);
    strcpy(new_contact->addr, (*contact).addr);
    strcpy(new_contact->city, (*contact).city);
    strcpy(new_contact->county, (*contact).county);
    strcpy(new_contact->state, (*contact).state);
    strcpy(new_contact->zip, (*contact).zip);
    strcpy(new_contact->phone1, (*contact).phone1);
    strcpy(new_contact->phone2, (*contact).phone2);
    strcpy(new_contact->email, (*contact).email);
    strcpy(new_contact->web, (*contact).web);
    new_contact->next = NULL;

    return new_contact;
}

void print_contact(CONTACT_T *contact, char mode) {

    if(mode == 'F') {
        printf("Name:    %s %s\n", contact->first_name, contact->last_name);
        printf("Address: %s, %s, %s %s  (%s)\n", contact->addr, contact->city, 
        (*contact).state, contact->zip, contact->county);
        printf("Phone:   %s (primary)  %s\n", contact->phone1, contact->phone2);
        printf("email:   %s\n", contact->email);
        printf("web:     %s\n\n", contact->web);
    }
    else {
        printf("%-20s%-20s%s  %s\n", contact->last_name, contact->first_name, 
        contact->phone1, contact->email);
    }
}
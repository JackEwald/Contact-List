/*** CS 304 - Assignment 6
   Author: Jack Ewald
   Description: This program takes in as input of text file containing 
   lines of contact information for numerous individuals. Using an array of linked lists, 
   the program alphabetically sorts each contact into its correct location. The program
   also allows the user to query the contact list by state, individual, and last name. 
***/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "contact.h"
#include "contact_list.h"

void process_file(char *filename);
char print_menu(void);
char print_format_menu(void);
void find_individual(char mode);
void print_tab(char mode);
void process_state_contacts(char mode);

void process_file(char *filename) {

    FILE *fp;
    CONTACT_T contact;
    CONTACT_T *contact_ptr;

    fp = fopen(filename, "r");
    fscanf(fp, "%*s\n");
    
    while(fscanf(fp, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%s ", 
    contact.first_name, contact.last_name, contact.co_name, contact.addr, 
    contact.city, contact.county, contact.state, contact.zip, contact.phone1,
    contact.phone2, contact.email, contact.web) == 12) {
        contact_ptr = create_contact(&contact);
        insert_contact(contact_ptr);
    }
}

char print_menu(void) {

    char option[10];
    char valid_options[] = "CITSQ";
    char input;

    int loop = 1;
    do {
        printf("Please select one of the following:\n\n");
        printf(" c  Change output format\n");
        printf(" i  Search for individual\n");
        printf(" t  Print tab\n");
        printf(" s  Look up by state\n");
        printf(" q  Quit\n\n");
        printf("Option: ");
        scanf("%s", option);
        printf("%s\n", option);
        input = option[0];
        upper(&input);
        if(strlen(option) > 1 || (!strchr(valid_options, input))) {
            printf("\n");
            printf("Invalid option entered\n");
        }
        else {
            loop = 0;
        }
    }
    while(loop);
    return input;
}

char print_format_menu(void) {

    char option[3];
    char valid_options[] = "CF";
    char input;

    printf("Please select one of the following:\n\n");
    printf(" c  Condensed output information\n");
    printf(" f  Full output information\n\n");
    printf("Option: ");
    scanf("%s", option);
    printf("%s\n", option);
    input = option[0];
    upper(&input);
    return input;
}

void find_individual(char mode) {

    CONTACT_T *contact_ptr;
    NAME_T last_name, first_name;

    printf("Please enter last name: ");
    scanf("%s", last_name);
    printf("%s\n", last_name);
    printf("Please enter first name: ");
    scanf("%s", first_name);
    printf("%s\n", first_name);

    upper(first_name);
    upper(last_name);

    contact_ptr = find_contact(last_name, first_name);
    
    if(contact_ptr) {
        print_contact(contact_ptr, mode);
    }
    else {
        printf("Contact not found\n\n");
    }
}

void print_tab(char mode) {

    CONTACT_T *contact_ptr;
    char input[2];
    char letter;

    printf("Please enter last name tab letter: ");
    scanf("%s", input);
    printf("%s\n", input);
    letter = input[0];
    upper(&letter);

    contact_ptr = get_next_contact(letter);
    if(contact_ptr) {
        while(contact_ptr) {
            print_contact(contact_ptr, mode);
            contact_ptr = get_next_contact(letter);
        }
    }
    else {
        printf("No contacts found\n");
    }
    
}

void process_state_contacts(char mode) {

    char state[3];

    printf("Please enter two-letter state abbreviation: ");
    scanf("%s", state);
    printf("%s\n", state);

    upper(state);
    print_state_contacts(state, mode);
}

void main(int argc, char *argv[]) {

    char mode = 'C';
    int loop = 1;

    if(argc < 2) {
        printf("No contact file provided");
        exit(1);
    }

    init_contact_list();
    process_file(argv[1]);
    print_contact_list(mode);

    do {
        char option = print_menu();

        switch(option) {
            case 'C':
            {
                mode = print_format_menu();
                break;
            }
            case 'I':
            {
                find_individual(mode);
                break;
            }
            case 'T':
            {
                print_tab(mode);
                break;
            }
            case 'S':
            {
                process_state_contacts(mode);
                break;
            }
            case 'Q':
            {
                loop = 0;
                break;
            }
        }
    }
    while(loop);

    free_contact_list(); 
}
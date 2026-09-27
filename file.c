#include <stdio.h>
#include "file.h"

/* Loads contacts from contact.txt into the address book. */
void loadcontacts(addressbook *book)
{
    FILE *fp;
    int i;

    /* Open the contact file in read mode. */
    fp = fopen("contact.txt", "r");

    /* Start with an empty address book if the file does not exist. */
    if (fp == NULL)
    {
        printf("No contact file found. Starting with empty address book.\n");
        book->count = 0;
        return;
    }

    /* Read the total number of contacts stored in the file. */
    if (fscanf(fp, "Contact Counts: %d\n", &book->count) != 1)
    {
        printf("Invalid contact file format.\n");
        book->count = 0;
        fclose(fp);
        return;
    }

    /* Validate that the contact count is within the array limit. */
    if (book->count < 0 || book->count > 100)
    {
        printf("Invalid contact count in file.\n");
        book->count = 0;
        fclose(fp);
        return;
    }

    /* Read each contact's name, phone number, and email from the file. */
    for (i = 0; i < book->count; i++)
    {
        if (fscanf(fp, "%*d: %49[^,],%14[^,],%49[^\n]\n",
                   book->Contacts[i].name,
                   book->Contacts[i].number,
                   book->Contacts[i].email) != 3)
        {
            printf("Invalid contact data in file.\n");

            /* Keep only the contacts that were successfully loaded. */
            book->count = i;
            break;
        }
    }

    /* Close the contact file after loading all records. */
    fclose(fp);
}

/* Saves all current contacts from the address book to contact.txt. */
void savecontacts(addressbook *book)
{
    FILE *fp;
    int i;

    /* Open the contact file in write mode and overwrite old contents. */
    fp = fopen("contact.txt", "w");

    /* Handle file opening failure. */
    if(fp == NULL)
    {
        printf("Error opening contact.txt\n");
        return;
    }

    /* Save the total number of contacts at the beginning of the file. */
    fprintf(fp, "Contact Counts: %d\n", book->count);

    /* Write each contact with its index, name, phone number, and email. */
    for (i = 0; i < book->count; i++)
    {
        fprintf(fp, "%d: %s,%s,%s\n",
                i + 1,
                book->Contacts[i].name,
                book->Contacts[i].number,
                book->Contacts[i].email);
    }

    /* Close the contact file after saving all contacts. */
    fclose(fp);
}
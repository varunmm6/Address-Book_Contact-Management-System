/*
┌──────────────────────────────┐
│         ADDRESS BOOK         │
├──────────────────────────────┤
│  +  1. Create contact        │
│  >  2. Search contact        │
│  *  3. Edit contact          │
│  -  4. Delete contact        │
│  #  5. List all contacts     │
│  ✓  6. Save and Exit         |
└──────────────────────────────┘
Enter choice: 1
===============================
Enter the name: Varun B R
Enter the number: 7975748560
Enter the email: varunbr32@gmail.com
===============================
Contact added successfully
===============================

*/
#include <stdio.h>
#include "header.h"
#include "file.h"

/*Documentation

Name        : Varun M M
Student id  : 26018_042
Batch id    : 26018D
Start Date  : 07/09/2026
End date    : 19/09/2026

Description:
The following functions are implemented in the Address Book project to manage contacts.

createcontact()        :-> Adds a new contact by taking name, phone number and email ID from the user.
                         -> Validates all inputs before storing the contact in the address book.

searchcontact()        :-> Searches contacts using name, phone number or email ID.
                         -> Displays all contacts matching the entered search value.

editcontact()          :-> Allows the user to modify the name, phone number or email ID of an existing contact.
                         -> Validates the new information before updating the contact.

deletecontact()        :-> Searches for a contact using name, phone number or email ID.
                         -> Displays the selected contact and asks for confirmation before deletion.

listcontact()          :-> Displays all contacts in a formatted table.
                         -> Allows the user to sort contacts by name, phone number or email ID.

validatename()         :-> Checks whether the name contains only alphabets and spaces and has at least 4 characters.
                         ->Also checks that the first and last characters are not spaces.

validatenumber()       :-> Checks that the phone number contains exactly 10 digits and starts with 6 to 9.
                         -> Also checks that the phone number is unique.

validateemail()        :-> Checks the email format for lowercase letters, digits, one '@', one '.', and '.com' at the end.
                         -> Also checks that the email ID is unique.

savecontacts()         :-> Saves the contact count and all contact details into contact.txt.
                         -> Preserves the contacts so they can be loaded during the next program execution.

loadcontacts()         :-> Reads the saved contact count and contact details from contact.txt.
                         -> Loads previously saved contacts into the address book when the program starts.

*/
int main()
{
    addressbook book;
    int choice;

    book.count = 0;
    /* TO load the contact file to Ram */
    loadcontacts(&book);

    do
    {
        printf("\n");
        printf("┌──────────────────────────────┐\n");
        printf("│       📒 ADDRESS BOOK        │\n");
        printf("├──────────────────────────────┤\n");
        printf("│  ✚  1. Create contact        │\n");
        printf("│  🔍 2. Search contact        │\n");
        printf("│  ✎  3. Edit contact          │\n");
        printf("│  ✖  4. Delete contact        │\n");
        printf("│  ☷  5. List all contacts     │\n");
        printf("│  ✓  6. Save and Exit         │\n");
        printf("└──────────────────────────────┘\n");

        printf(BRIGHT_BLUE "Enter choice: " RESET);
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid choice!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        printf("===============================\n");

        switch (choice)
        {
        /*Choice To Add New Contact To Address Book*/
        case 1:
            createcontact(&book);
            break;
        /*Choice To Search Saved Contacts*/
        case 2:
            searchcontact(&book);
            break;
        /*Choice To Edit Saved Contacts*/
        case 3:
            editcontact(&book);
            break;
        /*Choice To Delete The Contact By Nane,number,email*/
        case 4:
            deletecontact(&book);
            break;
        /*choice To List The Saved Contacts In Order*/
        case 5:
            listcontact(&book);
            break;

        /*choice to Save the contact Befor Exit*/
        case 6:
        {
            int i, delay, j;

            for (i = 1; i <= 100; i++)
            {
                printf(GREEN "\rSaving [" RESET);

                for (j = 1; j <= 23; j++)
                {
                    j <= i * 23 / 100 ? printf(GREEN "#" RESET) : printf(" ");
                }

                printf(GREEN "] %i%%" RESET, i);
                fflush(stdout);

                for (delay = 0xffffff; delay--;);
            }

            savecontacts(&book);

            printf(GREEN "\nSaved And Exit Successfully...\n" RESET);
            break;
        }
        default:
            printf(RED "Invalid choice! Please try again.\n" RESET);
        }
    } while (choice != 6);
    return 0;
}

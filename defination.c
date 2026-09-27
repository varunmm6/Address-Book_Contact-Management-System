#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "header.h"

/* CREATE CONTACT */
void createcontact(addressbook *book)
{
    /* Temp Storage */
    char tempname[50];
    char tempnumber[15];
    char tempemail[50];

    /* Check whether address book has reached maximum capacity */
    if (book->count >= 100)
    {
        printf(YELLOW "Contact List is Full\n" RESET);
        return;
    }
    /* Read complete name including spaces and validate the entered name */
    while (1)
    {
        printf(BRIGHT_BLUE "Enter the name: " RESET);
        if (scanf("%49[^\n]", tempname) != 1)
        {
            printf(RED "Invalid Name! Name Should Not Be Empty.\n" RESET);
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (validatename(tempname))
        {
            break;
        }
    }
    /* Read phone number as a string to preserve digit-by-digit validation */
    while (1)
    {
        printf(BRIGHT_BLUE "Enter the number: " RESET);
        if (scanf("%14[^\n]", tempnumber) != 1)
        {
            printf(RED "Invalid Number! Number should Not be empty.\n" RESET);
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (validatenumber(tempnumber, book, -1))
        {
            break;
        }
    }
    /* Read email ID and validate its format and uniqueness */
    while (1)
    {
        printf(BRIGHT_BLUE "Enter the email: " RESET);
        if (scanf("%49[^\n]", tempemail) != 1)
        {
            printf(RED "Invalid Email! Email Should Not be Empty.\n" RESET);
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (validateemail(tempemail, book, -1))
        {
            break;
        }
    }
    /* Store validated contact details at the next available index */
    strcpy(book->Contacts[book->count].name, tempname);
    strcpy(book->Contacts[book->count].number, tempnumber);
    strcpy(book->Contacts[book->count].email, tempemail);

    /* Increase contact count after successfully adding the contact */
    book->count++;

    printf("\n");

    /*Progress Bar*/
    int i, delay, j;
    for (i = 1; i <= 100; i++)
    {
        printf(GREEN "\rAdding [" RESET);
        for (j = 1; j <= 23; j++)
        {
            j <= i * 23 / 100 ? printf(GREEN "#" RESET) : printf(" ");
        }
        printf(GREEN "] %i%%" RESET, i);
        fflush(stdout);
        for (delay = 0xffffff; delay--;);
    }

    printf("\n==============================\n");
    printf(GREEN "Contact %d added successfully\n" RESET, book->count);
    printf("==============================\n");
}

/* LIST CONTACTS */
void listcontact(addressbook *book)
{
    /*Variables for listcontacts*/
    int i, j;
    int choice;
    contact temp;

    /* Prevent sorting/display operation when there are no contacts */
    if (book->count == 0)
    {
        printf(YELLOW "Address Book is Empty\n" RESET);
        return;
    }
    /* Repeat sorting menu until the user chooses Exit */
    do
    {
        printf("\n");
        printf("╔══════════════════════════════╗\n");
        printf("║       SORT CONTACTS BY       ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("║  ➤ 1. Sort by Name           ║\n");
        printf("║  ➤ 2. Sort by Phone          ║\n");
        printf("║  ➤ 3. Sort by Email          ║\n");
        printf("║  ➤ 4. Exit                   ║\n");
        printf("╚══════════════════════════════╝\n");

        printf(BRIGHT_BLUE "Enter List choice: " RESET);
        /* Handle non-numeric input and clear invalid characters from input buffer */
        if (scanf("%d", &choice) != 1)
        {
            printf(RED "Invalid Choice! Plesse Enter Valid Choice\n" RESET);
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice)
        {
        /* Bubble sort contacts alphabetically by name */
        case 1:
            for (i = 0; i < book->count - 1; i++)
            {
                for (j = 0; j < book->count - 1 - i; j++)
                {
                    if (strcmp(book->Contacts[j].name, book->Contacts[j + 1].name) > 0)
                    {
                        /* Swap complete contact structures to maintain all contact details together */
                        temp = book->Contacts[j];
                        book->Contacts[j] = book->Contacts[j + 1];
                        book->Contacts[j + 1] = temp;
                    }
                }
            }
            break;
        /* Bubble sort contacts in ascending order by phone number */
        case 2:
            for (i = 0; i < book->count - 1; i++)
            {
                for (j = 0; j < book->count - 1 - i; j++)
                {
                    if (strcmp(book->Contacts[j].number, book->Contacts[j + 1].number) > 0)
                    {
                        /* Swap complete contact structures to maintain all contact details together */
                        temp = book->Contacts[j];
                        book->Contacts[j] = book->Contacts[j + 1];
                        book->Contacts[j + 1] = temp;
                    }
                }
            }
            break;
        /* Bubble sort contacts alphabetically by email ID */
        case 3:
            for (i = 0; i < book->count - 1; i++)
            {
                for (j = 0; j < book->count - 1 - i; j++)
                {
                    if (strcmp(book->Contacts[j].email, book->Contacts[j + 1].email) > 0)
                    {
                        /* Swap complete contact structures to maintain all contact details together */
                        temp = book->Contacts[j];
                        book->Contacts[j] = book->Contacts[j + 1];
                        book->Contacts[j + 1] = temp;
                    }
                }
            }
            break;
        /* ---------- EXIT ---------- */
        case 4:
            return;

        default:
            printf(RED "Invalid Choice! Please Enter Valid Choice\n" RESET);
            break;
        }
        /* Display contacts after sorting in a formatted table */
        if (choice >= 1 && choice <= 3)
        {
            printf("\n");
            printf("+-------+--------------------------+----------------+-----------------------------------------+\n");
            printf("| %-5s | %-24s | %-14s | %-39s |\n", "SL.NO", "NAME", "PHONE", "EMAIL");
            printf("+-------+--------------------------+----------------+-----------------------------------------+\n");

            for (i = 0; i < book->count; i++)
            {
                printf("| %-5d | %-24s | %-14s | %-39s |\n",
                       i + 1, book->Contacts[i].name, book->Contacts[i].number, book->Contacts[i].email);
            }
            printf("+-------+--------------------------+----------------+-----------------------------------------+\n");

            printf("\n-------------------------------\n");
            printf(GREEN "Maximum Contacts Allowed: %d\n" RESET, 100);
            printf(YELLOW "Contacts Stored: %d\n" RESET, book->count);
            printf(YELLOW "Available Slots: %d\n" RESET, 100 - book->count);
            printf("-------------------------------\n");
        }
    } while (choice != 4);
}

/* SEARCH CONTACT */
void searchcontact(addressbook *book)
{
    int searchchoice;
    int found;
    int i;

    char str[100];

    /* Check whether address book is empty */
    if (book->count == 0)
    {
        printf(YELLOW "Address Book is Empty\n" RESET);
        return;
    }

    do
    {
        printf("\n");
        printf("+================================+\n");
        printf("|        SEARCH CONTACT BY       |\n");
        printf("+================================+\n");
        printf("|  1. >> Search by Name          |\n");
        printf("|  2. >> Search by Phone         |\n");
        printf("|  3. >> Search by Email         |\n");
        printf("|  4. >> Exit                    |\n");
        printf("+================================+\n");

        printf(BRIGHT_BLUE "Enter your Search choice: " RESET);

        if (scanf("%d", &searchchoice) != 1)
        {
            printf(RED "Invalid choice! Enter Valid Choice.\n" RESET);
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (searchchoice)
        {
        /* SEARCH BY NAME */
        case 1:
            found = 0;

            printf(BRIGHT_BLUE "Enter the name: " RESET);
            scanf(" %99[^\n]", str);

            /* First find whether contact exists */
            for (i = 0; i < book->count; i++)
            {
                if (strncmp(book->Contacts[i].name, str, strlen(str)) == 0)
                {
                    found = 1;
                    break;
                }
            }

            /* If not found, don't display table */
            if (found == 0)
            {
                printf("\n");
                printf(RED "Contact Not Found\n" RESET);
                break;
            }
            /* Display table only if contact is found */
            printf("\n");
            printf("+-------+--------------------------+----------------+-----------------------------------------+\n");
            printf("| %-5s | %-24s | %-14s | %-39s |\n", "INDEX", "NAME", "PHONE", "EMAIL");
            printf("+-------+--------------------------+----------------+-----------------------------------------+\n");

            for (i = 0; i < book->count; i++)
            {
                if (strncmp(book->Contacts[i].name, str, strlen(str)) == 0)
                {
                    printf("| %-5d | %-24s | %-14s | %-39s |\n", i + 1, book->Contacts[i].name, book->Contacts[i].number, book->Contacts[i].email);
                }
            }
            printf("+-------+--------------------------+----------------+-----------------------------------------+\n");

            break;
        /* SEARCH BY PHONE */
        case 2:
            found = 0;

            printf(BRIGHT_BLUE "Enter the number: " RESET);
            scanf("%99s", str);

            /* First find whether contact exists */
            for (i = 0; i < book->count; i++)
            {
                if (strncmp(book->Contacts[i].number, str, strlen(str)) == 0)
                {
                    found = 1;
                    break;
                }
            }

            /* If not found */
            if (found == 0)
            {
                printf("\n");
                printf(RED "Contact Not Found\n" RESET);
                break;
            }
            /* Display table */
            printf("\n");
            printf("+-------+--------------------------+----------------+-----------------------------------------+\n");
            printf("| %-5s | %-24s | %-14s | %-39s |\n", "INDEX", "NAME", "PHONE", "EMAIL");
            printf("+-------+--------------------------+----------------+-----------------------------------------+\n");

            for (i = 0; i < book->count; i++)
            {
                if (strncmp(book->Contacts[i].number, str, strlen(str)) == 0)
                {
                    printf("| %-5d | %-24s | %-14s | %-39s |\n", i + 1, book->Contacts[i].name, book->Contacts[i].number, book->Contacts[i].email);
                }
            }
            printf("+-------+--------------------------+----------------+-----------------------------------------+\n");
            break;

        /* SEARCH BY EMAIL */
        case 3:
            found = 0;

            printf(BRIGHT_BLUE "Enter the email: " RESET);
            scanf("%99s", str);

            /* First find whether contact exists */
            for (i = 0; i < book->count; i++)
            {
                if (strncmp(book->Contacts[i].email, str, strlen(str)) == 0)
                {
                    found = 1;
                    break;
                }
            }

            /* If not found, don't display table */
            if (found == 0)
            {
                printf("\n");
                printf(RED "Contact Not Found\n" RESET);
                break;
            }
            /* Display table */
            printf("\n");
            printf("+-------+--------------------------+----------------+-----------------------------------------+\n");
            printf("| %-5s | %-24s | %-14s | %-39s |\n", "INDEX", "NAME", "PHONE", "EMAIL");
            printf("+-------+--------------------------+----------------+-----------------------------------------+\n");

            for (i = 0; i < book->count; i++)
            {
                if (strncmp(book->Contacts[i].email, str, strlen(str)) == 0)
                {
                    printf("| %-5d | %-24s | %-14s | %-39s |\n", i + 1, book->Contacts[i].name, book->Contacts[i].number, book->Contacts[i].email);
                }
            }

            printf("+-------+--------------------------+----------------+-----------------------------------------+\n");

            break;

        /* EXIT */
        case 4:
            printf("\nExit Search Menu\n");
            break;

        default:
            printf(RED "Invalid Choice! Please Choose Valid Option\n" RESET);
        }

    } while (searchchoice != 4);
}

/* EDIT CONTACT */
void editcontact(addressbook *book)
{
    int choice;
    int i;
    int selected;
    int found;
    int match_count;
    int match[100];

    char search[100];
    char tempname[50];
    char tempnumber[15];
    char tempemail[50];

    /* Check whether address book is empty */
    if (book->count == 0)
    {
        printf(GREEN "Address Book is Empty\n" RESET);
        return;
    }

    while (1)
    {
        printf("\n");
        printf("+-----------------------------------+\n");
        printf("|            EDIT CONTACT           |\n");
        printf("+-----------------------------------+\n");
        printf("|  [1] -> Edit using Name           |\n");
        printf("|  [2] -> Edit using Phone Number   |\n");
        printf("|  [3] -> Edit using Email ID       |\n");
        printf("|  [4] -> Edit using All            |\n");
        printf("|  [5] -> Exit                      |\n");
        printf("+-----------------------------------+\n");

        printf(BRIGHT_BLUE "Enter your choice: " RESET);
        /* Validate menu choice and clear invalid input */
        if (scanf("%d", &choice) != 1)
        {
            printf(RED "Invalid choice! Please Enter Valid Option.\n" RESET);
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        /* Exit from edit menu */
        if (choice == 5)
        {
            printf("Exit Edit Menu\n");
            return;
        }

        /* Check whether menu choice is within valid range */
        if (choice < 1 || choice > 5)
        {
            printf(RED "Invalid Choice! Please Enter Valid option.\n" RESET);
            continue;
        }

        /* Get the search value based on selected search option */
        if (choice == 1 || choice == 4)
        {
            printf(BRIGHT_BLUE "Enter name to edit: " RESET);
            scanf(" %49[^\n]", search);
        }
        else if (choice == 2)
        {
            printf(BRIGHT_BLUE "Enter phone number to edit: " RESET);
            scanf("%99s", search);
        }
        else
        {
            printf(BRIGHT_BLUE "Enter email ID to edit: " RESET);
            scanf("%99s", search);
        }

        /* Find and store indexes of all matching contacts */
        match_count = 0;

        for (i = 0; i < book->count; i++)
        {
            /* Search contacts by name */
            if ((choice == 1 || choice == 4) &&
                strncmp(book->Contacts[i].name, search, strlen(search)) == 0)
            {
                match[match_count] = i;
                match_count++;
            }

            /* Search contacts by phone number */
            else if (choice == 2 &&
                     strncmp(book->Contacts[i].number, search, strlen(search)) == 0)
            {
                match[match_count] = i;
                match_count++;
            }

            /* Search contacts by email ID */
            else if (choice == 3 &&
                     strncmp(book->Contacts[i].email, search, strlen(search)) == 0)
            {
                match[match_count] = i;
                match_count++;
            }
        }

        /* Handle case when no contact matches the search */
        if (match_count == 0)
        {
            printf(RED "\nContact Not Found!\n" RESET);
            continue;
        }

        /* Display all matching contacts for user selection */
        printf("\n");
        printf(GREEN "                              MATCHING CONTACT(S)\n" RESET);

        printf("+-------+--------------------------+----------------+-----------------------------------------+\n");
        printf("| %-5s | %-24s | %-14s | %-39s |\n",
               "INDEX", "NAME", "PHONE", "EMAIL");
        printf("+-------+--------------------------+----------------+-----------------------------------------+\n");

        for (i = 0; i < match_count; i++)
        {
            int index = match[i];

            printf("| %-5d | %-24s | %-14s | %-39s |\n",
                   index + 1,
                   book->Contacts[index].name,
                   book->Contacts[index].number,
                   book->Contacts[index].email);
        }

        printf("+-------+--------------------------+----------------+-----------------------------------------+\n");

        /*
         * Get the actual contact index to edit.
         * Keep asking until the user enters one of the displayed indexes.
         */
        while (1)
        {
            printf(BRIGHT_BLUE "\nEnter index to edit: " RESET);

            /* Validate the entered index */
            if (scanf("%d", &selected) != 1)
            {
                printf(RED "Invalid index! Please enter valid index.\n" RESET);
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');

            /* Convert 1-based index to 0-based array index */
            selected = selected - 1;

            found = 0;

            /* Verify that selected index belongs to search results */
            for (i = 0; i < match_count; i++)
            {
                if (selected == match[i])
                {
                    found = 1;
                    break;
                }
            }

            /* Reject invalid index and ask again */
            if (found == 0)
            {
                printf(RED "Invalid index!\n" RESET);
                printf(YELLOW "Please enter one of the displayed indexes.\n" RESET);
                continue;
            }

            /* Valid index */
            break;
        }

        /* Edit and validate contact name */
        if (choice == 1 || choice == 4)
        {
            while (1)
            {
                printf(BRIGHT_BLUE "\nEnter new name: " RESET);
                if (scanf("%49[^\n]", tempname) != 1)
                {
                    printf(RED "Invalid Name! Name Should Not be Empty.\n" RESET);
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');

                if (validatename(tempname))
                {
                    strcpy(book->Contacts[selected].name, tempname);
                    break;
                }
            }
        }

        /* Edit phone number and check for duplicate numbers */
        if (choice == 2 || choice == 4)
        {
            while (1)
            {
                printf(BRIGHT_BLUE "Enter new phone number: " RESET);
                if (scanf("%49[^\n]", tempnumber) != 1)
                {
                    printf(RED "Invalid Number! Number should Not Be Empty.\n" RESET);
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');

                /* Allow the selected contact to retain its existing number */
                if (strcmp(tempnumber, book->Contacts[selected].number) == 0)
                {
                    break;
                }

                if (validatenumber(tempnumber, book, selected))
                {
                    strcpy(book->Contacts[selected].number, tempnumber);
                    break;
                }
            }
        }

        /* Edit email ID and check for duplicate email IDs */
        if (choice == 3 || choice == 4)
        {
            while (1)
            {
                printf(BRIGHT_BLUE "Enter new email ID: " RESET);
                if (scanf("%49[^\n]", tempemail) != 1)
                {
                    printf(RED "Invalid Email! Email Should Not be Empty.\n" RESET);
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');

                /* Allow the selected contact to retain its existing email */
                if (strcmp(tempemail, book->Contacts[selected].email) == 0)
                {
                    break;
                }

                if (validateemail(tempemail, book, selected))
                {
                    strcpy(book->Contacts[selected].email, tempemail);
                    break;
                }
            }
        }

        /* Display the updated contact details */
        printf("\n");
        printf("+--------------------------------------+\n");
        printf("|        UPDATED CONTACT DETAILS       |\n");
        printf("+--------------------------------------+\n");
        printf("| Index : %-29d|\n", selected + 1);
        printf("| Name  : %-29s|\n", book->Contacts[selected].name);
        printf("| Phone : %-29s|\n", book->Contacts[selected].number);
        printf("| Email : %-29s|\n", book->Contacts[selected].email);
        printf("+--------------------------------------+\n");

        return;
    }
}
/* DELETE CONTACT */
void deletecontact(addressbook *book)
{
    int choice, i, selected, confirm;
    int found, match_count;
    int match[100];
    char search[100];

    /* Check whether the address book is empty before deletion. */
    if (book->count == 0)
    {
        printf(YELLOW "Address Book is Empty\n" RESET);
        return;
    }

    /* Repeat the delete operation until the user chooses Exit. */
    while (1)
    {
        printf("\n");
        printf("+--------------------------------------+\n");
        printf("|            DELETE CONTACT            |\n");
        printf("+--------------------------------------+\n");
        printf("|  [1] -> Delete using Name            |\n");
        printf("|  [2] -> Delete using Phone Number    |\n");
        printf("|  [3] -> Delete using Email ID        |\n");
        printf("|  [4] -> Exit                         |\n");
        printf("+--------------------------------------+\n");

        printf(BRIGHT_BLUE "Enter your choice: " RESET);

        /* Handle invalid menu input and clear the input buffer. */
        if (scanf("%d", &choice) != 1)
        {
            printf(RED "Invalid choice!\n" RESET);
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        /* Exit the delete menu when the user selects option 4. */
        if (choice == 4)
        {
            printf("Exit Delete Menu\n");
            return;
        }

        /* Validate that the selected menu option is within the valid range. */
        if (choice < 1 || choice > 4)
        {
            printf(RED "Invalid Choice!\n" RESET);
            continue;
        }

        /* Read the search value based on the selected search option. */
        if (choice == 1)
        {
            printf(BRIGHT_BLUE "Enter the name: " RESET);
            scanf(" %99[^\n]", search);
        }
        else if (choice == 2)
        {
            printf(BRIGHT_BLUE "Enter the phone number: " RESET);
            scanf("%99s", search);
        }
        else
        {
            printf(BRIGHT_BLUE "Enter the email ID: " RESET);
            scanf("%99s", search);
        }

        match_count = 0;

        /* Find and store the indexes of all contacts matching the search value. */
        for (i = 0; i < book->count; i++)
        {
            if (choice == 1 &&
                strncmp(book->Contacts[i].name, search, strlen(search)) == 0)
            {
                match[match_count++] = i;
            }
            else if (choice == 2 &&
                     strncmp(book->Contacts[i].number, search, strlen(search)) == 0)
            {
                match[match_count++] = i;
            }
            else if (choice == 3 &&
                     strncmp(book->Contacts[i].email, search, strlen(search)) == 0)
            {
                match[match_count++] = i;
            }
        }

        /* Check whether at least one matching contact was found. */
        if (match_count == 0)
        {
            printf(RED "Contact Not Found!\n" RESET);
            continue;
        }

        /* Display the matching contacts. */
        printf(GREEN "\n                               MATCHING CONTACT(S)\n" RESET);

        printf("+-------+--------------------------+----------------+-----------------------------------------+\n");
        printf("| %-5s | %-24s | %-14s | %-39s |\n",
               "INDEX", "NAME", "PHONE", "EMAIL");
        printf("+-------+--------------------------+----------------+-----------------------------------------+\n");

        /* Display all matching contacts with their actual indexes. */
        for (i = 0; i < match_count; i++)
        {
            int index = match[i];

            printf("| %-5d | %-24s | %-14s | %-39s |\n",
                   index + 1,
                   book->Contacts[index].name,
                   book->Contacts[index].number,
                   book->Contacts[index].email);
        }

        printf("+-------+--------------------------+----------------+-----------------------------------------+\n");

        /*
         * Keep asking for the delete index until
         * the user enters one of the displayed indexes.
         */
        while (1)
        {
            printf(BRIGHT_BLUE "\nEnter index to delete: " RESET);

            /* Validate the entered index. */
            if (scanf("%d", &selected) != 1)
            {
                printf(RED "Invalid index!\n" RESET);
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');

            /* Convert 1-based index to 0-based array index. */
            selected = selected - 1;

            found = 0;

            /* Validate that the entered index belongs to the matching contacts. */
            for (i = 0; i < match_count; i++)
            {
                if (selected == match[i])
                {
                    found = 1;
                    break;
                }
            }

            /* If invalid, ask for the delete index again. */
            if (!found)
            {
                printf(RED "Invalid index!\n" RESET);
                printf(YELLOW "Please enter one of the displayed indexes.\n" RESET);
                continue;
            }

            /* Valid index, exit the index-validation loop. */
            break;
        }

        printf(YELLOW "\nContact selected for deletion:\n" RESET);

        /* Display the selected contact and ask for deletion confirmation. */
        printf("+-------+--------------------------+----------------+-----------------------------------------+\n");
        printf("| %-5s | %-24s | %-14s | %-39s |\n",
               "INDEX", "NAME", "PHONE", "EMAIL");
        printf("+-------+--------------------------+----------------+-----------------------------------------+\n");

        printf("| %-5d | %-24s | %-14s | %-39s |\n",
               selected + 1,
               book->Contacts[selected].name,
               book->Contacts[selected].number,
               book->Contacts[selected].email);

        printf("+-------+--------------------------+----------------+-----------------------------------------+\n");

        printf(YELLOW "\nAre you sure you want to delete this contact?\n" RESET);
        printf("1. Yes\n");
        printf("2. No\n");

        printf(BRIGHT_BLUE "Enter your choice: " RESET);

        if (scanf("%d", &confirm) != 1)
        {
            printf(RED "Invalid choice!\n" RESET);
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        /* Delete the selected contact after user confirmation. */
        if (confirm == 1)
        {
            /* Shift the contacts after the deleted contact one position backward. */
            for (i = selected; i < book->count - 1; i++)
            {
                book->Contacts[i] = book->Contacts[i + 1];
            }

            /* Decrease the contact count after successful deletion. */
            book->count--;

            printf(GREEN "\nContact deleted successfully!\n" RESET);
            return;
        }

        /* Cancel the deletion when the user selects No. */
        else if (confirm == 2)
        {
            printf(YELLOW "\nDeletion cancelled.\n" RESET);
            return;
        }

        else
        {
            printf(RED "\nInvalid confirmation choice!\n" RESET);
        }
    }
}
/* VALIDATE NAME */
int validatename(char *name)
{
    int i;
    /* Empty name */
    if (name[0] == '\0')
    {
        printf(RED "Invalid Name! Name Should Not Be Empty.\n" RESET);
        return 0;
    }
    /* Minimum length */
    if (strlen(name) < 4)
    {
        printf(RED "ERROR! Name must contain at least 4 characters.\n" RESET);
        return 0;
    }
    /* First character cannot be space */
    if (name[0] == ' ')
    {
        printf(RED "Invalid Name! First character cannot be space.\n" RESET);
        return 0;
    }
    /* Last character cannot be space */
    if (name[strlen(name) - 1] == ' ')
    {
        printf(RED "Invalid Name! Last character cannot be space.\n" RESET);
        return 0;
    }
    /* Only alphabets and spaces */
    for (i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha((unsigned char)name[i]) && name[i] != ' ')
        {
            printf(RED "ERROR! Name should contain only alphabets.\n" RESET);
            return 0;
        }
    }
    return 1;
}
/* VALIDATE PHONE NUMBER */
int validatenumber(char *number, addressbook *book, int selected)
{
    /* Variable for Number Validations i*/
    int i;
    /* Exactly 10 digits */
    if (strlen(number) != 10)
    {
        printf(RED "Invalid Number! Phone Number Must Contain Exactly 10 Digits.\n" RESET);
        return 0;
    }
    /* Digits only */
    for (i = 0; number[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)number[i]))
        {
            printf(RED "Invalid Number! Number Should Contain Digits Only.\n" RESET);
            return 0;
        }
    }

    /* First digit 6-9 */
    if (number[0] < '6' || number[0] > '9')
    {
        printf(RED "Invalid Number! First Digit Must Be Between 6 and 9.\n" RESET);
        return 0;
    }
    /* Checking For Duplicate Number */
    for (i = 0; i < book->count; i++)
    {
        if (i != selected && strcmp(number, book->Contacts[i].number) == 0)
        {
            printf(RED "Number Already Exists\n" RESET);
            printf(RED "Please try again\n" RESET);
            return 0;
        }
    }
    return 1;
}
/* VALIDATE EMAIL */
int validateemail(char *email, addressbook *book, int selected)
{
    /* Variables for Email Validations */
    int i;
    int at_count = 0;
    int dot_count = 0;
    int at_index = -1;
    int dot_index = -1;
    int length;

    length = strlen(email);

    /* Checking First Character is Space Or Not */
    if (email[0] == ' ')
    {
        printf(RED "Invalid Email! First character should not contain Space\n" RESET);
        return 0;
    }
    /* Check Characters */
    for (i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            at_count++;
            at_index = i;
        }
        else if (email[i] == '.')
        {
            dot_count++;
            dot_index = i;
        }
        /* Only lowercases and digits */
        else if (!islower((unsigned char)email[i]) && !isdigit((unsigned char)email[i]))
        {
            printf(RED "Invalid Email! Use lowercase letters and digits only.\n" RESET);
            return 0;
        }
    }
    /* Exactly one @ */
    if (at_count == 0)
    {
        printf(RED "Invalid Email! Missing @ in email.\n" RESET);
        return 0;
    }
    /* No Multipal @'s */
    if (at_count > 1)
    {
        printf(RED "Invalid Email! Multiple @ are not allowed.\n" RESET);
        return 0;
    }
    /* Exactly one dot */
    if (dot_count == 0)
    {
        printf(RED "Invalid Email! Missing dot in email.\n" RESET);
        return 0;
    }
    /* No Multipal dots */
    if (dot_count > 1)
    {
        printf(RED "Invalid Email! Multiple dots are not allowed.\n" RESET);
        return 0;
    }
    /* Something before @ */
    if (at_index == 0)
    {
        printf(RED "Invalid Email! Something must exist before @.\n" RESET);
        return 0;
    }
    /* @ before dot */
    if (dot_index < at_index)
    {
        printf(RED "Invalid Email! @ should be before dot.\n" RESET);
        return 0;
    }
    /* Something between @ and dot */
    if (dot_index == at_index + 1)
    {
        printf(RED "Invalid Email! At least one character is required between @ and dot.\n" RESET);
        return 0;
    }
    /* Check .com */
    if (dot_index + 4 != length ||
        email[dot_index + 1] != 'c' ||
        email[dot_index + 2] != 'o' ||
        email[dot_index + 3] != 'm')
    {
        printf(RED "Invalid Email! Email should end with .com\n" RESET);
        return 0;
    }
    /* Checking For Duplicate Email */
    for (i = 0; i < book->count; i++)
    {
        if (i != selected && strcmp(email, book->Contacts[i].email) == 0)
        {
            printf(RED "Email Already Exists\n" RESET);
            printf(RED "Try Again\n" RESET);
            return 0;
        }
    }
    return 1;
}
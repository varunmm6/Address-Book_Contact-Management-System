#ifndef HEADER_H
#define HEADER_H

/* Prevents the header file from being included multiple times. */
#define RESET "\033[0m"

/* Defines the red color for error messages. */
#define RED "\033[1;31m"

/* Defines the green color for success messages. */
#define GREEN "\033[0;32m"

/* Defines the bright blue color for prompts and headings. */
#define BRIGHT_BLUE "\033[1;34m"

/* Defines the yellow color for warning messages. */
#define YELLOW "\033[0;33m"

/* Stores the details of a single contact. */
typedef struct
{
    char name[50];
    char number[15];
    char email[50];

} contact;

/* Stores all contacts and the current number of contacts. */
typedef struct
{
    contact Contacts[100];
    int count;

} addressbook;

/* Contact functions */

/* Creates and adds a new contact to the address book. */
void createcontact(addressbook *book);

/* Displays all contacts stored in the address book. */
void listcontact(addressbook *book);

/* Searches for contacts using name, phone number, or email. */
void searchcontact(addressbook *book);

/* Edits the details of an existing contact. */
void editcontact(addressbook *book);

/* Deletes a selected contact from the address book. */
void deletecontact(addressbook *book);

/* Validation functions */

/* Validates the name entered by the user. */
int validatename(char *name);

/* Validates the phone number and checks for duplicate numbers. */
int validatenumber(char *number, addressbook *book, int selected);

/* Validates the email ID and checks for duplicate email addresses. */
int validateemail(char *email, addressbook *book, int selected);

// void savecontacts(addressbook *book);
#endif

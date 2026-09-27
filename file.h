#ifndef FILE_H
#define FILE_H

/* Includes the address book structure and required declarations. */
#include "header.h"

/* Loads saved contacts from the file into the address book. */
void loadcontacts(addressbook *book);

/* Saves the current contacts from the address book to the file. */
void savecontacts(addressbook *book);

#endif
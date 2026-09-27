# 📒 Address Book : Contacts Management System

## 📖 Overview

The **Address Book Management System** is a console-based C project designed to manage contact information in a simple and structured way.

Each contact contains three fields:

- **Name**
- **Phone number**
- **Email address**

The application provides a menu-driven interface for:

1. Create Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. List / Sort Contacts
6. Save and Exit

The project uses an in-memory `addressbook` structure to store up to **100 contacts** and a `contact.txt` file for persistent storage. Saved contacts are loaded when the program starts and written back to the file when the user selects Save and Exit.

## 🎯 Why This Project?

Managing a large number of contacts manually can be difficult. This project demonstrates how C can be used to build a practical contact management application using:

- Structures and arrays
- Functions and pointers
- String handling
- Character handling
- Input validation
- Prefix-based searching
- Editing and deletion
- Bubble sorting
- File handling
- Menu-driven programming
- Formatted and colored terminal output

## 🛠️ Technologies Used

| **Technology / Concept** | **Usage** |
| ------------------------ | --------- |
| **C** | Core programming language |
| **Structures** | Represents `contact` and `addressbook` |
| **Arrays** | Stores up to 100 contacts |
| **Pointers** | Passes the address book to functions |
| **String Handling** | `strlen()`, `strcmp()`, `strncmp()`, `strcpy()` |
| **Character Handling** | `isalpha()`, `isdigit()`, `islower()` |
| **File I/O** | `fopen()`, `fprintf()`, `fscanf()`, `fclose()` |
| **Standard I/O** | `printf()`, `scanf()`, `getchar()` |
| **ANSI Escape Codes** | Colored terminal messages and prompts |
| **Bubble Sort** | Sorts contacts by name, phone number, or email |

The project uses standard C headers including `stdio.h`, `string.h`, and `ctype.h`.

## 🏗️ System Architecture

```text
                 +----------------------+
                 |       main.c         |
                 |    Main Menu / UI    |
                 +----------+-----------+
                            |
                            v
                 +----------------------+
                 |      defination.c    |
                 |                      |
                 | Create               |
                 | Search               |
                 | Edit                 |
                 | Delete               |
                 | List / Sort          |
                 | Validation           |
                 +-----+----------+-----+
                       |          |
                       v          v
              +------------+   +------------+
              |  header.h  |   |   file.c   |
              | Structures |   | Save /Load |
              | Functions  |   +------+-----+
              +------------+          |
                                      v
                               +-------------+
                               | contact.txt |
                               +-------------+
```

## 🔄 Program Flow

```text
                 Program Start
                       |
                       v
              Initialize AddressBook
                       |
                       v
              Load contacts from
                 contact.txt
                       |
                       v
                  Main Menu
                       |
        +--------------+--------------+
        |              |              |
        v              v              v
   Create/Search    Edit/Delete    List/Sort
        |              |              |
        +--------------+--------------+
                       |
                       v
                Save and Exit
                       |
                       v
              savecontacts()
                       |
                       v
                 contact.txt
                       |
                       v
                 Program End
```

## 📂 Project Structure

```text
Address-Book/
│
├── README.md
├── main.c
├── defination.c
├── header.h
├── file.c
├── file.h
└── contact.txt
```

## 🔑 Key Functions

### ➕ Create Contacts

`createcontact()` adds a new contact to the address book.

The function:

- Checks whether the maximum capacity of 100 contacts has been reached.
- Reads the name, phone number, and email ID.
- Validates each input before storing it.
- Stores the validated information in the next available array position.
- Increases the contact count after successful insertion.
- Displays a progress bar and success message.

The contact details are stored using `strcpy()` after successful validation.

### 🔎 Search Contacts

`searchcontact()` searches contacts using:

- Name
- Phone number
- Email ID

The search uses **prefix matching** with `strncmp()`. This means the user can enter the beginning of a name, phone number, or email ID and matching contacts are displayed.

For example, entering a single character or digit can match contacts beginning with that value.

The search results display the actual contact index, name, phone number, and email address.

### ✏️ Edit Contact

`editcontact()` allows the user to modify an existing contact using:

- Name
- Phone number
- Email ID
- All contact details

The program first performs a prefix-based search and displays all matching contacts with their actual indexes.

The user then enters the displayed index to select the contact.

When updating:

- The new name is validated.
- The new phone number is validated and checked for duplicates.
- The new email ID is validated and checked for duplicates.
- Existing phone/email values can be retained.

After updating, the program displays the complete updated contact details.

### 🗑️ Delete Contact

`deletecontact()` allows a contact to be deleted using:

- Name
- Phone number
- Email ID

The program uses prefix matching to find contacts and displays all matching records with their actual indexes.

The user selects the required index and confirms the deletion.

When deletion is confirmed:

- The selected contact is removed.
- Remaining contacts are shifted one position backward.
- The contact count is decreased.
- A successful deletion message is displayed.

Deletion can also be cancelled by selecting the No option.

### ↕️ List / Sort Contacts

`listcontact()` displays all stored contacts and provides sorting options:

1. Sort by Name
2. Sort by Phone
3. Sort by Email
4. Exit

The project uses **Bubble Sort** and compares contact fields using `strcmp()`.

Unlike a temporary-copy sorting approach, the current implementation swaps the complete `contact` structures directly inside the `addressbook` array. Therefore, the selected sorting operation changes the order of contacts in the address book itself.

After sorting, contacts are displayed in a formatted table with:

- Serial number
- Name
- Phone number
- Email address

The display also shows:

- Maximum contacts allowed
- Contacts currently stored
- Available slots

## ✅ Validation

### 👤 Name Validation

`validatename()` checks that:

- The name is not empty.
- The name contains at least 4 characters.
- The first character is not a space.
- The last character is not a space.
- Only alphabets and spaces are allowed.

### 📱 Phone Number Validation

`validatenumber()` checks that:

- The phone number contains exactly 10 digits.
- Only digits are allowed.
- The first digit is between 6 and 9.
- Duplicate phone numbers are rejected.

The `selected` parameter is used during editing so that the current contact can retain its existing phone number without being treated as a duplicate.

### 📧 Email Validation

`validateemail()` checks that:

- The first character is not a space.
- Only lowercase letters and digits are allowed apart from the required `@` and `.` characters.
- Exactly one `@` is present.
- Exactly one `.` is present.
- Something exists before `@`.
- `@` appears before `.`.
- At least one character exists between `@` and `.`.
- The email ends with `.com`.
- Duplicate email addresses are rejected.

The `selected` parameter allows the current contact to retain its existing email ID during editing.

## 💾 File Handling

The project uses **`contact.txt`** to permanently store contacts.

### 📥 Load Contacts

```text
contact.txt
     |
     v
loadcontacts()
     |
     v
AddressBook
```

When the program starts, `loadcontacts()`:

- Opens `contact.txt` in read mode.
- Reads the stored contact count.
- Validates that the count is within the maximum limit of 100.
- Reads each saved contact.
- Loads the contacts into the address book.

If the file does not exist, the program starts with an empty address book.

### 💾 Save Contacts

```text
AddressBook
     |
     v
savecontacts()
     |
     v
contact.txt
```

When the user selects **Save and Exit**, `savecontacts()`:

- Opens `contact.txt` in write mode.
- Stores the total contact count.
- Writes each contact with its index, name, phone number, and email.
- Closes the file after saving.

Example file format:

```text
Contact Counts: 16
1: Yashu M R,7412589630,yashumr123@gmail.com
2: Prajwal k b,7485963210,prajwalkb123@gmail.com
3: Giresh,7531598641,gireshb12@gmail.com
```

## 🖥️ Main Menu

The application provides the following menu:

```text
┌──────────────────────────────┐
│       📒 ADDRESS BOOK        │
├──────────────────────────────┤
│  ✚  1. Create contact        │
│  🔍 2. Search contact        │
│  ✎  3. Edit contact          │
│  ✖  4. Delete contact        │
│  ☷  5. List all contacts     │
│  ✓  6. Save and Exit         │
└──────────────────────────────┘
```

The main function initializes the address book, loads saved contacts, displays the menu, and calls the corresponding function based on the user's choice.

## 🚀 How to Run

### 🔧 Compile

```bash
gcc main.c defination.c file.c -o addressbook
```

### ▶️ Run

```bash
./addressbook
```

Make sure `contact.txt` is present in the same working directory when running the program so previously saved contacts can be loaded.

## 📊 Contact Capacity

The address book can store a maximum of **100 contacts**.

```text
Maximum Contacts Allowed : 100
```

The program checks the capacity before creating a new contact and displays a message when the address book is full.

## 📚 Learnings & Outcomes

- Improved practical C programming skills.
- Learned to design and use structures for real-world data.
- Gained experience with arrays and pointers.
- Practiced modular programming using multiple `.c` and `.h` files.
- Implemented input validation using string and character functions.
- Learned prefix-based searching using `strncmp()`.
- Implemented editing and deletion using array indexes.
- Implemented Bubble Sort for contact organization.
- Gained practical experience with file handling using `fopen()`, `fscanf()`, `fprintf()`, and `fclose()`.
- Learned to maintain contact data between program executions.
- Improved debugging, input handling, and menu-driven programming skills.
- Used ANSI escape codes to improve terminal output and user interaction.

## ⭐ Project Summary

> **Address Book Management System** is a menu-driven C application that manages up to 100 contacts with validated name, phone number, and email information. It supports prefix-based searching, contact editing, deletion with confirmation, sorting using Bubble Sort, and persistent storage through `contact.txt`.

## 👨‍💻 Author

**Varun M M**


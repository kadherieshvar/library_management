
#include <stdio.h>
#include <string.h>

#define MAX 50

int count = 0;

void clearInput();
int findById(int id[], int searchId);

void addBook(int id[], char name[][50], char author[][50],
             char category[][30], float price[], int available[]);

void displayBooks(int id[], char name[][50], char author[][50],
                  char category[][30], float price[], int available[]);

void searchById(int id[], char name[][50], char author[][50],
                char category[][30], float price[], int available[]);

void searchByName(int id[], char name[][50], char author[][50],
                  char category[][30], float price[], int available[]);

void issueBook(int id[], int available[]);
void returnBook(int id[], int available[]);

void updateBook(int id[], char name[][50], char author[][50],
                char category[][30], float price[]);

void countBooks();
void displayAvailable(int id[], char name[][50], char author[][50],
                      char category[][30], float price[], int available[]);

int main()
{
    int id[MAX], available[MAX];
    char name[MAX][50], author[MAX][50], category[MAX][30];
    float price[MAX];

    int choice;

    do
    {
        printf("\n========== LIBRARY MANAGEMENT SYSTEM ==========\n");
        printf("1. Add New Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book by ID\n");
        printf("4. Search Book by Name\n");
        printf("5. Issue Book\n");
        printf("6. Return Book\n");
        printf("7. Update Book Details\n");
        printf("8. Count Total Books\n");
        printf("9. Display Available Books\n");
        printf("10. Exit\n");

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            clearInput();
            continue;
        }

        clearInput();

        switch (choice)
        {
            case 1:
                addBook(id, name, author, category, price, available);
                break;

            case 2:
                displayBooks(id, name, author, category, price, available);
                break;

            case 3:
                searchById(id, name, author, category, price, available);
                break;

            case 4:
                searchByName(id, name, author, category, price, available);
                break;

            case 5:
                issueBook(id, available);
                break;

            case 6:
                returnBook(id, available);
                break;

            case 7:
                updateBook(id, name, author, category, price);
                break;

            case 8:
                countBooks();
                break;

            case 9:
                displayAvailable(id, name, author, category, price, available);
                break;

            case 10:
                printf("\nThank you for using Library Management System!\n");
                break;

            default:
                printf("\nInvalid choice! Select 1 to 10.\n");
        }

    } while (choice != 10);

    return 0;
}

void clearInput()
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

int findById(int id[], int searchId)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (id[i] == searchId)
            return i;
    }

    return -1;
}

void addBook(int id[], char name[][50], char author[][50],
             char category[][30], float price[], int available[])
{
    int newId;

    if (count >= MAX)
    {
        printf("\nLibrary is full!\n");
        return;
    }

    printf("Enter Book ID: ");

    if (scanf("%d", &newId) != 1)
    {
        printf("Invalid ID!\n");
        clearInput();
        return;
    }

    clearInput();

    if (findById(id, newId) != -1)
    {
        printf("Duplicate Book ID!\n");
        return;
    }

    id[count] = newId;

    printf("Enter Book Name: ");
    scanf(" %49[^\n]", name[count]);

    printf("Enter Author Name: ");
    scanf(" %49[^\n]", author[count]);

    printf("Enter Category: ");
    scanf(" %29[^\n]", category[count]);

    printf("Enter Price: ");

    if (scanf("%f", &price[count]) != 1 || price[count] < 0)
    {
        printf("Invalid Price!\n");
        clearInput();
        return;
    }

    clearInput();

    available[count] = 1;
    count++;

    printf("\nBook added successfully!\n");
}

void displayBooks(int id[], char name[][50], char author[][50],
                  char category[][30], float price[], int available[])
{
    int i;

    if (count == 0)
    {
        printf("\nNo books found!\n");
        return;
    }

    for (i = 0; i < count; i++)
    {
        printf("\nBook ID: %d\n", id[i]);
        printf("Book Name: %s\n", name[i]);
        printf("Author: %s\n", author[i]);
        printf("Category: %s\n", category[i]);
        printf("Price: %.2f\n", price[i]);

        printf("Status: %s\n",
               available[i] ? "Available" : "Issued");
    }
}

void searchById(int id[], char name[][50], char author[][50],
                char category[][30], float price[], int available[])
{
    int searchId, index;

    printf("Enter Book ID: ");

    if (scanf("%d", &searchId) != 1)
    {
        printf("Invalid ID!\n");
        clearInput();
        return;
    }

    clearInput();

    index = findById(id, searchId);

    if (index == -1)
    {
        printf("Book not found!\n");
        return;
    }

    printf("\nBook Found!\n");
    printf("Name: %s\n", name[index]);
    printf("Author: %s\n", author[index]);
    printf("Category: %s\n", category[index]);
    printf("Price: %.2f\n", price[index]);
    printf("Status: %s\n",
           available[index] ? "Available" : "Issued");
}

void searchByName(int id[], char name[][50], char author[][50],
                  char category[][30], float price[], int available[])
{
    char searchName[50];
    int i, found = 0;

    printf("Enter Book Name: ");
    scanf(" %49[^\n]", searchName);

    for (i = 0; i < count; i++)
    {
        if (strcmp(name[i], searchName) == 0)
        {
            printf("\nBook Found!\n");
            printf("ID: %d\n", id[i]);
            printf("Name: %s\n", name[i]);
            printf("Author: %s\n", author[i]);
            printf("Category: %s\n", category[i]);
            printf("Price: %.2f\n", price[i]);
            printf("Status: %s\n",
                   available[i] ? "Available" : "Issued");

            found = 1;
        }
    }

    if (!found)
        printf("\nBook not found!\n");
}

void issueBook(int id[], int available[])
{
    static int issueCount = 0;

    int searchId, index;

    printf("Enter Book ID to issue: ");

    if (scanf("%d", &searchId) != 1)
    {
        printf("Invalid ID!\n");
        clearInput();
        return;
    }

    clearInput();

    index = findById(id, searchId);

    if (index == -1)
        printf("Book not found!\n");

    else if (available[index] == 0)
        printf("Book already issued!\n");

    else
    {
        available[index] = 0;
        issueCount++;

        printf("Book issued successfully!\n");
        printf("Total issue operations: %d\n", issueCount);
    }
}

void returnBook(int id[], int available[])
{
    int searchId, index;

    printf("Enter Book ID to return: ");

    if (scanf("%d", &searchId) != 1)
    {
        printf("Invalid ID!\n");
        clearInput();
        return;
    }

    clearInput();

    index = findById(id, searchId);

    if (index == -1)
        printf("Book not found!\n");

    else if (available[index] == 1)
        printf("Book is already available!\n");

    else
    {
        available[index] = 1;
        printf("Book returned successfully!\n");
    }
}

void updateBook(int id[], char name[][50], char author[][50],
                char category[][30], float price[])
{
    int searchId, index, choice;

    printf("Enter Book ID to update: ");

    if (scanf("%d", &searchId) != 1)
    {
        printf("Invalid ID!\n");
        clearInput();
        return;
    }

    clearInput();

    index = findById(id, searchId);

    if (index == -1)
    {
        printf("Book not found!\n");
        return;
    }

    printf("\n1. Update Book Name\n");
    printf("2. Update Author Name\n");
    printf("3. Update Category\n");
    printf("4. Update Price\n");

    printf("Enter choice: ");

    if (scanf("%d", &choice) != 1)
    {
        printf("Invalid choice!\n");
        clearInput();
        return;
    }

    clearInput();

    switch (choice)
    {
        case 1:
            printf("Enter New Book Name: ");
            scanf(" %49[^\n]", name[index]);
            break;

        case 2:
            printf("Enter New Author Name: ");
            scanf(" %49[^\n]", author[index]);
            break;

        case 3:
            printf("Enter New Category: ");
            scanf(" %29[^\n]", category[index]);
            break;

        case 4:
            printf("Enter New Price: ");

            if (scanf("%f", &price[index]) != 1 || price[index] < 0)
            {
                printf("Invalid price!\n");
                clearInput();
                return;
            }

            clearInput();
            break;

        default:
            printf("Invalid choice!\n");
            return;
    }

    printf("\nBook updated successfully!\n");
}

void countBooks()
{
    printf("\nTotal Books: %d\n", count);
}

void displayAvailable(int id[], char name[][50], char author[][50],
                      char category[][30], float price[], int available[])
{
    int i, found = 0;

    printf("\n========== AVAILABLE BOOKS ==========\n");

    for (i = 0; i < count; i++)
    {
        if (available[i] == 1)
        {
            printf("\nID: %d\n", id[i]);
            printf("Name: %s\n", name[i]);
            printf("Author: %s\n", author[i]);
            printf("Category: %s\n", category[i]);
            printf("Price: %.2f\n", price[i]);

            found = 1;
        }
    }

    if (!found)
        printf("No available books!\n");
}

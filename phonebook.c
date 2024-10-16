#include <stdio.h>
#include <string.h>
#define MAX_PEOPLE 100
struct Person
{
    char fname[100];
    char lname[100];
    char street[100];
    int streetno;
    long int telno;
};

void printPerson(struct Person p)
{
    printf("First name: %s\n", p.fname);
    printf("Last name: %s\n", p.lname);
    printf("Address: %s %d\n", p.street, p.streetno);
    printf("Telephone number: %ld\n", p.telno);
}

struct Person createPerson(const char *fname, const char *lname, const char *street, int streetno, long int telno)
{
    struct Person p;
    strcpy(p.fname, fname);
    strcpy(p.lname, lname);
    strcpy(p.street, street);
    // strcpy(p.telno, telno);
    p.streetno = streetno;
    p.telno = telno;
    return p;
}

struct phonebook
{
    struct Person people[MAX_PEOPLE];
    int count; // current amount of records in phonebook
};

void printPhonebook(struct phonebook *pb)
{
    printf("\n ////////////// Phonebook Entries: ////////////// \n");
    for (int i = 0; i < pb->count; i++)
    {
        printPerson(pb->people[i]);
        printf("\n");
    }
    if (pb->count == 0)
    {
        printf("Phonebook is currently empty, no records found.\n");
    }
}
void addPerson(struct phonebook *pb, const char *fname, const char *lname, const char *street, int streetno, long int telno)
{
    struct Person p = createPerson(fname, lname, street, streetno, telno);
    if (pb->count < MAX_PEOPLE)
    {
        pb->people[pb->count] = p;
        pb->count++;
        printf("COUNT COUNT COUNT \n");
    }
}

void insertPerson(struct phonebook *pb)
{
    char fname[100];
    char lname[100];
    char street[100];
    int streetno;
    long int telno;

    getchar(); // consume newline character from fscan
    printf("Enter first name: ");
    fgets(fname, sizeof(fname), stdin);
    // Remove the newline character at the end if it exists

    printf("Enter last name: ");
    fgets(lname, sizeof(lname), stdin);
    // Remove the newline character at the end if it exists

    printf("Enter street name: ");
    fgets(street, sizeof(street), stdin);
    // Remove the newline character at the end if it exists
    fname[strcspn(fname, "\n")] = '\0';   // Remove the newline, if any
    lname[strcspn(lname, "\n")] = '\0';   // Remove the newline, if any
    street[strcspn(street, "\n")] = '\0'; // Remove the newline, if any

    printf("Enter street number: ");
    scanf("%d", &streetno);

    printf("Enter telephone number: ");
    scanf("%ld", &telno);
    // Remove the newline character at the end if it exists

    addPerson(pb, fname, lname, street, streetno, telno);
}
void menu(struct phonebook *pb);
void searchPerson(struct phonebook *pb)
{
    printf("If you want to search a person by name, type 1.\nIf you want to search by telephone number, press 2.\nTo go back to the menu, press 3.\nEnter number:");
    // printf("press 1 to add person\n");
    int choice;
    scanf("%d", &choice);
    getchar();
    if (choice == 1)
    {
        char fname[100];
        char lname[100];
        printf("Enter first name: ");
        fgets(fname, sizeof(fname), stdin);
        // Remove the newline character at the end if it exists

        printf("Enter last name: ");
        fgets(lname, sizeof(lname), stdin);
        fname[strcspn(fname, "\n")] = '\0'; // Remove the newline, if any
        lname[strcspn(lname, "\n")] = '\0'; // Remove the newline, if any

        int f = 0;
        for (int i = 0; i < pb->count; i++)
        {

            if (strcmp(fname, pb->people[i].fname) == 0 && strcmp(lname, pb->people[i].lname) == 0)
            {
                printf("Person found.");
                printPerson(pb->people[i]);
                f = 1;

                break;
            }
        }
        if (f == 0)
        {
            printf("Person not found.\n");
        }
    }
    else if (choice == 2)
    {
        long int telno;
        scanf("%ld", &telno);
        getchar();
        int f = 0;
        for (int i = 0; i < pb->count; i++)
        {
            if (pb->people[i].telno == telno)
            {
                printf("Person found.\n");
                printPerson(pb->people[i]);
                f = 1;
                break;
            }
        }
        if (f == 0)
        {
            printf("Person not found.\n");
        }
    }
    else if (choice == 3)
    {
        menu(pb);
    }
};

struct Person searchPersonByTelno(struct phonebook *pb)
{
    long int telno;
    scanf("%ld", &telno);
    getchar();
    int f = 0;
    for (int i = 0; i < pb->count; i++)
    {
        if (pb->people[i].telno == telno)
        {
            return pb->people[i];
            f = 1;
            break;
        }
    }
    if (f == 0)
    {
        printf("Person not found.\n");
    }
}
void modifyPerson(struct phonebook *pb)
{
    printf("If you want to modify a person's name, press 1.\nIf you want to change a person's telephone number, press 2.\nTo go back to the menu, press 3.\nEnter number:");
    int choice;
    scanf("%d", &choice);
    getchar();
    if (choice == 1)
    {
        char fname[100];
        char lname[100];
        printf("Enter first name: ");
        fgets(fname, sizeof(fname), stdin);
        // Remove the newline character at the end if it exists

        printf("Enter last name: ");
        fgets(lname, sizeof(lname), stdin);
        fname[strcspn(fname, "\n")] = '\0'; // Remove the newline, if any
        lname[strcspn(lname, "\n")] = '\0'; // Remove the newline, if any

        char newfname[100];
        char newlname[100];
        printf("Enter new first name: ");
        fgets(newfname, sizeof(newfname), stdin);
        // Remove the newline character at the end if it exists

        printf("Enter new last name: ");
        fgets(newlname, sizeof(newlname), stdin);
        newfname[strcspn(newfname, "\n")] = '\0'; // Remove the newline, if any
        newlname[strcspn(newlname, "\n")] = '\0'; // Remove the newline, if any

        int f = 0;
        for (int i = 0; i < pb->count; i++)
        {
            if (strcmp(fname, pb->people[i].fname) == 0 && strcmp(lname, pb->people[i].lname) == 0)
            {
                printf("Person found.");
                strcpy(pb->people[i].fname, newfname);
                strcpy(pb->people[i].lname, newlname);
                printf("Change made.\n");
                f = 1;
                break;
            }
        }
        if (f == 0)
        {
            printf("Person not found.\n");
        }
    }
    else if (choice == 2)
    {
        char fname[100];
        char lname[100];
        printf("Enter first name: ");
        fgets(fname, sizeof(fname), stdin);
        // Remove the newline character at the end if it exists

        printf("Enter last name: ");
        fgets(lname, sizeof(lname), stdin);
        fname[strcspn(fname, "\n")] = '\0'; // Remove the newline, if any
        lname[strcspn(lname, "\n")] = '\0'; // Remove the newline, if any

        printf("Enter new phone number:");
        long int telno;
        scanf("%ld", &telno);
        getchar();
        int f = 0;
        for (int i = 0; i < pb->count; i++)
        {
            if (strcmp(fname, pb->people[i].fname) == 0 && strcmp(lname, pb->people[i].lname) == 0)
            {
                printf("Person found.");

                f = 1;
                pb->people[i].telno = telno;
                printf("Change made.\n");
                break;
            }
        }
        if (f == 0)
        {
            printf("Person not found.\n");
        }
    }
}

void deletePerson(struct phonebook *pb)
{
    int choice;
    printf("Are you sure you want to delete a person? Press 1 to continue, press 0 to return to menu.\nEnter number:");
    scanf("%d", &choice);
    getchar();
    if (choice == 1)
    {
        char fname[100];
        char lname[100];
        printf("Enter first name: ");
        fgets(fname, sizeof(fname), stdin);
        // Remove the newline character at the end if it exists

        printf("Enter last name: ");
        fgets(lname, sizeof(lname), stdin);
        fname[strcspn(fname, "\n")] = '\0'; // Remove the newline, if any
        lname[strcspn(lname, "\n")] = '\0'; // Remove the newline, if any

        int f = 0;
        for (int i = 0; i < pb->count; i++)
        {
            if (strcmp(fname, pb->people[i].fname) == 0 && strcmp(lname, pb->people[i].lname) == 0)
            {
                printf("Person found.");
                // we're going to switch person[i] with the last person (position:count) and then decrease count, effectively deleting the entry
                pb->people[i] = pb->people[pb->count - 1];
                pb->count--;
                printf("Person deleted.\n");
                f = 1;
                break;
            }
        }
        if (f == 0)
        {
            printf("Person not found.\n");
        }
    }
    else if (choice == 0)
    {
        menu(pb);
    }
}

void menu(struct phonebook *pb)
{

    int choice;
    do
    {
        printf("\n /////////Menu/////////\n");
        printf("Press 1 to add a person\n");
        printf("Press 2 to search a person.\n");
        printf("press 3 to print entire phonebook\n");
        printf("Press 4 to modify a person's details.\n");
        printf("Press 5 to delete a person.\n");
        printf("Press 0 to exit program.\n");
        printf("Enter number:\n");

        scanf("%d", &choice);
        if (choice == 1)
        {
            insertPerson(pb);
        }
        else if (choice == 2)
        {

            searchPerson(pb);
        }
        else if (choice == 3)
        {
            printPhonebook(pb);
        }
        else if (choice == 4)
        {
            modifyPerson(pb);
        }
        else if (choice == 5)
        {
            deletePerson(pb);
        }
    } while (choice != 0);
}

int main()
{
    struct Person p = createPerson("giannis", "papadopoulos", "mpiglistas", 91, 6906885523);
    // printPerson(p);

    struct phonebook book;
    book.count = 0;
    // addPerson(&book, "John", "johnis", "Devoil", 12, 69362223);
    menu(&book);
    // printPhonebook(&book);
}

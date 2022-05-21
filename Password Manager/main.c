#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

void add_entry();

void view_entry();

void delete_entry();

void generate_password();

struct manager {
    char name[17];
    char password[16];
    int crypt[16];
};

int main() {
    char x;
    printf("\t\t**********************\t\t\n");
    printf("\t\t***Password_manager***\t\t\n");
    printf("\t\t**********************\t\t\n");
    while (1) {
        printf("\n\t\t******Main_meniu******\t\t\n");
        printf("\n\t\tAdd password to manage\t [1]");
        printf("\n\t\tView passwords entered\t [2]");
        printf("\n\t\tDelete a password\t [3]");
        printf("\n\t\tGenerate random password [4]");
        printf("\n\t\tExit\t\t\t [5]");
        printf("\n\t\tSelect an option:");
        scanf("%c", &x);
        fflush(stdin);
        switch (x) {
            case '1':
                add_entry();
                break;
            case '2':
                view_entry();
                break;
            case '3':
                delete_entry();
                break;
            case '4':
                generate_password();
                break;
            case '5':
                exit(0);
            default:
                printf("\n\t\tInput error!\n\t\tPress enter and try again!");
                getch();
                fflush(stdin);
                break;
        }
    }
}

void add_entry() {
    struct manager entry;
    char reader[32];
    FILE *memory;
    srand(time(0));

    printf("\n\t\t*****New_Password*****\t\t");
    printf("\n\t\tAdd a name for the password:");
    scanf("%s", entry.name);
    fflush(stdin);

    memory = fopen("Index", "r+");
    if (memory == NULL) {
        printf("\n\t\tFile error!");
        printf("\n\t\tPress enter to continue!");
        getch();
        fflush(stdin);
        return;
    }

    while (fgets(reader, 17, memory) != NULL) {
        reader[strcspn(reader, "\n")] = 0;
        if (strcmp(reader, entry.name) == 0) {
            fclose(memory);
            printf("\n\t\tThis name is already taken!");
            printf("\n\t\tPress enter to continue!");
            getch();
            fflush(stdin);
            return;
        }
    }

    printf("\n\t\tAdd the password:");
    scanf("%s", entry.password);
    fflush(stdin);
    for (int i = 0; i < entry.password[i]; i++) {
        entry.crypt[i] = (rand() % 9) + 1;
        entry.password[i] ^= entry.crypt[i];
    }
    fclose(memory);
    memory = fopen("Index", "a");
    fprintf(memory, "%s\n", entry.name);

    FILE *f = fopen(entry.name, "wb");
    if (f == NULL) {
        printf("\n\t\tFile error!");
        printf("\n\t\tPress enter to continue!");
        getch();
        fflush(stdin);
        return;
    }
    for (int i = 0; i < entry.password[i]; i++) {
        fwrite(&entry.password[i], sizeof(char), 1, f);
        fwrite(&entry.crypt[i], sizeof(int), 1, f);
    }

    fclose(f);
    fclose(memory);
    printf("\n\t\tOperation completed successfully!\n\t\tPress enter to continue!");
    getch();
    fflush(stdin);
}

void view_entry() {
    struct manager entry;
    char reader[32];
    FILE *memory;

    printf("\n\t\t****View_Passwords****\t\t");
    printf("\n\t\tIndex entries:\n");

    memory = fopen("Index", "r");
    if (memory == NULL) {
        printf("\n\t\tFile error!");
        printf("\n\t\tPress enter to continue!");
        getch();
        fflush(stdin);
        return;
    }

    while (fgets(reader, 17, memory) != NULL)
        printf("\t\t%s", reader);

    printf("\n\t\tSelect an entry to view:");
    scanf("%s", &entry.name);
    fflush(stdin);
    FILE *f = fopen(entry.name, "rb");
    if (f == NULL) {
        printf("\n\t\tFile error!");
        printf("\n\t\tPress enter to continue!");
        getch();
        fflush(stdin);
        return;
    }

    int contor = 0;
    while (!feof(f)) {
        fread(&entry.password[contor], sizeof(char), 1, f);
        fread(&entry.crypt[contor], sizeof(int), 1, f);
        entry.password[contor] ^= entry.crypt[contor];
        contor++;
    }
    entry.password[contor - 1] = NULL;
    printf("\n\t\t%s: %s", entry.name, entry.password);
    fclose(memory);
    fclose(f);
    printf("\n\t\tPress enter to continue!");
    getch();
    fflush(stdin);
}

void delete_entry() {
    char name[32];
    char reader[32];
    FILE *memory;
    FILE *faux;

    printf("\n\t\t***Delete_Passwords***\t\t");
    printf("\n\t\tAvailable Passwords:\n");
    memory = fopen("Index", "r+");
    if (memory == NULL) {
        printf("\n\t\tFile error!");
        printf("\n\n\t\tPress enter to continue!");
        getch();
        fflush(stdin);
        return;
    }

    while (fgets(reader, 17, memory) != NULL)
        printf("\t\t%s", reader);

    printf("\n\t\tSelect an entry to delete:");
    scanf("%s", &name);
    fflush(stdin);
    rewind(memory);

    if (remove(name) == 0)
        printf("\n\t\tDeleted successfully");
    else {
        printf("\n\t\tUnable to delete the file");
        fclose(memory);
        printf("\n\t\tPress enter to continue!");
        getch();
        fflush(stdin);
        return;
    }

    faux = fopen("FAux", "w+");
    if (faux == NULL) {
        printf("\n\t\tFile error!");
        printf("\n\n\t\tPress enter to continue!");
        getch();
        fflush(stdin);
        return;
    }

    while (fgets(reader, 17, memory) != NULL) {
        reader[strcspn(reader, "\n")] = 0;
        if (strcmp(reader, name) != 0) {
            fprintf(faux, "%s", reader);
        }
    }
    fclose(memory);
    memory = fopen("Index", "w");
    if (memory == NULL) {
        printf("\n\t\tFile error!");
        printf("\n\n\t\tPress enter to continue!");
        getch();
        fflush(stdin);
        return;
    }
    rewind(faux);
    rewind(memory);
    printf("\n\t\tAvailable Passwords:\n");
    while (fgets(reader, 17, faux) != NULL) {
        fprintf(memory, "%s", reader);
        printf("\n\t\t%s", reader);
    }
    fclose(memory);
    fclose(faux);
    printf("\n\t\tPress enter to continue!");
    getch();
    fflush(stdin);
}

void generate_password() {
    int n;
    srand(time(0));
    printf("\n\t\t**Password_Generator**\t\t");
    printf("\n\t\tEnter the number of characters for the password:");
    scanf("%d", &n);
    printf("\t\t");
    for (int i = 1; i <= n; i++)
        printf("%d", rand() % 9 + 1);
    printf("\n\t\tPassword generated successfully!");
    printf("\n\t\tPress enter to continue!");
    getch();
    fflush(stdin);
}

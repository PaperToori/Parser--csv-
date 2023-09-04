#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <string.h>

#define ClearTerminal printf("\033[H\033[J")

int LIMIT = 353;

struct Person
{
    char source[16];
    char target[16];
    int weight;
};

struct Name
{
    char name[16];
};

void ListPeople(Person rows[]);
void ListEncounters(Person rows[]);

int main()
{

    Person rows[LIMIT];
    int tally = 0;

    // Opens file
    FILE *fip = fopen("thrones.csv", "r");
    if (NULL == fip)
    {
        puts("File not located.");
        return 1;
    }

    // This is where the fun begins ^x^
    char line[128];

    char first[16];
    char second[16];
    char heaft[3];
    int lim = 0;

    while (fgets(line, 128, fip))
    {
        short i = 0;
        short j = 0;

        // First name
        while (true)
        {
            if (line[i] == ',')
            {
                first[j] = '\0';
                break;
            }
            first[j] = line[i];
            i++;
            j++;
        }

        j = 0;
        i++;

        // Second name
        while (true)
        {
            if (line[i] == ',')
            {
                second[j] = '\0';
                break;
            }
            second[j] = line[i];
            i++;
            j++;
        }

        j = 0;
        i++;

        // Weight
        while (true)
        {
            if (line[i] == EOF || line[i] == '\n')
            {
                heaft[j] = '\0';
                break;
            }
            heaft[j] = line[i];
            i++;
            j++;
        }

        // Copes values from read line to values in Person
        strcpy(rows[tally].source, first);
        strcpy(rows[tally].target, second);
        rows[tally].weight = atoi(heaft);

        lim++;
        tally++;
    }

    // Yeetus deleetus the file across the heap
    fclose(fip);

    // Input & Action
    char inp;
    ClearTerminal;
    while (true)
    {
        printf("thrones.csv has been read.\n");
        printf("Choose action:\n");
        printf("L > List every person.\n");
        printf("R > List all related people in order of encounters.\n");
        printf("Q > End program.\n");

        inp = toupper(getc(stdin));
        fflush(stdin);

        switch (inp)
        {
        case 'Q':
            printf("Ending program...\n");
            return 1;
            break;
        case 'L':
            ListPeople(rows);
            break;
        case 'R':
            ListEncounters(rows);
            break;
        default:
            ClearTerminal;
            printf("Input not recognised\n");
            break;
        }
    }

    return 0;
}

void ListPeople(Person rows[])
{
    ClearTerminal;

    Name known_persons[LIMIT];
    short count = 0;
    short exists = 0;

    strcpy(known_persons[count].name, rows[0].source);
    count++;
    strcpy(known_persons[count].name, rows[0].target);
    count++;

    for (int k = 1; k < LIMIT; k++)
    {

        // Checks if source exists in Arr
        exists = 0;
        for (int c = 0; c < count; c++)
        {
            if (strcmp(known_persons[c].name, rows[k].source) == 0)
            {
                exists = 1;
            }
        }
        // If it didn't exists: adds it, then moves along.
        if (0 == exists)
        {
            strcpy(known_persons[count].name, rows[k].source);
            count++;
        }

        // Same thing as above, but for Target
        exists = 0;
        for (int c = 0; c < count; c++)
        {
            if (strcmp(known_persons[c].name, rows[k].target) == 0)
            {
                exists = 1;
            }
        }
        // If it didn't exists: adds it, then moves along.
        if (0 == exists)
        {
            strcpy(known_persons[count].name, rows[k].target);
            count++;
        }
    }

    // Bubble sort for names
    char cache[16];
    while (true)
    {
        short perfect = 0;
        for (int k = 0; k < count - 1; k++)
        {
            if (strcmp(known_persons[k].name, known_persons[k + 1].name) > 0)
            {
                perfect = 1;
                strcpy(cache, known_persons[k].name);
                strcpy(known_persons[k].name, known_persons[k + 1].name);
                strcpy(known_persons[k + 1].name, cache);
            }
        }
        if (perfect == 0)
        {
            break;
        }
    }

    // Prints everybody's names
    printf("----------------\n");
    for (int k = 0; k < count; k++)
    {
        printf("%s\n", known_persons[k].name);
    }
    printf("----------------\n");
    return;
}

void ListEncounters(Person row[])
{
    ClearTerminal;
    char inp[16];

    printf("Enter name: ");
    gets(inp);
    printf("\n");

    short exists = 0;

    for (int k = 0; k < LIMIT; k++)
    {
        if (strcmp(inp, row[k].source) == 0)
        {
            printf("%s\tWeight: %d\n", row[k].target, row[k].weight);
            exists = 1;
        }
        else if (strcmp(inp, row[k].target) == 0)
        {
            printf("%s\tWeight: %d\n", row[k].source, row[k].weight);
            exists = 1;
        }
    }
    printf("\n");
    if (exists == 0)
    {
        printf("Person doesn't exist.\n");
    }
}
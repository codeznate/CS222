/*
    Program that reads from external Inet file and returns found records at locality
    address. Checks for bounds errors between 0-255, and writes results into
    a file for viewing. 
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *getDateAndTime();
int readDataFile();

struct address_t{
    int addr[4];
    char name[11];
};

struct address_t records[100];

int main()
{
    char dateTime[32];
    char name[32];

    //input name
    printf("Please enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    //date and time
    strcpy(dateTime, getDateAndTime());
}

char *getDateAndTime(void)
{
    time_t t;
    time(&t);
    return ctime(&t);
}

int readDataFile(void)
{
    FILE *fptr;
    int i = 0;

    fptr = fopen("CS222_Inet.txt", "r");
    if (fptr == NULL)
    {
        perror("Error opening CS222_Inet.txt");
        return -1;
    }

    while (fscanf(fptr, "%d.%d.%d.%d %10s", &records[i].addr[0], &records[i].addr[1],
        &records[i].addr[2], &records[i].addr[3], records[i].name) == 5)
    {
        if (strcmp(records[i].name, "NONE") == 0)
        {
            break;
        }

        for (int j = 0; records[i].name[j] != '\0'; j++)
        {
            records[i].name[j] = toupper(records[i].name[j]);
        }
    }
    i++;
}
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
/*
    Declaration of functions
    char *getDateAndTime() - gets current date and time
    int readDataFile() - reads data from external file into struct array
    int specifyLocality() - prompts user for locality address values, range checking
*/

char *getDateAndTime(void);
int readDataFile(void);
int specifyLocality(int *a, int *b);
void generateLocalityReport(int num1, int num2, int count);

/*
    Struct definition for records
    addr -> array of 4 integer values for IP address from file
    char -> name associated with the IP address
*/
struct address_t{
    int addr[4];
    char name[11];
};
struct address_t records[100]; /* -> global array of records */
/*
    Main program, handles function calls for later formatting
*/
int main()
{
    char dateTime[32];
    char name[32];
    int local1, local2, recordsFound;

    //input name
    printf("Please enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; //-> remove newline char

    //date and time
    strcpy(dateTime, getDateAndTime());
    //read data file and store records found
    recordsFound = readDataFile();
    //specifiy locality 
    specifyLocality(&local1, &local2);
    //locality report
    generateLocalityReport(local1, local2, recordsFound);
}
/*
    Function for retrieving current date and time using time library
*/
char *getDateAndTime(void)
{
    time_t t;
    time(&t);
    return ctime(&t);
}
/*
    Function for reading data from external txt file 
    -> Retrieves data from file such as IP addresses and names associated until NULL record
    -> Converts names to uppercase for easier comparison
    -> Returns the number of records read 
*/
int readDataFile(void)
{
    FILE *fptr;
    int i=0;

    fptr = fopen("CS222_Inet.txt", "r"); //open file for reading
    if (fptr == NULL) //error handling
    {
        perror("Error opening CS222_Inet.txt");
        return -1;
    }
    while (fscanf(fptr, "%d.%d.%d.%d %10s", &records[i].addr[0], &records[i].addr[1],
        &records[i].addr[2], &records[i].addr[3], records[i].name) == 5) //read file data and storing into struct
    {
        if (strcmp(records[i].name, "NONE") == 0) //if record is NULL
        {
            break;
        }
        for (int j = 0; records[i].name[j] != '\0'; j++) //convert name to uppercase
        {
            records[i].name[j] = toupper(records[i].name[j]);
        }
        i++;
    }
    fclose(fptr);
    return i;
}
/*
    Function for prompting user for locality address values
    -> Ensures values are within range of 0-255
    -> Uses pointers to return values to main program
*/
int specifyLocality(int *a, int *b)
{
    char ip1[8], ip2[8];
    int i1, i2;
    while(1)
    {
        //locality value 1
        //-> store only 7 chars preventing overflow 
        printf("\nEnter locality value #1[0-255] --> ");
        scanf("%7s", ip1);
        i1 = atoi(ip1);

        if (i1 < 0 || i1 > 255) //range checking
        {
            printf("\nError: Please enter value in range (0-255)\n");
            continue;
        }
        while(1) //locality value 2
        {
            printf("Enter locality value #2[0-255] --> ");
            scanf("%7s", ip2);
            i2 = atoi(ip2);

            if (i2 <0 || i2 > 255) //range checking 
            {
                printf("\nError: Please enter value in range (0-255)\n");
                continue;
            }
            *b = i2;
            break;
        }
        *a = i1;
        break;
    }
}
/*
    Function for generating locality report and checking matches 
*/
void generateLocalityReport(int num1, int num2, int count)
{
    struct match_t{
        char ip[16];
        char name[11];
    };
    struct match_t matches[100];

    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (records[i].addr[0] == num1 && records[i].addr[1] == num2)
        {
            sprintf(matches[found].ip, "%d.%d.%d.%d", records[i].addr[0], records[i].addr[1],
                records[i].addr[2], records[i].addr[3]);
            strcpy(matches[found].name, records[i].name);
            found++;
        }
    }
    if (found > 0)
    {
        printf("\nLocality Report\n");
        printf("==================\n");
        printf("Records at %d.%d:\n", num1, num2);
        for (int i = 0; i < found; i++)
        {
            printf("%s  %s\n", matches[i].ip, matches[i].name);
        }
    }
    else
    {
        printf("Error: No records exist at location %d.%d\n", num1, num2);
    }
}


/*
-> Name: Nathaniel Crick
-> Homework: 5 Locality pair
-> G#: G01494888
-> CS222

-> Given a file of IP Addresses and their assigned aliases, request for two inputs for the locality repair, and 
   parse through the given file to find a match for the locality repair and print to console with its assigned alias. 
   As compared to HW4, this will be done by using a linked list. 
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
    Declaration of functions
*/

char *getDateAndTime(void);
int readDataFile(void);
int specifyLocality(int *a, int *b);
void generateLocalityReport(int num1, int num2, char name[32]);


/*
    Struct definition for records
    octet[4] -> array of 4 integer values for IP address from file
    alias[11] -> name associated with the IP address
    *next -> pointer to next struct address
*/
struct address_t{
    int octet[4];
    char alias[11];
    struct address_t *next;
};
struct address_t *head = NULL;

int main()
{
    char name[32];
    int local1, local2, recordsFound;

    //input name
    printf("Please enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    //read data file and store records found
    recordsFound = readDataFile();
    //specifiy locality 
    specifyLocality(&local1, &local2);
    //locality report
    generateLocalityReport(local1, local2, name);
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
    -> Stores within linked list 
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

    while(1)
    {
        struct address_t *newNode = malloc(sizeof(struct address_t));
        if (!newNode)
        {
            perror("Memory Allocation Failed!\n");
            fclose(fptr);
            return -1;
        }

        int count = fscanf(fptr, "%d.%d.%d.%d %12s", &newNode->octet[0], &newNode->octet[1], &newNode->octet[2],
            &newNode->octet[3], newNode->alias);

        if (newNode->octet[0] == 0 && newNode->octet[1] == 0 && newNode->octet[2] == 0 && newNode->octet[3] == 0
        && strcmp(newNode->alias, "NONE") == 0)
        {
            free(newNode);
            break;
        }

        for (i = 0; newNode->alias[i]; i++)
        {
            newNode->alias[i] = toupper(newNode->alias[i]); 
        }

        newNode->next = head;
        head = newNode;
    }
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

void generateLocalityReport(int num1, int num2, char name[32])
{
    struct address_t *curr = head;
    int found = 0;
    FILE *fptr;

    fptr = fopen("222_Locality_List", "w");
    fprintf(fptr,"%s\n", name);
    fprintf(fptr,"%s\n", getDateAndTime());
    fprintf(fptr,"Records at %d.%d:\n", num1, num2);

    while(curr != NULL)
    {
        if (curr->octet[0] == num1 && curr->octet[1] == num2)
        {
            printf("%d.%d.%d.%d %12s\n", curr->octet[0], curr->octet[1], curr->octet[2], curr->octet[3],
                curr->alias);
            found += 1; 
            fprintf(fptr, "%d.%d.%d.%d %s\n", curr->octet[0], curr->octet[1], curr->octet[2], curr->octet[3], curr->alias);
        }
        curr = curr->next;
    }

    if (found == 0)
    {
        printf("No records exist at %d.%d\n", num1, num2);
        specifyLocality(&num1, &num2);
        generateLocalityReport(num1, num2, name);
    }
    fclose(fptr);
    printf("\nData successfully stored within 222_Locality_List!\n");
    printf("Goodbye!\n");
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function prototype for getDateAndTime
char *getDateAndTime();
int getInteger();

int main()
{
    char dateTime[64];
    char name[32];
    char binString[32];
    char octString[32];
    char hexString[32];
    int decVal = 0;
    int saveSuccess = 0;

    strcpy(dateTime, getDateAndTime());
}

char *getDateAndTime()
{
    time_t currentTime;
    time(&currentTime);

    char *dateStr = ctime(&currentTime);
    static char result[64];
    snprintf(result, sizeof(result), "Today's date: %s", dateStr);
    return result;
}

int getInteger();
{
    int value; 

    printf("Enter an Integer [1-1,000,000] or type x to exit: ")
    char *fgets(char *str, int n, FILE *stream);
}
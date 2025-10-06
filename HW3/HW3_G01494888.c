// Nathaniel Crick
//Homework 3
//G01494888

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *getDateAndTime();
int getInteger();
void decimalToBinary(int decValue, char binString[]);
void decimalToHex(int decValue, char hexString[]);
void decimalToOct(int decValue, char octString[]);

int main() 
{
    char dateTime[32];
    char name[32];
    char binString[32];
    char octString[32];
    char hexString[32];
    int decVal = 0;
    int saveSuccess = 0;

    

    strcpy(dateTime, getDateAndTime());

    // prompt user for name
    // TODO: Implement prompt for name

    decVal = getInteger();

    // exit clause
    if (decVal == -1)
        return 0;

    // run conversions
    decimalToBinary(decVal, binString);
    decimalToHex(decVal, hexString);
    decimalToOct(decVal, octString);

    // print conversions to the console
    printf("Decimal: %d\n", decVal);
    printf("Binary: %s\n", binString);
    printf("Octal: %s\n", octString);
    printf("Hexidecimal: %s\n", hexString);

    // save the file
    //saveSuccess = saveFile(name, dateTime, decVal, octString, hexString, binString);
    //if (!saveSuccess) // equivalent to: if (saveSuccess == 0)
        //return 1;

    //return 0;
}

char *getDateAndTime(void) //prove date and time
{
    time_t t;
    time(&t);
    return ctime(&t);
}

int getInteger() //input integer 
{ 
    char buffer[100]; 
    int value;

    while (1) 
    {
        int value;
        printf("Enter an integer between [1-1,000,000] or enter x to quit: ");
        fgets(buffer, sizeof(buffer), stdin); //get integer from input converting to array

        buffer[strcspn(buffer, "\n")] = '\0'; //terminate string at end

        if (buffer[0] == 'x' || buffer[0] == 'X') //check for exit input
        {
            return -1;
        }
        
        value = atoi(buffer); //convert to int

        if (value >= 1 && value <= 1000000) //bound checking
        {
            return value;
        }
        else
        {
            printf("Please enter an integer in bounds, or type x to quit.\n");
        }
        
    }
}

void decimalToBinary(int decValue, char binString[])
{
    int i = 0;
    char binTemp[32];

    while (decValue > 0) //loop to convert decimal to binary
    {
        binTemp[i++] = (decValue % 2) + '0'; //store ascii
        decValue = decValue / 2; //move to next int
    }
    binTemp[i]='\0';  //terminate string

    for (int j = 0; j < i; j++)  //converting data into binString
    {
        binString[j] = binTemp[i-j-1];
    }
    binString[i] = '\0'; //terminate string
}

void decimalToHex(int decValue, char hexString[]) //conversion to hex
{
    long int quotient;
    int i=0, hexTemp;
    char tempHexString[32];
    quotient = decValue;

    while (quotient != 0)
    {
        hexTemp = quotient % 16; 

        if (hexTemp < 10) //convert int to character
        {
            hexTemp = hexTemp + 48;
        }
        else
        {
            hexTemp = hexTemp + 55;
        }

        tempHexString[i++] = hexTemp;
        quotient = quotient/16;

        tempHexString[i] = '\0';
    }

    for (int j = i-1, k = 0; j >= 0; j--, k++) //reversal
    {
        hexString[k] = tempHexString[j];
    }
    hexString[i] = '\0';
}

void decimalToOct(int decValue, char octString[]) //conversion to octal
{
    long int quotient;
    int i = 0, octTemp;
    char tempOctString[32];

    quotient = decValue;

    while (quotient != 0)
    {
        octTemp = quotient % 8;
        tempOctString[i++] = octTemp +'0';
        quotient = quotient /8;
    }
    tempOctString[i] = '\0';

    for(int j = i-1, k = 0; j >= 0; j--, k++) //reversal
    { 
        octString[k] = tempOctString[j];
    }

}

int saveFile(char name[], char date[], int decValue, char octString[], char hexString[], char binString[])
{
    
}


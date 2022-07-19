/*
Assignment#1 Milestone#4
Richard Lowe
140804204
rlowe1@myseneca.ca
IPC144NHH
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "commonHelpers.h"
#include "account.h"
#include <time.h>
#include <string.h>
#include "accountTicketingUI.h"

// Uses the time.h library to obtain current year information
// Get the current 4-digit year from the system
int currentYear(void)
{
    time_t currentTime = time(NULL);
    return localtime(&currentTime)->tm_year + 1900;
}

// As demonstrated in the course notes: 
//https://ict.senecacollege.ca//~ipc144/pages/content/formi.html#buf
// Empty the standard input buffer
void clearStandardInputBuffer(void)
{
    while (getchar() != '\n')
    {
        ; // On purpose: do nothing
    }
}

//function for getInteger
int getInteger(void)
{
    int value;
    char newLine = 'x';


    scanf(" %d%c", &value, &newLine);
    
    while (newLine != '\n')
    {
        clearStandardInputBuffer();
        printf("ERROR: Value must be an integer: ");
        scanf(" %d%c", &value, &newLine);
    }
    return value;
}

int getPositiveInteger(void)
{

    int value;
    //clearStandardInputBuffer();
    scanf(" %d", &value);

    while (value <= 0)
    {

        printf("ERROR: Value must be a positive integer greater than zero: ");

        scanf("%d", &value);
        clearStandardInputBuffer();
    }
    return value;
}

int getIntFromRange(int lowNumber, int highNumber)
{
    int value;

    //clearStandardInputBuffer();
    value = getInteger();
    while (value < lowNumber || value > highNumber)
    {
        printf("ERROR: Value must be between %d and %d inclusive: ", lowNumber, highNumber);
        value = getInteger();
    }
    return value;
}

double getDouble(void)
{
    double value;
    char newLine = 'x';


    while (newLine != '\n')
    {
        scanf("%lf%c", &value, &newLine);
        if (newLine != '\n')
        {
            printf("ERROR: Value must be a double floating-point number: ");
            clearStandardInputBuffer();
        }
    }

    return value;
}

double getPositiveDouble(void)
{
    double value = 0;

    value = getDouble();
    if (value <= 0)
    {
        printf("ERROR: Value must be a positive double floating-point number: ");
        value = getDouble();
    }

    return value;
}


char getCharOption(const char string[])
{

    char letter[31] = { '\0' };
    int i, x = 0;

    while (x == 0)
    {
        scanf("%10[^\n]", letter);
        if (letter[1] == '\0')
        {
            for (i = 0; i < 5; i++)

                if (string[i] == letter[0])
                {
                    x++;
                }
        }
        if ((x == 0) || (letter[1] != '\0'))
        {
            printf("ERROR: Character must be one of [%s]: ", string);
            clearStandardInputBuffer();
            letter[0] = '\0';
        }
    }
    return *letter;
}

char getCString(char* cstringValue, int y, int x)
{

    int maxLength = x;
    int minLength = y;
    char stringName[31] = { 0 };
    int length = 0, i;

    while ((length + 1) > maxLength || (length + 1) < minLength)
    {
        scanf("%[^\n]", stringName);
        clearStandardInputBuffer();

        for (i = 0; stringName[i] != '\0'; i++)
        {
            length = i;
        }
        if ((minLength == maxLength) && ((length + 1) > maxLength || (length + 1) < minLength))
        {
            printf("ERROR: String length must be exactly %d chars: ", maxLength);

        }
        if ((length + 1) > maxLength && (minLength != maxLength))
        {
            printf("ERROR: String length must be no more than %d chars: ", maxLength);

        }
        if ((minLength < maxLength) && ((length + 1) < minLength))
        {
            printf("ERROR: String length must be between %d and %d chars: ", minLength, maxLength);

        }
    }
    for (i = 0; stringName[i] != '\0'; i++)
        cstringValue[i] = stringName[i];
    cstringValue[i] = '\0';

    return *cstringValue;
}

void pauseExecution(void)
{
    printf("<< ENTER key to Continue... >>");
    clearStandardInputBuffer();
    putchar('\n');
    return;
}
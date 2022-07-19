/*
Assignment#1 Milestone#4
Richard Lowe
140804204
rlowe1@myseneca.ca
IPC144NHH
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "account.h"                       
#include "commonHelpers.h"  
#include "accountTicketingUI.h"

char user[11];
char name[31];
char pass[9];
char country[31] = { 0 };
int i = 0; int x = 0; int y = 0;

void getAccountData(ACCOUNT* account)
{
    printf("\n");
    printf("Account Data: New Record\n");
    printf("----------------------------------------\n");
    printf("Enter the account number: ");
    account->acctNumber = getInteger();
    printf("\nEnter the account type (A=Agent | C=Customer): ");
    account->acctType = getCharOption("AC");
    clearStandardInputBuffer();
    printf("\n");

    return;
}


void getUserLogin(ACCOUNT* account)
{
    printf("User Login Data Input\n");
    printf("----------------------------------------\n");
    printf("Enter user login (10 chars max): ");
    getCString(user, 2, 10);
    for (i = 0; user[i] != '\0'; i++)
        account->UserLogin.userName[i] = user[i];

    printf("Enter the display name (30 chars max): ");
    getCString(name, 2, 30);
    for (x = 0; name[x] != '\0'; x++)
        account->UserLogin.fullName[x] = name[x];

    printf("Enter the password (must be 8 chars in length): ");
    getCString(pass, 8, 8);
    for (y = 0; y < 8; y++)
        account->UserLogin.password[y] = pass[y];


    printf("\n");
    return;
}



void getDemographic(ACCOUNT* account)
{
    int yearStart, yearEnd;
    yearStart = currentYear() - 110;
    yearEnd = currentYear() - 18;

    printf("Demographic Data Input\n");
    printf("----------------------------------------\n");
    printf("Enter birth year (current age must be between 18 and 110): ");

    account->Demographic.birthYear = getIntFromRange(yearStart, yearEnd);

    printf("Enter the household Income: $");
    account->Demographic.houseHoldIncome = getPositiveDouble();

    printf("Enter the country (30 chars max.): ");

    getCString(country, 2, 30);
    for (y = 0; country[y] != '\0'; y++)
        account->Demographic.countryResidence[y] = country[y];

    printf("\n");
    return;
}

int findAccountIndexByAcctNum(int acct_num, const ACCOUNT account[], int size, int prompt)
{
    int i, index = -3;
    if (prompt == 0) {
        putchar('\n');
        printf("Enter your account#: ");
        acct_num = getPositiveInteger();
        printf("\n");
    }
    for (i = 0; i < size; i++)
    {
        if (account[i].acctNumber == acct_num)
        {
            index = i;
            break;
        }
    }//printf("\n");
    return index;
}

void updateAccount(ACCOUNT* account)
{
    int selection = -1;
  while (selection != 0)
   {
    //printf("\n");
    printf("Account: %d - Update Options\n", account->acctNumber);
    printf("----------------------------------------\n");
    printf("1) Update account type (current value: %c)\n", account->acctType);
    printf("2) Login\n");
    printf("3) Demographics\n");
    printf("0) Done\n");
    printf("Selection: ");
    selection = getIntFromRange(0, 3);
    switch (selection) 
        {
        case 1:
            printf("\n");
            printf("Enter the account type (A=Agent | C=Customer): ");
            account->acctType = getCharOption("AC");
            printf("\n");
            break;
        case 2: 
            updateUserLogin(account);
            break;
        case 3:
            updateDemographic(account);
            break;
        case 0:
            break;
        }
   } 
  printf("\n");
    return;
}

void updateUserLogin(ACCOUNT* account)
{
    int selection = -1;
    while(selection != 0)
    {
        printf("\n");
        printf("User Login: %s - Update Options\n", 
            account->UserLogin.userName);
        printf("----------------------------------------\n");
        printf("1) Display name (current value: %s)\n", 
            account->UserLogin.fullName);
        printf("2) Password\n");
        printf("0) Done\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 2);

            switch (selection)
            {
            case 1:
                printf("\n");
                printf("Enter the display name (30 chars max): ");
                getCString(account->UserLogin.fullName, 2, 30);
                break;
            case 2:
                printf("\n");
                printf("Enter the password (must be 8 chars in length): ");
                getCString(account->UserLogin.password, 8, 8);
                break;
            case 0:
                printf("\n");
                break;
            }
    } 
    return;
}

void updateDemographic(ACCOUNT* account)
{
    int selection = -1;
    while (selection != 0)
    {
        printf("\n");
        printf("Demographic Update Options\n");
        printf("----------------------------------------\n");
        printf("1) Household Income (current value: $%0.2lf)\n", 
            account->Demographic.houseHoldIncome);
        printf("2) Country (current value: %s)\n", 
            account->Demographic.countryResidence);
        printf("0) Done\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 2);
      
            switch (selection)
            {
            case 1:
                printf("\n");
                printf("Enter the household Income: $");
                account->Demographic.houseHoldIncome = getPositiveDouble();
                break;
            case 2:
                printf("\n");
                printf("Enter the country (30 chars max.): ");
                getCString(country, 2, 30);
                for (y = 0; country[y] != '\0'; y++)
                    account->Demographic.countryResidence[y] = country[y];
                break;
            case 0:
                printf("\n");
                break;
            }      
    } 
    return;
}
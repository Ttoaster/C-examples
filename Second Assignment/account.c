/*
Assignment#2 Milestone#4
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
#include "ticket.h"
#include <stdlib.h>

#define ACCOUNT_SIZE 15
#define TICKET_SIZE 17

char user[11] = { '\0' };
char name[31] = { '\0' };
char pass[9];
char country[31] = { 0 };

int i = 0; int x = 0; int y = 0;

void getAccountData(ACCOUNT* account)
{
    printf("Enter the account type (A=Agent | C=Customer): ");
    account->acctType = getCharOption("AC");
    clearStandardInputBuffer();
    printf("\n");

    return;
}

void getUserLogin(ACCOUNT* account)
{
    printf("User Login Data Input\n");
    printf("----------------------------------------\n");
    int y;
    do
    {
        y = 0;
        printf("Enter user login (10 chars max): ");
        getCString(user, 2, 10);
        for (i = 0; user[i] != '\0'; i++)
            if (isspace(user[i]) != 0)
                y = y + 1;
        if (y > 0)
        {
            printf("ERROR:  The user login must NOT contain whitespace characters.\n");
        }
    } while (y != 0);
    for (i = 0; user[i] != '\0'; i++)
        account->UserLogin.userName[i] = user[i];
    printf("Enter the display name (30 chars max): ");

    getCString(name, 2, 30);
    for (x = 0; name[x] != '\0'; x++)
        account->UserLogin.fullName[x] = name[x];
    account->UserLogin.fullName[x] = '\0';
    int x;
    do
    {
        x = 0;
        printf("Enter the password (must be 8 chars in length): ");
        getCString(pass, 8, 8);
        for (i = 0; pass[i] != '\0'; i++)
            if ((pass[i] == ')') || (pass[i] == '('))
                x = x + 10;
        for (i = 0; pass[i] != '\0'; i++)
            if (islower(pass[i]))
                x = x + 1;
        for (i = 0; pass[i] != '\0'; i++)
            if (isupper(pass[i]))
                x = x + 2;
        for (i = 0; pass[i] != '\0'; i++)
            if (isdigit(pass[i]))
                x = x + 4;
        for (i = 0; pass[i] != '\0'; i++)
            if (isalpha(pass[i]))
                x = x + 6;
        if (x != 38)
        {
            printf("SECURITY: Password must contain 2 of each:\n");
            printf("          Digit: 0-9\n");
            printf("          UPPERCASE character\n");
            printf("          lowercase character\n");
            printf("          symbol character: !@#$%%^&*\n");
        }
    } while (x != 38);
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
        country[y] = toupper(country[y]);
    for (y = 0; country[y] != '\0'; y++)
        account->Demographic.countryResidence[y] = toupper(country[y]);
    account->Demographic.countryResidence[y] = '\0';
    printf("\n");
    return;
}

int findAccountIndexByAcctNum(int acct_num, const ACCOUNT account[], int size, int prompt)
{
    int i = 0, index = -2, attempts = 3;
    int badAttempt = 0;
    if (prompt == 1)

        do
        {    // system login
            int acct_num;
            char aline[100];
            badAttempt = 0;
          
            printf("\nEnter the account#: ");
            acct_num = getInteger();
        
            for (i = 0; i < size; i++)
                if (account[i].acctNumber == acct_num)
                {
                    index = i;
                    break;
                }
            if (index < 0)
                badAttempt = 1; // 1 = means failure to authenticate 
            aline[0] = '\0';
            printf("User Login    : ");
            scanf("%s[^\n]", aline);
            clearStandardInputBuffer();
            if (index >= 0)
                if (strcmp(aline, account[index].UserLogin.userName))
                    badAttempt = 1;
            aline[0] = '\0';
            printf("Password      : ");
            scanf("%s[^\n]", aline);

            if (index >= 0)
                if (strcmp(aline, account[index].UserLogin.password))
                    badAttempt = 1;
            attempts--;

            if (badAttempt == 1)
                printf("INVALID user login/password combination! [attempts remaining:%d]\n", attempts);
            clearStandardInputBuffer();
        } while ((attempts > 0) && (badAttempt == 1));

        if (attempts == 0)
        {
            printf("\n");
            printf("ERROR:  Login failed!\n");
            printf("\n");
            pauseExecution();
            attempts = 0;
            index = -2;
        }
        if (attempts > 0 && badAttempt == 0 && prompt != 2)
        {
            printf("\n");

        }


        if (prompt == 0) {
            putchar('\n');
            printf("Enter your account#: ");
            acct_num = getPositiveInteger();
            printf("\n");
            for (i = 0; i < size; i++)
                if (account[i].acctNumber == acct_num)
                {
                    index = i;
                    break;
                }
        }
        if (prompt == 2)
            for (i = 0; i < size; i++)//this loop is used for account removal prompt == 2 && modify account
                if (account[i].acctNumber == acct_num)
                {
                    index = i;
                    break;
                } 
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
          //  printf("\n");
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
    while (selection != 0)
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
            do
            {

                x = 0;
                printf("Enter the password (must be 8 chars in length): ");
                getCString(pass, 8, 8);

                for (i = 0; pass[i] != '\0'; i++)
                    if (islower(pass[i]))
                        x = x + 1;
                for (i = 0; pass[i] != '\0'; i++)
                    if (isupper(pass[i]))
                        x = x + 2;
                for (i = 0; pass[i] != '\0'; i++)
                    if (isdigit(pass[i]))
                        x = x + 4;
                for (i = 0; pass[i] != '\0'; i++)
                    if (isalpha(pass[i]))
                        x = x + 6;
                if (x != 38)
                {
                    printf("SECURITY: Password must contain 2 of each:\n");
                    printf("          Digit: 0-9\n");
                    printf("          UPPERCASE character\n");
                    printf("          lowercase character\n");
                    printf("          symbol character: !@#$%%^&*\n");
                }
            } while (x != 38);
            for (y = 0; y < 8; y++)
                account->UserLogin.password[y] = pass[y];
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
                account->Demographic.countryResidence[y] = toupper(country[y]);
            account->Demographic.countryResidence[y] = '\0';
            break;
        case 0:
            printf("\n");
            break;
        }
    }
    return;
}

int isAgent(ACCOUNT* account) {
    if (account->acctType == 'A')
        return 1;
    return 0;
}

int loadAccounts(struct Account* accounts, int size)
{
    int i = 0;
    FILE* fp;
    fp = fopen("accounts.txt", "r");
    if (fp == NULL)
    {
        printf("ERROR: Can't open accounts.txt file.\n");
         exit(1);
    }
    while (fscanf(fp, "%d%*c%c%*c%[^~]%*c%[^~]%*c%[^~]%*c%d%*c%lf%*c%[^\n]",
            &accounts[i].acctNumber,
            &accounts[i].acctType,
            accounts[i].UserLogin.fullName,
            accounts[i].UserLogin.userName,
            accounts[i].UserLogin.password,
            &accounts[i].Demographic.birthYear,
            &accounts[i].Demographic.houseHoldIncome,
            accounts[i].Demographic.countryResidence) != EOF)

    {
   
        i++;
        if (i >= size) break;
    }
    fclose(fp);
    return i;
}

int saveAccounts(struct Account* accounts, int size)
{
    int i = 0;
    int savedAccountsCount = 0;
    FILE* fp;
    fp = fopen("accounts.txt", "w");
    if (fp == NULL)
    {
        printf("ERROR: Can't open accounts.txt file.\n");
        exit(2);
    }
    for (i = 0; i < size; i++)
    {
        if (accounts[i].acctNumber != 0)
        {
            writeAccount(accounts[i], fp);
            savedAccountsCount++;
        }
    }
    fclose(fp);
    return savedAccountsCount;
}

int archiveAccounts(struct Account accounts)
{
    FILE* fp = NULL;
    fp = fopen("accounts_arc.txt", "a");
    if (fp == NULL)
    {
        printf("ERROR: Can't open accounts_arc.txt file.\n");
        exit(1);
    }
    writeAccount(accounts, fp);
    fclose(fp);
    return 1;
}

int writeAccount(struct Account accounts, FILE* fp)
{
    if (accounts.acctNumber != 0)
    {
        fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n",
            accounts.acctNumber,
            accounts.acctType,
            accounts.UserLogin.fullName,
            accounts.UserLogin.userName,
            accounts.UserLogin.password,
            accounts.Demographic.birthYear,
            accounts.Demographic.houseHoldIncome,
            accounts.Demographic.countryResidence);      
    }
    return 1;
}

void archivedAccountsStatistics()
{
    int totalArchivedAccounts = 0;
    int accountNumber = 0;
    int Birth = 0;
    double Income;
    char accountType;
    char Name[31] = { '\0' };
    char User[11] = { '\0' };
    char Password[9] = { '\0' };
    char Country[31] = { '\0' };

    FILE* fp;
    fp = fopen("accounts_arc.txt", "r");
    if (fp == NULL)
    {
        printf("ERROR: Can't open accounts_arc.txt archive file.\n");
        exit(1);
    }
    while (fscanf(fp, "%d%*c%c%*c%[^~]%*c%[^~]%*c%[^~]%*c%d%*c%lf%*c%[^\n]",
           &accountNumber,
           &accountType,
           Name,
           User,
           Password,
           &Birth,
           &Income,
           Country) != EOF)
    {
        totalArchivedAccounts++;
    }
    fclose(fp);
    if (totalArchivedAccounts >= 0)
        printf("There are %d account(s) currently archived.\n",
            totalArchivedAccounts);
    return;
}
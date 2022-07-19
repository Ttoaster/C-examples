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
#include "accountTicketingUI.h"
#include <time.h>
#include <string.h>
#include <ctype.h>

int u = 0; int k = 0;
char hidden[9] = "********";
char temp[9] = { 0 };
char Agent[] = { "AGENT" };
char Customer[] = { "CUSTOMER" };
char type[] = { 0 };

void displayAccountSummaryHeader(const ACCOUNT* account)
{
    printf("Acct# Acct.Type Birth\n");
    printf("----- --------- -----\n");
}

void displayAccountSummaryRecord(const ACCOUNT* account)
{
    int i = 0;

    if (account->acctType == 'A')
    {
        for (i = 0; Agent[i] != '\0'; i++)
            type[i] = Agent[i];
    }
    if (account->acctType == 'C')
    {
        for (i = 0; Customer[i] != '\0'; i++)
            type[i] = Customer[i];
    }

    printf("%05d %-9s %5d", 
        account->acctNumber,
        type, 
        account->Demographic.birthYear);

    printf("\n");
}

void displayAllAccountSummaryHeader(void)
{
    printf("\nAcct# Acct.Type Birth\n");
    printf("----- --------- -----\n");
}

void displayAllAccountSummaryRecords(const ACCOUNT* account)
{
    int i = 0;
   
   
       if (account->acctType == 'A')
        {
            for (i = 0; Agent[i] != '\0'; i++)
                type[i] = Agent[i];
           
       } type[i] = '\0';
        if (account->acctType == 'C')
        {
            for (i = 0; Customer[i] != '\0'; i++)
                type[i] = Customer[i];
        }type[i] = '\0';
   

        printf("%05d %-9s %5d",
            account->acctNumber,
            type,
            account->Demographic.birthYear);
    
    printf("\n");
}

void displayAllAccountDetailHeader(void)
{
    printf("\nAcct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
    printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAllAccountDetailRecords(const ACCOUNT* account)
{
    int i = 0;

    for (u = 0; u < 8; u++)
    {
        temp[u] = account->UserLogin.password[u];
    }
    for (k = 1; k < 8; (k += 2))
    {
        temp[k] = hidden[k];
    }

    if (account->acctType == 'A')
    {
        for (i = 0; Agent[i] != '\0'; i++)
            type[i] = Agent[i];
    }type[i] = '\0';
    if (account->acctType == 'C')
    {
        for (i = 0; Customer[i] != '\0'; i++)
            type[i] = Customer[i];
    }type[i] = '\0';

    printf("%05d %-9s %5d $%10.2lf %-10.10s %-15s %-10s %8s",
        account->acctNumber,
        type,
        account->Demographic.birthYear,
        account->Demographic.houseHoldIncome,
        account->Demographic.countryResidence,
        account->UserLogin.fullName,
        account->UserLogin.userName,
        temp);
    printf("\n");
}

void displayAccountDetailHeader(const ACCOUNT* account)
{
    printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
    printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccountDetailRecord(const ACCOUNT* account)
{
    int i = 0;

    for (u = 0; u < 8; u++)
    {
        temp[u] = account->UserLogin.password[u];
    }
        for (k = 1; k < 8; (k += 2))
        {
        temp[k] = hidden[k];
        }

    if (account->acctType == 'A')
    {
        for (i = 0; Agent[i] != '\0'; i++)
            type[i] = Agent[i];
    }
    if (account->acctType == 'C')
    {
        for (i = 0; Customer[i] != '\0'; i++)
            type[i] = Customer[i];
    }

    printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s", 
        account->acctNumber,
        type, 
        account->Demographic.birthYear,
        account->Demographic.houseHoldIncome,
        account->Demographic.countryResidence,
        account->UserLogin.fullName,
        account->UserLogin.userName,
        temp);

    printf("\n");
}

void applicationStartup(ACCOUNT account[], int size) // Entry point
{
    
    int index;
    do
    {
        index = menuLogin(account, size);
        
        if (isAgent(&account[index]))
            menuAgent(account, size, &account[index]);
       
        if(account[index].acctType == 'C' )
        {
            printf("CUSTOMER: home menu currently unavailable...\n");
            clearStandardInputBuffer();
            putchar('\n');
            pauseExecution();
        }
    } while (index != -1);

    printf("==============================================\n");
    printf("Account Ticketing System - Terminated\n");
    printf("==============================================\n");
   return;
}

int isAgent(ACCOUNT* account) {
    if (account->acctType == 'A')
        return 1;
    return 0;
}

int menuLogin(const ACCOUNT account[], int size)
{
    
    int choice = -1;
    int acct_num = 0;
    int index = -1;
    char option;
    
    do {
        choice = -1;
        //printf("\n");
        printf("==============================================\n");
        printf("Account Ticketing System - Login\n");
        printf("==============================================\n");
        printf("1) Login to the system\n");
        printf("0) Exit application\n");
        printf("----------------------------------------------\n");
        printf("\nSelection: ");
        
        choice = getIntFromRange(0, 1);
        if (choice == 0)
        {
            printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
            option = getCharOption("yYnN");
            if (option == 'y' || option == 'Y')
                index = -1;
            else
                index = -3;
            putchar('\n');
        }
        if (choice == 1)
        {
            index = findAccountIndexByAcctNum(acct_num, account, size, 0);
        }
        if (index == -3 && choice == 1)
        {
                clearStandardInputBuffer();
            printf("ERROR:  Access Denied.\n");
            printf("\n");
                pauseExecution();
        }
    } while (index < -1);

    return index;
}

void menuAgent( ACCOUNT account[], int size, const ACCOUNT paccount[])
{
    int selection; int j; int index;
    int acct_num;
    char option;
    do {
        printf("AGENT: %s (%d)\n", paccount->UserLogin.fullName, paccount->acctNumber);
        printf("==============================================\n");
        printf("Account Ticketing System - Agent Menu\n");
        printf("==============================================\n");
        printf("1) Add a new account\n");
        printf("2) Modify an existing account\n");
        printf("3) Remove an account\n");
        printf("4) List accounts: summary view\n");
        printf("5) List accounts: detailed view\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n");
        printf("\nSelection: ");
        selection = getIntFromRange(0, 5);
        switch (selection)
        {
        case 1: //add new account
            for (j = 0; j < size; j++) 
                if (account[j].acctNumber == 0)
                    break;
                if (j < size) 
                {
                    getAccountData(&account[j]);
                    getUserLogin(&account[j]);
                    getDemographic(&account[j]);
                    printf("*** New account added! ***\n");
                    printf("\n");
                }
                else 
                {
                    printf("ERROR: Account listing is FULL, call ITS Supprot!\n");
                }
                pauseExecution();
                break;
        case 2: // modify account
            printf("\n");
            printf("Enter the account#: ");
            acct_num = getPositiveInteger();
            printf("\n");
            index = findAccountIndexByAcctNum(acct_num, account, size, 1);
            if (index == -1)
            {
                printf("ERROR: Access Denied.\n");
                pauseExecution();
            }
            else {
                updateAccount(&account[index]);
            }
            break;
        case 3: // remove account
            printf("\n");
            printf("Enter the account#: ");
            acct_num = getPositiveInteger();
            //printf("\n");
            index = findAccountIndexByAcctNum(acct_num, account, size, 1);
            if (index == -1)
            {
                printf("ERROR: Access Denied.\n");
            }
            else if (account[index].acctNumber == paccount->acctNumber) {
                printf("\n");
                printf("ERROR: You can't remove your own account!\n");
                printf("\n");
                clearStandardInputBuffer();
                pauseExecution();
            }
            else {
                displayAccountDetailHeader(&account[index]);
                displayAccountDetailRecord(&account[index]);
                printf("\n");
                printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
                clearStandardInputBuffer();
                option = getCharOption("YN");
               
                if ((option) == 'Y')
                {
                    account[index].acctNumber = 0;
                    printf("\n*** Account Removed! ***\n");
                    printf("\n");
                    clearStandardInputBuffer();
                    pauseExecution();
                }
                else {
                    printf("\n");
                    printf("*** No changes made! ***\n");
                    printf("\n");
                    clearStandardInputBuffer();
                    pauseExecution();
                }  
            }
            break;
        case 4:// display summary
           displayAllAccountSummaryHeader();
           {
               int x;
               for (x = 0; x < size; x++)
               if (account[x].acctNumber != 0)
               {
                   displayAllAccountSummaryRecords(&account[x]);
               }
              printf("\n");
               pauseExecution();
               break;
           }
        case 5: // display detailed accounts
            displayAllAccountDetailHeader();
            {
                int x;
                for (x = 0; x < size; x++)
                if (account[x].acctNumber != 0)
                {
                    displayAllAccountDetailRecords(&account[x]);                 
                }
                printf("\n");
                pauseExecution();
                break;
            }
        case 0:
            printf("\n");
            printf("### LOGGED OUT ###\n");
            printf("\n");
            break;
        }
    } while (selection > 0);
 return;
}
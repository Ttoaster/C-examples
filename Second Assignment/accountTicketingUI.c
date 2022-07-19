/*
Assignment#2 Milestone#4
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
#include "ticket.h"
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ACCOUNT_SIZE 15
#define TICKET_SIZE 17

char hidden[9] = "********";
char temp[9] = { 0 };
char Agent[] = "AGENT";
char Customer[] = "CUSTOMER";
char type[] = { 0 };
struct Ticket tickets[TICKET_SIZE] = { {0} };
struct Account accounts[ACCOUNT_SIZE] = { {0} };

void displayAccountSummaryHeader(void)
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
             type[i] = '\0';
    }
    if (account->acctType == 'C')
    {
        for (i = 0; Customer[i] != '\0'; i++)
            type[i] = Customer[i];
             type[i] = '\0';
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
             type[i] = '\0';
    } 
    if (account->acctType == 'C')
    {
        for (i = 0; Customer[i] != '\0'; i++)
            type[i] = Customer[i];
             type[i] = '\0';
    }
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

void displayAllAccountDetailRecords(struct AccountTicketingData data)
{
    int i = 0;
    int k = 0;
    int j = 0;
    int x = 0;

    for (x = 0; x < ACCOUNT_SIZE; x++)
      if (data.accounts[x].acctNumber != 0)
      {
            for (k = 0; k < 8; k++)
            {
                temp[k] = data.accounts[x].UserLogin.password[k];
            }
            for (j = 1; j < 8; (j += 2))
            {
                temp[j] = hidden[j];
            }

            if (data.accounts[x].acctType == 'A')
            {
                for (i = 0; Agent[i] != '\0'; i++)
                    type[i] = Agent[i];

            }  type[i] = '\0';
            if (data.accounts[x].acctType == 'C')
            {
                for (i = 0; Customer[i] != '\0'; i++)
                    type[i] = Customer[i];

            }  type[i] = '\0';
            printf("%05d %-9s %5d $%10.2lf %-10s %-15.15s %-10.10s %8s\n",
                data.accounts[x].acctNumber,
                type,
                data.accounts[x].Demographic.birthYear,
                data.accounts[x].Demographic.houseHoldIncome,
                data.accounts[x].Demographic.countryResidence,
                data.accounts[x].UserLogin.fullName,
                data.accounts[x].UserLogin.userName,
                temp);
      }
}

void displayAccountDetailHeader(void)
{
    printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
    printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccountDetailRecord(const ACCOUNT* account)
{
    int i = 0;
    int k = 0;
    int j = 0;

    for (k = 0; k < 8; k++)
    {
        temp[k] = account->UserLogin.password[k];
    }
    for (j = 1; j < 8; (j += 2))
    {
        temp[j] = hidden[j];
    }
    if (account->acctType == 'A')
    {
        for (i = 0; Agent[i] != '\0'; i++)
            type[i] = Agent[i];
             type[i] = '\0';
    }
    if (account->acctType == 'C')
    {
        for (i = 0; Customer[i] != '\0'; i++)
            type[i] = Customer[i];
             type[i] = '\0';
    }
    printf("%05d %-9s %5d $%10.2lf %-10s %-15.15s %-10.10s %8s",
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
//======================================================================//
                               // START
//======================================================================//
void applicationStartup(struct AccountTicketingData* data) // Entry point
{
    int index;
    loadTickets(tickets, TICKET_SIZE);
    loadAccounts(accounts, TICKET_SIZE);
    do
    {
        index = menuLogin(accounts, TICKET_SIZE);

        if (isAgent(&data->accounts[index]))
            menuAgent(*data, &data->accounts[index]);

        if (data->accounts[index].acctType == 'C')
        {
            menuClient(*data, &data->accounts[index], TICKET_SIZE);

        }
    } while (index != -1);
    printf("==============================================\n");
    printf("Account Ticketing System - Terminated\n");
    printf("==============================================\n");
    return;
}

int menuLogin(const ACCOUNT account[], int size)
{
    int choice = -1;
    int acct_num = 0;
    int index = -1;
    char option;

    do {
        choice = -1;
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
            index = findAccountIndexByAcctNum(acct_num, account, ACCOUNT_SIZE, 1);
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

void menuAgent(struct AccountTicketingData data, const ACCOUNT paccount[])
{
    int size = ACCOUNT_SIZE;
    int c;
    int selection; int j; int index;
    int acct_num;
    char option;
    int highestAcct = 0;
    int location = 0;

    do {
        printf("AGENT: %s (%d)\n", paccount->UserLogin.fullName, paccount->acctNumber);
        printf("==============================================\n");
        printf("Account Ticketing System - Agent Menu\n");
        printf("==============================================\n");
        printf(" 1) Add a new account\n");
        printf(" 2) Modify an existing account\n");
        printf(" 3) Remove an account\n"); 
        printf(" 4) List accounts: summary view\n");
        printf(" 5) List accounts: detailed view\n");
        printf("----------------------------------------------\n");
        printf(" 6) List new tickets\n");
        printf(" 7) List active tickets\n");
        printf(" 8) List closed tickets\n");
        printf(" 9) Manage a ticket\n");
        printf("10) Archive closed tickets\n");
        printf("----------------------------------------------\n");
        printf("11) View archived account statistics\n");
        printf("12) View archived tickets statistics\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n");
        printf("\nSelection: ");
        selection = getIntFromRange(0, 12);
        switch (selection)
        {
        case 1: //add new account

            for (j = 0; j < size; j++)
                if (data.accounts[j].acctNumber == 0)
                    break;
            if (j < size)
            {
                for (c = 1; c < size; c++)
                    if (data.accounts[c].acctNumber > data.accounts[location].acctNumber)
                    {
                        location = c;
                    }
                highestAcct = data.accounts[location].acctNumber;

                data.accounts[j].acctNumber = highestAcct + 1;
                printf("\n");
                printf("New Account Data (Account#:%d)\n", data.accounts[j].acctNumber);
                printf("----------------------------------------\n");
                getAccountData(&data.accounts[j]);
                getUserLogin(&data.accounts[j]);
                getDemographic(&data.accounts[j]);
                printf("*** New account added! ***\n");
            }
            else
            {
                printf("\n");
                printf("ERROR: Account listing is FULL, call ITS Support!\n");
            }
            printf("\n");
            pauseExecution();
            break;
        case 2: // modify account
            printf("\n");
            printf("Enter the account#: ");
            acct_num = getPositiveInteger();
            index = findAccountIndexByAcctNum(acct_num, data.accounts, size, 2);
            if (index == -1)
            {
                printf("ERROR: Access Denied.\n");
                pauseExecution();
            }
            else 
            {
                printf("\n");
                updateAccount(&data.accounts[index]);
            }
            break;
        case 3: // remove account
            printf("\n");
            printf("Enter the account#: ");
            acct_num = getPositiveInteger();
           
            index = findAccountIndexByAcctNum(acct_num, data.accounts, size, 2);
            if (index == -1)
            {
                printf("ERROR: Access Denied.\n");
            }
            else if (data.accounts[index].acctNumber == paccount->acctNumber) 
            {
                printf("ERROR: You can't remove your own account!\n");
                printf("\n");
                clearStandardInputBuffer();
                pauseExecution();
            }
            else 
            {
                displayAccountDetailHeader();
                displayAccountDetailRecord(&data.accounts[index]);
                printf("\n");
                printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
                clearStandardInputBuffer();
                option = getCharOption("YN");
                if ((option == 'Y') || (option == 'y'))
                {
                    int x;  // sets ticketNumbers to 0 and status to 0 
                            // sets acctnumbers to 0 in tickets and account
                    for (x = 0; x < TICKET_SIZE; x++)
                        if (data.tickets[x].acctNumber == acct_num)
                        {
                            if (data.tickets[x].ticketStatus == 0)
                            {
                               archiveTickets(data.tickets[x]);
                            }
                            data.tickets[x].ticketNumber = 0;
                            data.tickets[x].acctNumber = 0;
                        }
                    archiveAccounts(data.accounts[index]);
                    data.accounts[index].acctNumber = 0;
                    printf("\n*** Account Removed! ***\n");
                    printf("\n");
                    clearStandardInputBuffer();
                    pauseExecution();
                }
                else 
                {
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
                    if (data.accounts[x].acctNumber != 0)
                    {
                        displayAllAccountSummaryRecords(&data.accounts[x]);
                    }
                printf("\n");
                pauseExecution();
                break;
            }
        case 5: // display detailed accounts
        {
            displayAllAccountDetailHeader();
            displayAllAccountDetailRecords(data);
            printf("\n");
            pauseExecution();
            break;
        }
        case 6: // List new tickets
        {
            printf("\n");
            listNewTicketsHeader();
            displayNewTickets(data);
            printf("\n");
            break;
        }
        case 7: //List active tickets
        {
            printf("\n");
            displayAllTicketsHeader();
            displayAllTicketRecords(data);
            printf("\n");
            break;
        }
        case 8: //list closed tickets
        {
            printf("\n");
            displayAllClosedTicketsHeader();
            displayAllClosedTicketRecords(data);
            printf("\n");
            break;
        }
        case 9: // manage a ticket
        {
            printf("\n");
            manageAllTickets(data, paccount->UserLogin.fullName);
            printf("\n");
            break;
        }
        case 10: // archive closed tickets
        {
     
            archiveClosedTickets(data.tickets, data.TICKET_MAX_SIZE);
            printf("\n");
            pauseExecution();
            break;
        }
        case 11: // view archived account statistics
        {
            printf("\n");
            archivedAccountsStatistics();
            printf("\n");
            pauseExecution();
            break;
        }
        case 12: // view archived ticket statistics
        {
            printf("\n");
            archivedTicketStatistics();
            printf("\n");
            pauseExecution();
            break;
        }
        case 0:
            printf("\n");
            printf("Saving session modifications...\n");
            printf("   %d account saved.\n", 
                saveAccounts(data.accounts, data.ACCOUNT_MAX_SIZE));
            printf("   %d tickets saved.\n", 
                saveTickets(data.tickets, data.TICKET_MAX_SIZE));
            printf("### LOGGED OUT ###\n");
            printf("\n");
            break;
        }
    } while (selection > 0);
    return;
}



void menuClient(struct AccountTicketingData data, const ACCOUNT paccount[], int size)
{
    int selection;

    do
    {
        printf("CUSTOMER: %s (%d)\n", paccount->UserLogin.fullName, paccount->acctNumber);
        printf("==============================================\n");
        printf("Customer Main Menu\n");
        printf("==============================================\n");
        printf("1) View your account detail\n");
        printf("2) Create a new ticket\n");
        printf("3) Modify an active ticket\n");
        printf("4) List my tickets\n");
        printf("----------------------------------------------\n");
        printf("0) Logout\n");
        printf("\nSelection: ");
        selection = getIntFromRange(0, 4);
        switch (selection)
        {
        case 1: // view client account details
        {
            printf("\n");
            displayAccountDetailHeader();
            displayAccountDetailRecord(paccount);
            printf("\n");
            pauseExecution();
            break;
        }
        case 2: // create new ticket
        {
            newTicket(data,
                paccount->acctNumber,
                paccount->UserLogin.fullName);
            printf("\n");
            pauseExecution();
            break;
        }
        case 3://modify active ticket
        {
            modifyActiveTicket(data,
                paccount->acctNumber,
                paccount->UserLogin.fullName);
            printf("\n");
            pauseExecution();
            break;
        }
        case 4: // list clients own tickets
        {
            printf("\n");
            displayTicketListHeader();
            displayTicketListRecords(data, paccount->acctNumber);// client ticket display
            printf("\n");
            break;
        }
        case 0:
        {
            printf("\n");
            printf("Saving session modifications...\n");
            printf("   %d tickets saved.\n", saveTickets(data.tickets, size));
            printf("### LOGGED OUT ###\n");
            printf("\n");
            break;
        }
        }
    } while (selection > 0);
    return;
}

void displayTicketListHeader(void) // client menu option 4
{
    printf("------ ------ ------------------------------ --------\n");
    printf("Ticket Status Subject                        Messages\n");
    printf("------ ------ ------------------------------ --------\n");
}
void displayTicketListRecords(struct AccountTicketingData data, int Number) //client menu option 4
{
    //displays client tickets - open and closed
    int i = 0;
    int j = 0;
    int k = 0;
    int ticket_number = -1;
    char Active[] = "ACTIVE";
    char Closed[] = "CLOSED";
    do
    {
        for (i = 0; i < data.TICKET_MAX_SIZE; i++)
            if (data.tickets[i].acctNumber == Number)
            {
                if (data.tickets[i].ticketStatus == 0)
                    printf("%06d %-6s %-30s %5d\n",
                        data.tickets[i].ticketNumber,
                        Closed,
                        data.tickets[i].ticketSubject,
                        data.tickets[i].ticketCounter);
                if (data.tickets[i].ticketStatus == 1)
                    printf("%06d %-6s %-30s %5d\n",
                        data.tickets[i].ticketNumber,
                        Active,
                        data.tickets[i].ticketSubject,
                        data.tickets[i].ticketCounter);
            }
        printf("------ ------ ------------------------------ --------\n");
        printf("\n");
        printf("Enter the ticket number to view the messages or\n");
        printf("0 to return to previous menu: ");
        ticket_number = getTicketInteger();
        if (ticket_number == 0)
            break;
        {
            for (j = 0; j < data.TICKET_MAX_SIZE; j++)
                if ((data.tickets[j].ticketNumber == ticket_number) &&
                    (data.tickets[j].acctNumber == Number))
                {
                    printf("\n");
                    printf("================================================================================\n");
                    if (data.tickets[j].ticketStatus == 0)
                        printf("%06d (%s) Re: %s\n",
                            data.tickets[j].ticketNumber,
                            Closed,
                            data.tickets[j].ticketSubject);
                    if (data.tickets[j].ticketStatus == 1)
                        printf("%06d (%s) Re: %s\n",
                            data.tickets[j].ticketNumber,
                            Active,
                            data.tickets[j].ticketSubject);
                    printf("================================================================================\n");
                    for (k = 0; k < data.tickets[j].ticketCounter; k++)
                    {
                        if ((k % 5 == 0) && (k != 0)) pauseExecution();
                        if (data.tickets[j].message[k].acctType == 'A')
                        {
                            for (i = 0; Agent[i] != '\0'; i++)
                                type[i] = Agent[i];
                        }type[i] = '\0';
                        if (data.tickets[j].message[k].acctType == 'C')
                        {
                            for (i = 0; Customer[i] != '\0'; i++)
                                type[i] = Customer[i];
                        }type[i] = '\0';
                        printf("%s (%s):\n   %s\n\n",
                            type,
                            data.tickets[j].message[k].fullName,
                            data.tickets[j].message[k].messageDetails);
                    }pauseExecution();
                    displayTicketListHeader();
                    break;
                }
        }
        if ((data.tickets[j].ticketNumber != ticket_number) && (ticket_number != 0))
        {
            printf("\n");
            printf("ERROR: Invalid ticket number - you may only access your own tickets.\n");
            printf("\n");
            pauseExecution();
            displayTicketListHeader();
        }
    } while (ticket_number != 0);
    return;
}

void listNewTicketsHeader(void) //Agent menu option 6
{
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
    printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

void displayNewTickets(struct AccountTicketingData data) //Agent menu option 6
{
    int ticket_number = -1;
    int i = 0;
    int j = 0;
    int k = 0;
    char Active[] = "ACTIVE";
    do
    {   //  new ticket and active ticket display
        for (i = 0; i < data.TICKET_MAX_SIZE; i++)//validation for new open tickets only
            if ((data.tickets[i].ticketStatus == 1) && (data.tickets[i].ticketCounter == 1))
                printf("%06d %-5d %-15s %-6s %-30s %5d\n",
                    data.tickets[i].ticketNumber,
                    data.tickets[i].acctNumber,
                    data.tickets[i].message->fullName,
                    Active,
                    data.tickets[i].ticketSubject,
                    data.tickets[i].ticketCounter);
        printf("------ ----- --------------- ------ ------------------------------ --------\n");
        printf("\n");
        printf("Enter the ticket number to view the messages or\n");
        printf("0 to return to previous menu: ");
        ticket_number = getTicketInteger(); // in commonHelpers
        if (ticket_number == 0)
            break;
        {
            for (j = 0; j < data.TICKET_MAX_SIZE; j++)//validation for new open tickets only
                if ((data.tickets[j].ticketNumber == ticket_number)
                    && (data.tickets[j].ticketCounter == 1)
                    && (data.tickets[j].ticketStatus == 1))
                {
                    printf("\n");
                    printf("================================================================================\n");
                    printf("%06d (%s) Re: %s\n",
                        data.tickets[j].ticketNumber,
                        Active,
                        data.tickets[j].ticketSubject);
                    printf("================================================================================\n");

                    for (k = 0; k < data.tickets[j].ticketCounter; k++)
                    {
                        if ((k % 5 == 0) && (k != 0)) pauseExecution();
                        if (data.tickets[j].message[k].acctType == 'A')
                        {
                            for (i = 0; Agent[i] != '\0'; i++)
                                type[i] = Agent[i];
                        }type[i] = '\0';
                        if (data.tickets[j].message[k].acctType == 'C')
                        {
                            for (i = 0; Customer[i] != '\0'; i++)
                                type[i] = Customer[i];
                        }type[i] = '\0';
                        printf("%s (%s):\n   %s\n\n",
                            type,
                            data.tickets[j].message[k].fullName,
                            data.tickets[j].message[k].messageDetails);
                    }pauseExecution();
                    listNewTicketsHeader();
                    break;
                }
        }
        if ((data.tickets[j].ticketNumber != ticket_number) && (ticket_number != 0))
        {
            printf("\n");
            printf("ERROR: Invalid ticket number.\n");
            printf("\n");
            pauseExecution();
            listNewTicketsHeader();
        }

    } while (ticket_number != 0);
    return;
}

void displayAllTicketsHeader(void) //  agent option 7 all active ticket report display
{
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
    printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

void displayAllTicketRecords(struct AccountTicketingData data)
{
    int ticket_number = -1;
    int i = 0;
    int j = 0;
    int k = 0;
    char Active[] = "ACTIVE";
    do
    {   //  all active ticket report display
        for (i = 0; i < data.TICKET_MAX_SIZE; i++)//validation for all active tickets
            if ((data.tickets[i].ticketStatus == 1) && (data.tickets[i].acctNumber != 0))
                printf("%06d %-5d %-15s %-6s %-30s %5d\n",
                    data.tickets[i].ticketNumber,
                    data.tickets[i].acctNumber,
                    data.tickets[i].message->fullName,
                    Active,
                    data.tickets[i].ticketSubject,
                    data.tickets[i].ticketCounter);
        printf("------ ----- --------------- ------ ------------------------------ --------\n");
        //================================================================================//
        printf("\n");
        printf("Enter the ticket number to view the messages or\n");
        printf("0 to return to previous menu: ");
        ticket_number = getTicketInteger(); // in commonHelpers
        if (ticket_number == 0)
            break;
        {
            for (j = 0; j < data.TICKET_MAX_SIZE; j++)//validation for all active tickets 
                if ((data.tickets[j].ticketNumber == ticket_number)
                    && (data.tickets[j].ticketStatus == 1))
                {
                    printf("\n");
                    printf("================================================================================\n");
                    printf("%06d (%s) Re: %s\n",
                        data.tickets[j].ticketNumber,
                        Active,
                        data.tickets[j].ticketSubject);
                    printf("================================================================================\n");
                    for (k = 0; k < data.tickets[j].ticketCounter; k++)
                    {
                        if ((k % 5 == 0) && (k != 0)) pauseExecution();
                        if (data.tickets[j].message[k].acctType == 'A')
                        {
                            for (i = 0; Agent[i] != '\0'; i++)
                                type[i] = Agent[i];
                        }type[i] = '\0';
                        if (data.tickets[j].message[k].acctType == 'C')
                        {
                            for (i = 0; Customer[i] != '\0'; i++)
                                type[i] = Customer[i];
                        }type[i] = '\0';
                        printf("%s (%s):\n   %s\n\n",
                            type,
                            data.tickets[j].message[k].fullName,
                            data.tickets[j].message[k].messageDetails);
                    }pauseExecution();
                    displayAllTicketsHeader();
                    break;
                }
        }
        if ((data.tickets[j].ticketNumber != ticket_number)
            && (ticket_number != 0))
        {
            printf("\n");
            printf("ERROR: Invalid ticket number.\n");
            printf("\n");
            pauseExecution();
            displayAllTicketsHeader();
        }
    } while (ticket_number != 0);
    return;
}

void displayAllClosedTicketsHeader(void) //  agent option 8 all closed ticket report display
{
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
    printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
    printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

void displayAllClosedTicketRecords(struct AccountTicketingData data)
{
    int ticket_number = -1;
    int i = 0;
    int j = 0;
    int k = 0;
    char Closed[] = "CLOSED";
    do
    {   //  all closed ticket report display
        for (i = 0; i < data.TICKET_MAX_SIZE; i++)//validation for all closed tickets
            if ((data.tickets[i].ticketStatus == 0)
                && (data.tickets[i].ticketNumber != 0))
                printf("%06d %-5d %-15s %-6s %-30s %5d\n",
                    data.tickets[i].ticketNumber,
                    data.tickets[i].acctNumber,
                    data.tickets[i].message->fullName,
                    Closed,
                    data.tickets[i].ticketSubject,
                    data.tickets[i].ticketCounter);
        printf("------ ----- --------------- ------ ------------------------------ --------\n");
        //================================================================================//
        printf("\n");
        printf("Enter the ticket number to view the messages or\n");
        printf("0 to return to previous menu: ");

        ticket_number = getTicketInteger(); // in commonHelpers
        if (ticket_number == 0)
            break;
        {
            for (j = 0; j < data.TICKET_MAX_SIZE; j++)//validation for all closed tickets 
                if ((data.tickets[j].ticketNumber == ticket_number)
                    && (data.tickets[j].ticketStatus == 0))
                {
                    printf("\n");
                    printf("================================================================================\n");
                    printf("%06d (%s) Re: %s\n",
                        data.tickets[j].ticketNumber,
                        Closed,
                        data.tickets[j].ticketSubject);
                    printf("================================================================================\n");
                    for (k = 0; k < data.tickets[j].ticketCounter; k++)
                    {
                        if ((k % 5 == 0) && (k != 0)) pauseExecution();
                        if (data.tickets[j].message[k].acctType == 'A')
                        {
                            for (i = 0; Agent[i] != '\0'; i++)
                                type[i] = Agent[i];
                        }type[i] = '\0';
                        if (data.tickets[j].message[k].acctType == 'C')
                        {
                            for (i = 0; Customer[i] != '\0'; i++)
                                type[i] = Customer[i];
                        }type[i] = '\0';
                        printf("%s (%s):\n   %s\n\n",
                            type,
                            data.tickets[j].message[k].fullName,
                            data.tickets[j].message[k].messageDetails);
                    }pauseExecution();
                    displayAllTicketsHeader();
                    break;
                }
        }
        if ((data.tickets[j].ticketNumber != ticket_number)
            && (ticket_number != 0))
        {
            printf("\n");
            printf("ERROR: Invalid ticket number.\n");
            printf("\n");
            pauseExecution();
            displayAllTicketsHeader();
        }
    } while (ticket_number != 0);
    return;
}

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

//client new ticket case 2
void newTicket(struct AccountTicketingData data, int Number, const char* FullName)
{
    int j, c;
    int location = 0;
    int highestTicketNumber = 0;
    char customer = 'C';
    char subject[31] = { 0 };
    char message[151] = { 0 };

    for (j = 0; j < data.TICKET_MAX_SIZE; j++)
        if (data.tickets[j].ticketNumber == 0)
            if (j < data.TICKET_MAX_SIZE)
            {
                for (c = 1; c < data.TICKET_MAX_SIZE; c++)
                    if (data.tickets[c].ticketNumber > data.tickets[location].ticketNumber)
                    {
                        location = c;
                    }
                highestTicketNumber = data.tickets[location].ticketNumber;
                data.tickets[j].ticketNumber = highestTicketNumber + 1;
                printf("\n");
                printf("New Ticket (Ticket#:%06d)\n", data.tickets[j].ticketNumber);
                printf("----------------------------------------\n");
                printf("Enter the ticket SUBJECT (30 chars. maximum): ");
                getCString(subject, 2, 30);
                strcpy(data.tickets[j].ticketSubject, subject);
                data.tickets[j].message[0].acctType = customer;
                strcpy(data.tickets[j].message[0].fullName, FullName);
                printf("\n");
                printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
                getCString(message, 2, 150);
                strcpy(data.tickets[j].message[0].messageDetails, message);
                data.tickets[j].ticketCounter = data.tickets[j].ticketCounter + 1;
                data.tickets[j].acctNumber = Number;
                data.tickets[j].ticketStatus = 1;

                printf("\n");
                printf("*** New ticket created! ***\n");
                break;
            }
    if (j >= data.TICKET_MAX_SIZE)
    {
        printf("\n");
        printf("ERROR: Ticket listing is FULL, call ITS Support!\n");
    }
    return;
}

//client modify ticket case 3
void modifyActiveTicket(struct AccountTicketingData data, int Number, const char* FullName)
{
    int ticketNumber = 0;
    int validTicket = 0;
    int j = 0; int i = 0;
    int selection = 0;
    char subject[31] = { 0 };
    char message[151] = { 0 };
    char customer = 'C';
    char option;
    char closingMessageOption;

    printf("\n");
    printf("Enter ticket number: ");
    ticketNumber = getPositiveInteger();
    for (j = 0; j < data.TICKET_MAX_SIZE; j++)
    {
        if (ticketNumber == data.tickets[j].ticketNumber &&
            data.tickets[j].acctNumber == Number)
        {
            validTicket = 1;
            break;
        }
    }
    if ((data.tickets[j].ticketStatus == 0) && (data.tickets[j].acctNumber == Number))
    {
        printf("\n");
        printf("ERROR: Ticket is closed - changes are not permitted.");
        printf("\n");
        clearStandardInputBuffer();
        return;
    }
    if (validTicket == 1)
    {
        do
        {

            printf("\n");
            printf("----------------------------------------\n");
            printf("Ticket %06d - Update Options\n", ticketNumber);
            printf("----------------------------------------\n");
            printf("Status  : %s\n",
                data.tickets[j].ticketStatus == 1 ? "ACTIVE" : "CLOSED");
            printf("Subject : %s\n",
                data.tickets[j].ticketSubject);
            printf("----------------------------------------\n");

            printf("1) Modify the subject\n");
            printf("2) Add a message\n");
            printf("3) Close ticket\n");
            printf("0) Done\n");
            printf("Selection: ");
            selection = getIntFromRange(0, 3);
            switch (selection)
            {
            case 1: //modify subject
                printf("\n");
                printf("Enter the revised ticket SUBJECT (30 chars. maximum): ");
                getCString(subject, 2, 30);
                strcpy(data.tickets[j].ticketSubject, subject);
                break;
            case 2: //add message
                for (i = 0; i < 20; i++)
                    if (data.tickets[j].message[i].acctType == '\0')
                    {
                        data.tickets[j].message[i].acctType = customer;
                        strcpy(data.tickets[j].message[i].fullName, FullName);
                        printf("\n");
                        printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
                        getCString(message, 2, 150);
                        strcpy(data.tickets[j].message[i].messageDetails, message);
                        data.tickets[j].ticketCounter = data.tickets[j].ticketCounter + 1;
                        break;
                    }
                if (i == 20)
                {
                    printf("\n");
                    printf("ERROR: Message limit has been reached, call ITS Support!\n");
                }
                break;
            case 3: //close ticket
                printf("\n");
                printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
                option = getToUpperCharOption("YN");
                if ((option == 'Y') || (option == 'y'))
                {
                    data.tickets[j].ticketStatus = 0;
                    if (data.tickets[j].ticketCounter >= 20)
                    {
                        printf("\n");
                        printf("*** Ticket closed! ***\n");
                        selection = -1;
                        clearStandardInputBuffer();
                        break;
                    }
                    printf("\n");
                    printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
                    clearStandardInputBuffer();
                    closingMessageOption = getToUpperCharOption("YN");
                    if ((closingMessageOption == 'N') || (closingMessageOption == 'n'))
                        clearStandardInputBuffer();
                    if ((closingMessageOption == 'Y') || (closingMessageOption == 'y'))
                    {
                        for (i = 0; i < 20; i++)
                            if (data.tickets[j].message[i].acctType == '\0')
                            {
                                data.tickets[j].message[i].acctType = customer;
                                strcpy(data.tickets[j].message[i].fullName, FullName);
                                printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
                                clearStandardInputBuffer();
                                getCString(message, 2, 150);
                                strcpy(data.tickets[j].message[i].messageDetails, message);
                                data.tickets[j].ticketCounter = data.tickets[j].ticketCounter + 1;
                                break;
                            }
                    }
                    if (i > 20)
                    {
                        printf("ERROR: Message limit has been reached, call ITS Support!\n");
                    }
                    if (data.tickets[j].ticketStatus == 0)
                    {
                        printf("\n");
                        printf("*** Ticket closed! ***\n");
                        selection = -1;
                        break;
                    }
                }
                if (option == 'N')
                    break;
            case 0: // done
                break;
            }
        } while (selection > 0);
    }
    else {
        printf("\n");
        clearStandardInputBuffer();
        printf("ERROR: Invalid ticket number - you may only modify your own ticket.\n");
        // pauseExecution();
    }
    return;
}

void manageAllTickets(struct AccountTicketingData data, const char* FullName) // agent menu option 9
{
    int ticketNumber = 0;
    int j = 0; int i = 0;
    int selection = 0;
    char message[151] = { 0 };
    char closingMessageOption;
    char agent = 'A';
    char option;

    printf("Enter ticket number: ");
    ticketNumber = getPositiveInteger();
    for (j = 0; j < data.TICKET_MAX_SIZE; j++)
    {
        if (ticketNumber == data.tickets[j].ticketNumber)
        {
            break;
        }
    }
    do
    {
        printf("\n");
        printf("----------------------------------------\n");
        printf("Ticket %06d - Update Options\n", ticketNumber);
        printf("----------------------------------------\n");
        printf("Status  : %s\n",
            data.tickets[j].ticketStatus == 1 ? "ACTIVE" : "CLOSED");
        printf("Subject : %s\n",
            data.tickets[j].ticketSubject);
        printf("Acct#   : %d\n",
            data.tickets[j].acctNumber);
        printf("Customer: %s\n",
            data.tickets[j].message->fullName);
        printf("----------------------------------------\n");
        printf("1) Add a message\n");
        printf("2) Close ticket\n");
        printf("3) Re-open ticket\n");
        printf("0) Done\n");
        printf("Selection: ");
        selection = getIntFromRange(0, 3);
        switch (selection)
        {
        case 1: //add a message
            if (data.tickets[j].ticketStatus == 0)
            {
                printf("\n");
                printf("ERROR: Ticket is closed - new messages are not permitted.\n");
                break;
            }
            for (i = 0; i < 20; i++)
                if (data.tickets[j].message[i].acctType == '\0')
                {
                    data.tickets[j].message[i].acctType = agent;
                    strcpy(data.tickets[j].message[i].fullName, FullName);
                    printf("\n");
                    printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
                    getCString(message, 2, 150);
                    strcpy(data.tickets[j].message[i].messageDetails, message);
                    data.tickets[j].ticketCounter = data.tickets[j].ticketCounter + 1;
                    break;
                }
            if (i == 20)
            {
                printf("\n");
                printf("ERROR: Message limit has been reached, call ITS Support!\n");
            }
            break;
        case 2: //close ticket
            if (data.tickets[j].ticketStatus == 0)
            {
                printf("\n");
                printf("ERROR: Ticket is already closed!\n");
                break;
            }
            printf("\n");
            printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
            option = getToUpperCharOption("YN");
            if ((option == 'Y') && (data.tickets[j].ticketCounter < 20))
            {
                data.tickets[j].ticketStatus = 0;
                printf("\n");
                printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
                clearStandardInputBuffer();
                closingMessageOption = getToUpperCharOption("YN");
                clearStandardInputBuffer();
                if ((closingMessageOption == 'Y') || (closingMessageOption == 'y'))
                {
                    for (i = 0; i < 20; i++)
                        if (data.tickets[j].message[i].acctType == '\0')
                        {
                            data.tickets[j].message[i].acctType = agent;
                            strcpy(data.tickets[j].message[i].fullName, FullName);
                            printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
                            getCString(message, 2, 150);
                            strcpy(data.tickets[j].message[i].messageDetails, message);
                            data.tickets[j].ticketCounter = data.tickets[j].ticketCounter + 1;
                            break;
                        }
                }
                if (i == 20)
                {
                    printf("\n");
                    printf("ERROR: Message limit has been reached, call ITS Support!\n");
                }
                if (data.tickets[j].ticketStatus == 0)
                {
                    printf("\n");
                    printf("*** Ticket closed! ***\n");
                    break;
                }
            }
            if ((option == 'Y') && (data.tickets[j].ticketCounter == 20))//closes full ticket account
            {
                    data.tickets[j].ticketStatus = 0;
                    printf("\n");
                    printf("*** Ticket closed! ***\n");
                    break;
            }
            
            if (option == 'N')
            {
                break;
            }
        case 3: //re-open ticket
            if (data.tickets[j].ticketStatus == 1)
            {
                printf("\n");
                printf("ERROR: Ticket is already active!\n");
                break;
            }
            printf("\n");
            printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
            option = getToUpperCharOption("YN");
            if ((option == 'Y') || (option == 'y'))
            {
                data.tickets[j].ticketStatus = 1;
            }

            if (data.tickets[j].ticketStatus == 1)
            {
                printf("\n");
                printf("*** Ticket re-opened! ***\n");
                break;
            }
            if (option == 'N')
                break;
        case 0: // done
            break;
        }
    } while (selection > 0);
    return;
}

int loadTickets(struct Ticket* tickets, int size)
{
    int i = 0, j;
    FILE* fp = NULL;
    fp = fopen("tickets.txt", "r");
    if (fp == NULL)
    {
        printf("ERROR: Can't open tickets.txt file.\n");
        exit(1);
    }
    while (fscanf(fp, "%d%*c%d%*c%d%*c%[^|]%*c%d%*c",
        &tickets[i].ticketNumber,
        &tickets[i].acctNumber,
        &tickets[i].ticketStatus,
        tickets[i].ticketSubject,
        &tickets[i].ticketCounter) != EOF)
    {
        if (i == size - 1)
        {
            i = size;
            break;
        }
        if (tickets[i].ticketCounter > 20)
        {
            tickets[i].ticketCounter = 20;
            for (j = 0; j < tickets[i].ticketCounter; j++)
            {
                fscanf(fp, "%c%*c%[^|]%*c%[^|]%*c",
                    &tickets[i].message[j].acctType,
                    tickets[i].message[j].fullName,
                    tickets[i].message[j].messageDetails);
            }
            fscanf(fp, "%*[^\n]");
        }
        else
        { 
            for (j = 0; j < tickets[i].ticketCounter; j++)
            {
                fscanf(fp,"%c%*c%[^|]%*c%[^|]%*c",
                    &tickets[i].message[j].acctType,
                    tickets[i].message[j].fullName,
                    tickets[i].message[j].messageDetails);
            }
        }
        i++;
    }
    fclose(fp);
    return i;
}

int saveTickets(struct Ticket* tickets, int size)
{
    int i = 0;
    int savedTicketCount = 0;
    FILE* fp = NULL;
    fp = fopen("tickets.txt", "w");
    if (fp == NULL)
    {
        printf("ERROR: Can't open tickets.txt file.\n");
        exit(1);
    }
    for (i = 0; i < size; i++)
    {
        if (tickets[i].ticketNumber != 0)
        {
            writeTicket(tickets[i],fp);
            savedTicketCount++;
        }
    }
    fclose(fp);
    return savedTicketCount;
}

int archiveTickets(struct Ticket ticket)
{
    FILE* fp = NULL;
    fp = fopen("tickets_arc.txt", "a");
    if (fp == NULL)
    {
        printf("ERROR: Can't open tickets_arc.txt file.\n");
        exit(1);
    }
    writeTicket(ticket, fp);
    fclose(fp);
    return 1;
}

int writeTicket(struct Ticket ticket, FILE* fp)
{
    int messageCount = 0;
    int j = 0;
    if (ticket.ticketNumber != 0)
    {
        fprintf(fp,"%d|%d|%d|%s|%d|",
        ticket.ticketNumber,
        ticket.acctNumber,
        ticket.ticketStatus,
        ticket.ticketSubject,
        ticket.ticketCounter);
        for (j = 0; j < ticket.ticketCounter; j++)
        {
            fprintf(fp,"%c|%s|%s|",
            ticket.message[j].acctType,
            ticket.message[j].fullName,
            ticket.message[j].messageDetails);
            messageCount++; 
        }
        fprintf(fp, "\n");
    }
    return messageCount;
}

int archiveClosedTickets(struct Ticket* tickets, int size)
{
    int i = 0;
    char option;
    int archivedTicketCount = 0;
    printf("\nAre you sure? This action cannot be reversed. ([Y]es|[N]o): ");
    option = getToUpperCharOption("YN");
    if ((option == 'Y') || (option == 'y'))
    {
        FILE* fp = NULL;
        fp = fopen("tickets_arc.txt", "a");
  
        if (fp == NULL)
        {
            printf("ERROR: Can't open tickets_arc.txt file.\n");
            exit(1);
        }
        for (i = 0; i < size; i++)
        {
            if ((tickets[i].ticketStatus == 0) && (tickets[i].ticketNumber != 0))
            {
                writeTicket(tickets[i], fp);
                tickets[i].ticketNumber = 0;
                tickets[i].acctNumber = 0;
                tickets[i].ticketStatus = 0;
                archivedTicketCount++;
            }  
        }fclose(fp);
    }
    printf("\n");
    printf("*** %d tickets archived ***\n", archivedTicketCount);
    clearStandardInputBuffer();
    return archivedTicketCount;
} 

void archivedTicketStatistics() 
{
    int totalArchivedTickets = 0; 
    int totalArchivedMessages = 0;
    int ticketNumber = 0;
    int accountNumber = 0; 
    int ticketStatus = 0;
    int messageCount = 0;
    char subject[31] = { '\0' };

    FILE* fp;
    fp = fopen("tickets_arc.txt", "r");
    if (fp == NULL)
    {
        printf("ERROR: Can't open tickets_arc.txt archive file.\n");
        exit(1);
    }
    while (fscanf(fp, "%d|%d|%d|%[^|]|%d|%*[^\n]",
        &ticketNumber,
        &accountNumber,
        &ticketStatus,
        subject,
        &messageCount) != EOF) 
    {
        totalArchivedMessages = totalArchivedMessages + messageCount;
        totalArchivedTickets++;
    }
    fclose(fp);
    if (totalArchivedTickets >= 0)
        printf("There are %d ticket(s) and a total of %d message(s) archived.\n", 
            totalArchivedTickets, 
            totalArchivedMessages);
    return;
}


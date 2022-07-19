/*
Assignment#2 Milestone#4
Richard Lowe
140804204
rlowe1@myseneca.ca
IPC144NHH
*/


#ifndef TICKET_HEADER_
#define TICKET_HEADER_

#include "account.h"

typedef struct Message {
    char acctType;
    char fullName[31];
    char messageDetails[151];
}MESSAGE;

typedef struct Ticket {
    int ticketNumber;
    int acctNumber;
    int ticketStatus;
    char ticketSubject[31];
    int ticketCounter;
    MESSAGE message[20];
}TICKET;

struct AccountTicketingData
{
    struct Account* accounts; // array of accounts
    const int ACCOUNT_MAX_SIZE; // maximum elements for account array
    struct Ticket* tickets; // array of tickets
    const int TICKET_MAX_SIZE; // maximum elements for ticket array
};

#endif 


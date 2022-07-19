/*
Assignment#2 Milestone#4
Richard Lowe
140804204
rlowe1@myseneca.ca
IPC144NHH
*/


#include "account.h"
#include "ticket.h"
#include "commonHelpers.h"

#ifndef ACCT_TICKET
#define ACCT_TICKET

void displayAccountSummaryHeader(void);

void displayAccountSummaryRecord(const ACCOUNT* account);

void displayAccountDetailHeader(void);

void displayAccountDetailRecord(const ACCOUNT* account);

void applicationStartup(struct AccountTicketingData* data);

int  menuLogin(const ACCOUNT account[], int size);

void menuAgent(struct AccountTicketingData data, const ACCOUNT paccount[]);

void menuClient(struct AccountTicketingData data, const ACCOUNT paccount[], int);

int  findAccountIndexByAcctNum(int, const ACCOUNT account[], int, int);

void displayAllAccountSummaryHeader(void);

void displayAllAccountSummaryRecords(const ACCOUNT* account);

void displayAllAccountDetailHeader(void);

void displayAllAccountDetailRecords(struct AccountTicketingData data);

int  isAgent(ACCOUNT*);

void displayTicketListHeader(void);

void displayTicketListRecords(struct AccountTicketingData data, int);

void displayAllTicketsHeader(void);

void displayAllTicketRecords(struct AccountTicketingData data);

void listNewTicketsHeader(void);

void displayNewTickets(struct AccountTicketingData data);

void modifyActiveTicket(struct AccountTicketingData data, int, const char* FullName);

void newTicket(struct AccountTicketingData data, int, const char* FullName);

void manageAllTickets(struct AccountTicketingData data, const char* FullName);

void displayAllClosedTicketsHeader(void);

void displayAllClosedTicketRecords(struct AccountTicketingData data);

int  loadTickets(struct Ticket* tickets, int);

int  saveTickets(struct Ticket* tickets, int);

int  loadAccounts(struct Account* accounts, int);

int  saveAccounts(struct Account* accounts, int);

int  writeTicket(struct Ticket ticket, FILE* fp);

int  archiveTickets(struct Ticket ticket);

int  archiveAccounts(struct Account accounts);

int  writeAccount(struct Account accounts, FILE* fp);

int  archiveClosedTickets(struct Ticket* tickets, int);

void archivedTicketStatistics(void);

void archivedAccountsStatistics(void);
#endif 



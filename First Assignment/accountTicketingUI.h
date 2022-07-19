/*
Assignment#1 Milestone#4
Richard Lowe
140804204
rlowe1@myseneca.ca
IPC144NHH
*/



#ifndef ACCT_TICKET
#define ACCT_TICKET


void displayAccountSummaryHeader(const ACCOUNT* account);

void displayAccountSummaryRecord(const ACCOUNT* account);

void displayAccountDetailHeader(const ACCOUNT* account);

void displayAccountDetailRecord(const ACCOUNT* account);

void applicationStartup(ACCOUNT account[], int size);

int menuLogin(const ACCOUNT account[], int size);

void menuAgent( ACCOUNT account[], int, const ACCOUNT*);

int findAccountIndexByAcctNum(int, const ACCOUNT account[], int, int);

void displayAllAccountSummaryHeader(void);

void displayAllAccountSummaryRecords(const ACCOUNT* account);

void displayAllAccountDetailHeader(void);

void displayAllAccountDetailRecords(const ACCOUNT*);

int isAgent(ACCOUNT*);
#endif 

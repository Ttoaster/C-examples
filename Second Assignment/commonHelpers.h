/*
Assignment#2 Milestone#4
Richard Lowe
140804204
rlowe1@myseneca.ca
IPC144NHH
*/
#define _CRT_SECURE_NO_WARNINGS

#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_



int    currentYear(void);

void   clearStandardInputBuffer(void);

int    getInteger(void);

int    getPositiveInteger(void);

int    getIntFromRange(int lowNumber, int highNumber);
 
double getDouble(void);

double getPositiveDouble(void);

char   getCharOption(const char string[]);

char   getToUpperCharOption(const char string[]);

char   getCString(char* cstringValue, int y, int x);

void   pauseExecution(void);

int    getTicketInteger(void);

#endif // !COMMON_HELPERS_H_



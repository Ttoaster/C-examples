/*
Assignment#1 Milestone#4
Richard Lowe
140804204
rlowe1@myseneca.ca
IPC144NHH
*/

//#define _CRT_SECURE_NO_WARNINGS

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

typedef struct Demographic {
    int birthYear;
    double houseHoldIncome;
    char countryResidence[31];
}DEMO;

typedef struct UserLogin {
    char fullName[31];
    char userName[11];
    char password[9];
}LOGIN;

typedef struct Account {
    int acctNumber;
    char acctType;
    LOGIN UserLogin;
    DEMO Demographic;
}ACCOUNT;

void getAccountData(ACCOUNT* account);

void getUserLogin(ACCOUNT* account);

void getDemographic(ACCOUNT* account);

void updateAccount(ACCOUNT* );

void updateUserLogin(ACCOUNT*);

void updateDemographic(ACCOUNT*);



#endif //  !ACCOUNT_H_

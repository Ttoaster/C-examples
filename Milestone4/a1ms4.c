// ============================================================================
//  Assignment: 1 
//  Milestone : 4
// ============================================================================


// ****************************************************************************
// ****************************************************************************
// ****************************************************************************
//                   DO NOT MODIFY THIS FILE!!!!
// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

#define _CRT_SECURE_NO_WARNINGS

// System Libraries
#include <stdio.h>

// User Libraries
#include "account.h"
#include "accountTicketingUI.h"

// Macro's: helpers for default data
#define ACCOUNT_SIZE 50
#define INIT_DATA_SIZE 5

// Function Prototype for populating some default values
void populateAccounts(struct Account accounts[], int arrSize);


// Main entry-point to the application
int main(void)
{
    struct Account accounts[ACCOUNT_SIZE] = { {0} };

    // setup some test accounts:
    populateAccounts(accounts, ACCOUNT_SIZE);

    // launch application logic
    applicationStartup(accounts, ACCOUNT_SIZE);

    return 0;
}

void populateAccounts(struct Account accounts[], int arrSize)
{
    int i, max = arrSize < INIT_DATA_SIZE ? arrSize : INIT_DATA_SIZE;
    struct Account tmp[INIT_DATA_SIZE] = {
        { 50001, 'C', {"Silly Sally", "cust1", "password"}, {1990, 150000.10, "CANADA"} },
        { 50028, 'A', {"Fred Flintstone", "agent1", "yabadaba"}, {1972, 2250400.22, "AFRICA"} },
        { 50004, 'C', {"Betty Boop", "cust2", "pepper33"}, {1978, 250800.74, "INDIA"} },
        { 50008, 'A', {"Will Smith", "agentJ", "theboss1"}, {1952, 2350600.82, "U.S.A."} },
        { 50020, 'C', {"Shrimpy Shrimp", "cust3", "jimmyjim"}, {2000, 350500.35, "KOREA"} }
    };

    // Copy test data
    for (i = 0; i < max; i++)
    {
        accounts[i] = tmp[i];
    }
}
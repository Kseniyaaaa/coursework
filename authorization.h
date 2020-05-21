#pragma once

#include "account_operations.h"
#include "structures.h"

#include <vector>

void showAccountsMenu();

void authorize(vector<Account>& accounts, vector<Participant>& records);
void login(vector<Account> &accounts, vector<Participant>& records);
void registration(vector<Account> &accounts);

string transformPassword();
//void hashPassword(Account account);
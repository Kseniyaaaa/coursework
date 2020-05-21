#pragma once

#include <vector>
#include "structures.h"

using namespace std;

Account* getAccount(vector<Account> &accounts, string login);
Account* createFirstAdmin();

void showAccount(vector<Account> accounts);
void addAccount(vector<Account> &accounts);
void editAccount(vector<Account>& accounts);
void editionMenu(Account& account);
void deleteAccount(vector<Account>& accounts, Account current_account);
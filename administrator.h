#pragma once

#include "account_operations.h"
#include "structures.h"

#include <vector>

void showAdminMenu(vector<Account>& accounts, Account current_account, vector<Participant>& records);
void showAdminAccountMenu(vector<Account>& accounts, Account current_account);
void showAdminDataMenu(vector<Participant>& records);



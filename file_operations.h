#pragma once

#include "account_operations.h"
#include "structures.h"

#include <vector>

using namespace std;

vector<Account> readAccountsFile();
void writeAccountFile(vector<Account> accounts);
void writeToEndAccountFile(Account account);

vector<Participant> readRecordsFile();
void writeRecordFile(vector<Participant> records);
void writeToEndRecordsFile(Participant record);
#include "authorization.h"
#include "account_operations.h"
#include "file_operations.h"
#include "structures.h"

#include <iostream>
#include <Windows.h>

using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vector<Account> accounts = readAccountsFile();
	vector<Participant> records = readRecordsFile();

	authorize(accounts, records);

	system("pause");
}

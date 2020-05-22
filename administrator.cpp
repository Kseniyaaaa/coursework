#include "account_operations.h"
#include "data_operations.h"
#include "administrator.h"
#include "validation.h"
#include "structures.h"

#include <iostream>

using namespace std;

void showAdminMenu(vector<Account>& accounts, Account current_account, vector<Participant>& records)
{
	int item;
	while (true)
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1 - Работа с учетными записями " << endl
			<< "2 - Работа с данными " << endl
			<< "0 - ВЫХОД" << endl;
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			showAdminAccountMenu(accounts, current_account);
			break;

		case 2:
			showAdminDataMenu(records);
			break;

		default:
			cout << "Выберите еще раз" << endl;
			break;
		}
	}
}

void showAdminAccountMenu(vector<Account>& accounts, Account current_account)
{
	int item;

	while (true)
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1. Просмотреть учетные записи " << endl
			<< "2. Добавить учетную запись " << endl
			<< "3. Отредактировать учетную запись " << endl
			<< "4. Удалить учетную запись" << endl
			<< "0. ВЫХОД" << endl;
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			showAccount(accounts);
			break;

		case 2:
			addAccount(accounts);
			break;

		case 3:
			editAccount(accounts);
			break;

		case 4:
			deleteAccount(accounts, current_account);
			break;

		default:
			cout << "Выберите еще раз" << endl;
			break;
		}
	}
}


void showAdminDataMenu(vector<Participant>& records)
{
	int item;

	while (true)
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1. Просмотреть данные о конкурсе" << endl
			<< "2. Добавить участника/ов конкурса " << endl
			<< "3. Отредактировать данные о конкурсе" << endl
			<< "4. Найти участника конкурса" << endl
			<< "5. Отсортировать данные " << endl
			<< "6. Выполнить индивидуальное задание " << endl
			<< "7. Удалить определенные данные" << endl
			<< "8. Удалить данные" << endl
			<< "0. ВЫХОД" << endl;
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			showData(records);
			break;

		case 2:
			addRecord(records);
			break;

		case 3:
			editData(records);
			break;

		case 4:
			showFindingMenu(records);
			break;

		case 5:
			showSortingMenu(records);
			break;

		case 6:
			Task(records);
			break;

		case 7:
			deleteRecord(records);
			break;

		case 8:
			deleteData(records);
			break;

		default:
			cout << "Выберите еще раз" << endl;
			break;
		}
	}
}



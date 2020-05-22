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
		cout << "1 - ������ � �������� �������� " << endl
			<< "2 - ������ � ������� " << endl
			<< "0 - �����" << endl;
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
			cout << "�������� ��� ���" << endl;
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
		cout << "1. ����������� ������� ������ " << endl
			<< "2. �������� ������� ������ " << endl
			<< "3. ��������������� ������� ������ " << endl
			<< "4. ������� ������� ������" << endl
			<< "0. �����" << endl;
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
			cout << "�������� ��� ���" << endl;
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
		cout << "1. ����������� ������ � ��������" << endl
			<< "2. �������� ���������/�� �������� " << endl
			<< "3. ��������������� ������ � ��������" << endl
			<< "4. ����� ��������� ��������" << endl
			<< "5. ������������� ������ " << endl
			<< "6. ��������� �������������� ������� " << endl
			<< "7. ������� ������������ ������" << endl
			<< "8. ������� ������" << endl
			<< "0. �����" << endl;
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
			cout << "�������� ��� ���" << endl;
			break;
		}
	}
}



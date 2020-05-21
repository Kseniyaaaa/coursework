#include "authorization.h"
#include "account_operations.h"
#include "data_operations.h"
#include "administrator.h"
#include "user.h"
#include "validation.h"
#include "file_operations.h"
#include "structures.h"

#include <iostream>

using namespace std;



void showAccountsMenu()
{
	cout << "�����������: " << endl
		<< "1. ����� " << endl
		<< "2. ������������������ " << endl
		<< "0. �����" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
}


void authorize(vector<Account>& accounts, vector<Participant>& records)
{
	int item;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~����� ����������!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	while (true)
	{
		showAccountsMenu();
		item = getNumber();

		switch (item)
		{
		case 0:
			return;

		case 1:
			login(accounts, records);
			break;

		case 2:
			registration(accounts);
			break;

		default:
			cout << "�������� ��� ���" << endl;
			break;
		}
	}
}


void login(vector<Account> &accounts, vector<Participant>& records)
{
	string login, password;
	cout << "������� �����: ";
	cin >> login;
	cout << "������� ������: ";
	password = transformPassword();

	Account* account = getAccount(accounts, login);

	if (account == NULL) {
		cout << "������ ������������ �� ����������." << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		return;
	}
	else if (account->password != password) {
		cout << "��������� ��������� ������." << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		return;
	}

	if (account->role == 1) {
		cout << "�� �������������." << endl;
		cout << "���� �������� �������." << endl;
		showAdminMenu(accounts, *account, records);
	}
	else {
		if (account->access == 0) {
			cout << "�� �� ������ ����� � �������. �������� ������������� ��������������." << endl;
			cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
			return;
		}
		else {
			cout << "�� ������������." << endl;
			cout << "���� �������� �������." << endl;
			writeToEndAccountFile(*account);
			showUserMenu(records);
		}
	}
}


void registration(vector<Account> &accounts)
{
	string login, password, password2;
	cout << "������� �����: " << endl;
	cin >> login;
	do {
		cout << "������� ������: ";
		password = transformPassword();
		cout << "����������� ������: ";
		password2 = transformPassword();
	} while (password != password2);

	Account* account = new Account;
	account->login = login;
	account->password = password;
	account->role = 0;
	account->access = 0;

	accounts.push_back(*account);
}


string transformPassword()
{
	string password;
	int ch = 0;
	while (true)
	{
		ch = _getwch();                                                                                // ���������� ������� �������

		if (ch == 13)                                                                                    // ��� Enter
		{
			break;
		}
		else {
			if (ch == 8)
			{
				if (!password.empty()) {      
					cout << (char)8 << ' ' << (char)8;
					password.erase(password.length() - 1);
				}
			}
			else
			{
				cout << "*";
				password += (char)ch;
			}
		}
	}
	cout << endl;
	return password;
}


//void hashPassword(Account account)
//{
//	const int p = 33;
//	long long hash = 0, p_pow = 1;
//	for (size_t i = 0; i < account.password.length(); ++i)
//	{
//		hash += (account.password[i] - 'a' + 1) * p_pow;
//		p_pow *= p;
//	}
//}
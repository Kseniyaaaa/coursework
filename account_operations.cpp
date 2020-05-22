#include <string>
#include <fstream>
#include <iostream>

#include "account_operations.h"
#include "file_operations.h"
#include "validation.h"
#include "structures.h"
#include "authorization.h"

const string FILE_OF_ACCOUNTS = "accounts.txt";
const int SALT_LENGTH = 7;


Account* getAccount(vector<Account> &accounts, string login)
{

	for(int i = 0; i < accounts.size(); i++)
	{
		if (accounts[i].login == login) {
			return &accounts[i];
		}
	}
	return NULL;
}


Account* createFirstAdmin()
{
	Account* account = new Account;
	account->login = "admin";
	account->salt = getSalt();
	account->hash_password = hashPassword("admin", account->salt);
	account->role = 1;
	account->access = 1;

	ofstream fout(FILE_OF_ACCOUNTS, ios::out);
	fout << account->login << " "
		<< account->hash_password << " "
		<< account->salt << " "
		<< account->role << " "
		<< account->access;
	fout.close();
	return account;
}


void showAccount(vector<Account> accounts)
{
	cout << "  =================================== " << endl;
	cout << " | " << " ����� " << "  |"
		<< " ������ " << " |" << "     ���� " << "    |" << endl;
	cout << "  =================================== " << endl;
	for (int i = 0; i < accounts.size(); i++)
	{
		cout << " |     " << accounts[i].login  << "    |   ";

		if (accounts[i].access == 0)
		{
			cout << " ��� " << "|";
		}
		if (accounts[i].access == 1)
		{
			cout << " ����" << " |";
		}

		if (accounts[i].role == 0)
		{
			cout << " ������������ " << "|" << endl;
		}
		if (accounts[i].role == 1)
		{
			cout << "�������������" << " |" << endl;
		}
		cout << "  ----------------------------------- " << endl;
	}
}


void addAccount(vector<Account> &accounts)
{
	string password;
	Account* account = new Account;
	account->access = 1;
	account->salt = getSalt();

	cout << "������� �����: " << endl;
	cin >> account->login;
	cout << "������� ������: " << endl;
	password = transformPassword();
	account->hash_password = hashPassword(password, account->salt);
	cout << "������������(0) ��� �������������(1)? : ";
	account->role = getNumber();

	accounts.push_back(*account);
	writeToEndAccountFile(*account);
	cout << "������� ������� ��������!" << endl;
}


void editAccount(vector<Account>& accounts)
{
	int i;
	cout << "������� ����� ��������, ������� ������ ���������������: ";
	i = getNumber() - 1;

	if (i >= 0 && i < accounts.size())
	{
		editionMenu(accounts[i]);
		writeAccountFile(accounts);
		cout << "������� ������� ��������������!" << endl;
	}
	else cout << "������ �������� �� ����������." << endl;
}


void editionMenu(Account& account)
{
	string login, password;
	int item, role, access;

	while (true)
	{
		cout << "1. ��������������� ����� " << endl
			<< "2. ��������������� ������ " << endl
			<< "3. �������� ���� " << endl
			<< "4. �������� ������ " << endl
			<< "0. �����" << endl;
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			cout << "������� ����� �����: ";
			cin >> login;
			account.login = login;
			break;

		case 2:
			cout << "������� ����� ������: ";
			cin >> password;
			account.hash_password = hashPassword(password, account.salt);
			break;

		case 3:
			cout << "�������� ����: ";
			role = getNumber();
			account.role = role;
			break;

		case 4:
			cout << "�������� ������: ";
			access = getNumber();
			account.access = access;
			break;

		default:
			cout << "�������� ��� ���." << endl;
			break;
		}
	}
}


void deleteAccount(vector<Account>& accounts, Account current_account)
{
	int i;
	int item;
	cout << "������� ����� ��������, ������� ������ �������: ";
	i = getNumber() - 1;
	
	while (i >= 0 && i < accounts.size())
	{
		if (current_account.login == accounts[i].login)
		{
			cout << "��� ������� �� ����� ���� ������." << endl;
			break;
		}
		else {
			cout << "�� ����� ������ ������� �������?" << endl;
			cout << "1 - ��" << endl
				<< "2 - ���" << endl;
			cout << "������� ���� �����: ";
			item = getNumber();
			if (item == 1) {
				accounts.erase(accounts.begin() + i);
				writeAccountFile(accounts);
				cout << "������� ������� ������!" << endl;
				break;
			}
			else if (item == 2) {
				return;
			}
			else {
				cout << "������� ��� ���." << endl;
			}
		}
	}
	if (i > accounts.size()) {
		cout << "������ �������� �� ����������." << endl;
	}
}


string getSalt() {
	string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	string salt = "";
	for (int i = 0; i < SALT_LENGTH; ++i) {
		salt += alphabet[rand() % (sizeof(alphabet) - 1)];
	}

	return salt;
}


long long int hashPassword(string password, string salt)
{
	string password_with_salt = password + salt;
	const int p = 33;
	long long hash = 0, p_pow = 1;
	for (size_t i = 0; i < password_with_salt.length(); ++i)
	{
		hash = (hash + ((int)password_with_salt[i] - (int)'a' + 1) * p_pow) % LONG_MAX;
		p_pow *= p;
	}

	return hash;
}
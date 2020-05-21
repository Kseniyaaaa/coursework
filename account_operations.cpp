#include <string>
#include <fstream>
#include <iostream>

#include "account_operations.h"
#include "file_operations.h"
#include "validation.h"
#include "structures.h"

const string FILE_OF_ACCOUNTS = "accounts.txt";


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
	account->password = "admin";
	account->role = 1;
	account->access = 1;

	ofstream fout(FILE_OF_ACCOUNTS, ios::out);
	fout << account->login << " "
		<< account->password << " "
		<< account->role << " "
		<< account->access << endl;
	fout.close();
	return account;
}


void showAccount(vector<Account> accounts)
{
	cout << "  =================================== " << endl;
	cout << " | " << " Логин " << "  |"
		<< " Доступ " << " |" << "     Роль " << "    |" << endl;
	cout << "  =================================== " << endl;
	for (int i = 0; i < accounts.size(); i++)
	{
		cout << " |     " << accounts[i].login  << "    |   ";

		if (accounts[i].access == 0)
		{
			cout << " нет " << "|";
		}
		if (accounts[i].access == 1)
		{
			cout << " есть" << " |";
		}

		if (accounts[i].role == 0)
		{
			cout << " пользователь " << "|" << endl;
		}
		if (accounts[i].role == 1)
		{
			cout << "администратор" << " |" << endl;
		}
		cout << "  ----------------------------------- " << endl;
	}
}


void addAccount(vector<Account> &accounts)
{
	Account* account = new Account;
	account->access = 1;

	cout << "Введите логин: " << endl;
	cin >> account->login;
	cout << "Введите пароль: " << endl;
	cin >> account->password;
	cout << "Пользователь(0) или администратор(1)? : ";
	account->role = getNumber();

	accounts.push_back(*account);
	writeToEndAccountFile(*account);
}


void editAccount(vector<Account>& accounts)
{
	int i;
	cout << "Введите номер аккаунта, который хотите отредактировать: ";
	i = getNumber();

	if (i >= 0 && i < accounts.size())
	{
		editionMenu(accounts[i]);
		writeAccountFile(accounts);
	}
	else cout << "Такого акканута не существует." << endl;
}


void editionMenu(Account& account)
{
	string login, password;
	int item, role, access;

	while (true)
	{
		cout << "1. Отредактировать логин " << endl
			<< "2. Отредактировать пароль " << endl
			<< "3. Изменить роль " << endl
			<< "4. Изменить доступ " << endl
			<< "0. ВЫХОД" << endl;
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			cout << "Введите новый логин: ";
			cin >> login;
			account.login = login;
			break;

		case 2:
			cout << "Введите новый пароль: ";
			cin >> password;
			account.password = password;
			break;

		case 3:
			cout << "Измените роль: ";
			cin >> role;
			account.role = role;
			break;

		case 4:
			cout << "Измените доступ: ";
			cin >> access;
			account.access = access;
			break;

		default:
			cout << "Выберите еще раз." << endl;
			break;
		}
	}
}


void deleteAccount(vector<Account>& accounts, Account current_account)
{
	int i;
	cout << "Введите номер аккаунта, который хотите удалить: ";
	i = getNumber();
	
	if (i >= 0 && i < accounts.size())
	{
		if (current_account.login == accounts[i].login)
		{
			cout << "Ваш аккаунт не может быть удален." << endl;
		}
		else {
			accounts.erase(accounts.begin() + i);
			writeAccountFile(accounts);
		}
	}
	else cout << "Такого аккаунта не существует." << endl;
}
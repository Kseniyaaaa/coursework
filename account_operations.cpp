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
	string password;
	Account* account = new Account;
	account->access = 1;
	account->salt = getSalt();

	cout << "Введите логин: " << endl;
	cin >> account->login;
	cout << "Введите пароль: " << endl;
	password = transformPassword();
	account->hash_password = hashPassword(password, account->salt);
	cout << "Пользователь(0) или администратор(1)? : ";
	account->role = getNumber();

	accounts.push_back(*account);
	writeToEndAccountFile(*account);
	cout << "Аккаунт успешно добавлен!" << endl;
}


void editAccount(vector<Account>& accounts)
{
	int i;
	cout << "Введите номер аккаунта, который хотите отредактировать: ";
	i = getNumber() - 1;

	if (i >= 0 && i < accounts.size())
	{
		editionMenu(accounts[i]);
		writeAccountFile(accounts);
		cout << "Аккаунт успешно отредактирован!" << endl;
	}
	else cout << "Такого аккаунта не существует." << endl;
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
			account.hash_password = hashPassword(password, account.salt);
			break;

		case 3:
			cout << "Измените роль: ";
			role = getNumber();
			account.role = role;
			break;

		case 4:
			cout << "Измените доступ: ";
			access = getNumber();
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
	int item;
	cout << "Введите номер аккаунта, который хотите удалить: ";
	i = getNumber() - 1;
	
	while (i >= 0 && i < accounts.size())
	{
		if (current_account.login == accounts[i].login)
		{
			cout << "Ваш аккаунт не может быть удален." << endl;
			break;
		}
		else {
			cout << "Вы точно хотите удалить аккаунт?" << endl;
			cout << "1 - Да" << endl
				<< "2 - Нет" << endl;
			cout << "Введите свой ответ: ";
			item = getNumber();
			if (item == 1) {
				accounts.erase(accounts.begin() + i);
				writeAccountFile(accounts);
				cout << "Аккаунт успешно удален!" << endl;
				break;
			}
			else if (item == 2) {
				return;
			}
			else {
				cout << "Введите еще раз." << endl;
			}
		}
	}
	if (i > accounts.size()) {
		cout << "Такого аккаунта не существует." << endl;
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
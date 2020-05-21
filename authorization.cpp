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
	cout << "Авторизация: " << endl
		<< "1. Войти " << endl
		<< "2. Зарегистрироваться " << endl
		<< "0. ВЫХОД" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
}


void authorize(vector<Account>& accounts, vector<Participant>& records)
{
	int item;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Добро пожаловать!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
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
			cout << "Выберите еще раз" << endl;
			break;
		}
	}
}


void login(vector<Account> &accounts, vector<Participant>& records)
{
	string login, password;
	cout << "Введите логин: ";
	cin >> login;
	cout << "Введите пароль: ";
	password = transformPassword();

	Account* account = getAccount(accounts, login);

	if (account == NULL) {
		cout << "Такого пользователя не существует." << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		return;
	}
	else if (account->hash_password != hashPassword(password, account->salt)) {
		cout << "Проверьте введенный пароль." << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		return;
	}

	if (account->role == 1) {
		cout << "Вы администратор." << endl;
		cout << "Вход выполнен успешно." << endl;
		showAdminMenu(accounts, *account, records);
	}
	else {
		if (account->access == 0) {
			cout << "Вы не можете войти в аккаунт. Ожидайте подтверждения администратора." << endl;
			cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
			return;
		}
		else {
			cout << "Вы пользователь." << endl;
			cout << "Вход выполнен успешно." << endl;
			writeToEndAccountFile(*account);
			showUserMenu(records);
		}
	}
}


void registration(vector<Account> &accounts)
{
	string login, password, password2;
	cout << "Введите логин: " << endl;
	while (true) {
		cin >> login;
		Account* account = getAccount(accounts, login);
		if (account == NULL) {
			break;
		}
		else {
			cout << "Аккаунт с таким логином уже существует." << endl;
			cout << "Введите другой логин: " << endl;
		}
	}

	do {
		cout << "Введите пароль: ";
		password = transformPassword();
		cout << "Подтвердите пароль: ";
		password2 = transformPassword();
	} while (password != password2);

	Account* account = new Account;
	account->salt = getSalt();
	account->login = login;
	account->hash_password = hashPassword(password, account->salt);
	account->role = 0;
	account->access = 0;

	accounts.push_back(*account);
	writeToEndAccountFile(*account);
}


string transformPassword()
{
	string password;
	int ch = 0;
	while (true)
	{
		ch = _getwch();                                                                                // считывание нажатия клавиши

		if (ch == 13)                                                                                    // код Enter
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


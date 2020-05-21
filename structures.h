#pragma once

#include <string>

using namespace std;

struct Participant
{
	string name;
	int year;
	string country;
	string instrument;
	int place;
};


struct Account
{
	string login;
	int access;           // 0 - нет доступа, 1 - есть доступ
	int role;          // 0 - пользователь, 1 - администратор
	long long hash_password;
	string salt;
};
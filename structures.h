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
	int access;           // 0 - ��� �������, 1 - ���� ������
	int role;          // 0 - ������������, 1 - �������������
	long long hash_password;
	string salt;
};
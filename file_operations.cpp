#include "account_operations.h"
#include "file_operations.h"
#include "structures.h"

#include <iostream>
#include <fstream>

using namespace std;

const string FILE_OF_ACCOUNTS = "accounts.txt";
const string FILE_OF_RECORDS = "records.txt";

vector<Account> readAccountsFile()
{
	vector<Account> accounts;

	ifstream fin(FILE_OF_ACCOUNTS, ios::in);
	if (!fin.is_open()) {
		accounts.push_back(*createFirstAdmin());
	}
	else
	{
		while (!fin.eof())
		{
			Account* account = new Account;
			fin >> account->login
				>> account->hash_password
				>> account->salt
				>> account->role
				>> account->access;
			accounts.push_back(*account);
		}
	}
	fin.close();
	return accounts;
}


void writeAccountFile(vector<Account> accounts)
{
	ofstream fout(FILE_OF_ACCOUNTS, ios::out);
	for (int i = 0; i < accounts.size(); i++)
	{
		fout << accounts[i].login << " "
			<< accounts[i].hash_password << " "
			<< accounts[i].salt << " "
			<< accounts[i].role << " "
			<< accounts[i].access;
		if (i < accounts.size() - 1)
		{
			fout << endl;
		}
	}
	fout.close();
}


void writeToEndAccountFile(Account account)
{
	ofstream fadd(FILE_OF_ACCOUNTS, ios::app);
	fadd << account.login << " "
		<< account.hash_password << " "
		<< account.salt << " "
		<< account.role << " "
		<< account.access << endl;
	fadd.close();
}


vector<Participant> readRecordsFile()
{
	vector<Participant> records;

	ifstream fin(FILE_OF_RECORDS, ios::in);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			Participant* record = new Participant;
			getline(fin, record->name);
			getline(fin, record->country);
			fin >> record->year;
			fin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			getline(fin, record->instrument);
			fin >> record->place;
			fin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			records.push_back(*record);
		}
	}
	fin.close();
	return records;
}


void writeRecordFile(vector<Participant> records)
{
	ofstream fout(FILE_OF_RECORDS, ios::out);
	for (int i = 0; i < records.size(); i++)
	{
		fout << records[i].name << endl;
		fout << records[i].country << endl;
		fout << records[i].year << endl;
		fout << records[i].instrument << endl;
		fout << records[i].place;
		if (i < records.size() - 1)
		{
			fout << endl;
		}
	}
	fout.close();
}


void writeToEndRecordsFile(Participant record)
{
	ofstream fadd(FILE_OF_RECORDS, ios::app);
	fadd << record.name << " "
		<< record.country << " "
		<< record.year << " "
		<< record.instrument << " "
		<< record.place;
	fadd.close();
}


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <map>

#include "data_operations.h"
#include "account_operations.h"
#include "validation.h"
#include "file_operations.h"
#include "structures.h"

using namespace std;

void showData(vector<Participant> records)
{
	showHeader();
	for (int i = 0; i < records.size(); i++)
	{
		showRecord(records[i]);
	}
}

void showRecord(Participant record)
{
	cout << " |    " << record.name << "     |    "
		<< record.country << "    |    " << record.year << "     |       "
		<< record.instrument << "       |    " << record.place << "    |" << endl;
		cout << "  ---------------------------------------------------------------------------------------------- " << endl;
}


void showHeader()
{
	cout << "  ============================================================================================== " << endl;
	cout << " |        " << "      ���     " << "        | "
		<< "    ������   " << " | " << "   ���   " << "  |"
		<< "     ���������� " << "    |" << "  ����� " << " |" << endl;
	cout << "  ============================================================================================== " << endl;
}


void addRecord(vector<Participant>& records)
{
	Participant* record = new Participant;

	cout << "������� ��� ���������: ";
	getline(cin, record->name);
	cout << "������� ������, ������� �� ������������: ";
	getline(cin, record->country);

	cout << "������� ���/� ��� ��������: ";
	while (true) {
		record->year = getNumber();
		if (record->year < getCurrentYear()) {
			break;
		}
		else {
			cout << "������� ���������� ��� �������� (<" << getCurrentYear() << "): ";
		}
	}

	cout << "������� ����������, �� ������� �� ������: ";
	getline(cin, record->instrument);
	cout << "������� ������� ��/�� �����: ";
	record->place = getNumber();
	cout << endl;

	records.push_back(*record);
	writeToEndRecordsFile(*record);
	cout << "������ ������� ���������!" << endl;
}


void editData(vector<Participant>& records)
{
	int i;
	cout << "������� ����� ������, ������� ������ ���������������: ";
	i = getNumber() - 1;

	if (i >= 0 && i < records.size())
	{
		editionMenu(records[i]);
		writeRecordFile(records);
		cout << "������ ������� ���������������!" << endl;
	}
	else cout << "����� ������ �� ����������." << endl;
}


void editionMenu(Participant& record)
{
	string name, country, instrument;
	int item, year, place;

	while (true)
	{
		cout << "1. �������� ��� " << endl
			<< "2. �������� ������ " << endl
			<< "3. �������� ��� �������� " << endl
			<< "4. �������� ���������� " << endl
			<< "5. �������� ������� ����� " << endl
			<< "0. �����" << endl;
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			cout << "������� ���: " << endl;
			record.name = name;
			getline(cin, record.name);
			break;

		case 2:
			cout << "������� ������: ";
			cin >> country;
			record.country = country;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, record.country);
			break;

		case 3:
			cout << "�������� ��� ��������: ";
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			while (true) {
				year = getNumber();
				if (year < getCurrentYear()) {
					break;
				}
				else {
					cout << "������� ���������� ��� �������� (<" << getCurrentYear() << "): ";
				}
			}
			record.year = year;
			break;

		case 4:
			cout << "�������� ����������: ";
			cin >> instrument;
			record.instrument = instrument;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, record.instrument);
			break;

		case 5:
			cout << "�������� ������� �����: ";
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			place = getNumber();
			record.place = place;
			break;

		default:
			cout << "�������� ��� ���." << endl;
			break;
		}
	}
}


void deleteRecord(vector<Participant>& records)
{
	int i;
	int item;
	cout << "������� ����� ������, ������� ������ �������: ";
	i = getNumber() - 1;

	while (i >= 0 && i < records.size())
	{
		cout << "�� ����� ������ ������� ������?" << endl;
		cout << "1 - ��" << endl
			<< "2 - ���" << endl;
		cout << "������� ���� �����: ";
		item = getNumber();
		if (item == 1) {
			records.erase(records.begin() + i);
			writeRecordFile(records);
			cout << "������ ������� �������!" << endl;
			break;
		}
		else if (item == 2) {
			return;
		}
		else {
			cout << "������� ��� ���." << endl;
		}
	}
	if (i > records.size()) {
		cout << "����� ������ �� ����������." << endl;
	}
}


void showFindingMenu(vector<Participant>& records)
{
	int item;

	while (true)
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1 - ����� �� ����� " << endl
			<< "2 - ����� �� ���� �������� " << endl
			<< "3 - ����� �� �������� ����� " << endl
			<< "0 - �����" << endl;
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			findRecordByName(records);
			break;

		case 2:
			findRecordByYear(records);
			break;

		case 3:
			findRecordByPlace(records);
			break;

		default:
			cout << "�������� ��� ���" << endl;
			break;
		}
	}
}


void findRecordByName(vector<Participant>& records)
{
	int i;
	string name;
	cout << "������� ��� �������� ���������: ";
	getline(cin, name);
	bool flag = false;

	for (i = 0; i < records.size(); i++)
	{
		if (!flag) {
			showHeader();
		}
		if (records[i].name.find(name) != string::npos)
		{
			showRecord(records[i]);
			flag = true;
		}
	}
	if (!flag) {
		cout << "������ ��������� ���." << endl;
	}
}


void findRecordByYear(vector<Participant>& records)
{
	int i, year;
	cout << "������� ��� �������� �������� ���������: ";
	year = getNumber();
	bool flag = false;

	for (i = 0; i < records.size(); i++)
	{
		if (!flag) {
			showHeader();
		}
		if (year == records[i].year)
		{
			showRecord(records[i]);
			flag = true;
		}
	}
	if (!flag) {
		cout << "������ ��������� ���." << endl;
	}
}


void findRecordByPlace(vector<Participant>& records)
{
	int i, place;
	cout << "������� ������� ������� ���������� �����: ";
	place = getNumber();
	bool flag = false;

	for (i = 0; i < records.size(); i++)
	{
		if (!flag) {
			showHeader();
		}
		if (place == records[i].place)
		{
			showRecord(records[i]);
			flag = true;
		}
	}
	if (!flag) {
		cout << "������ ��������� ���." << endl;
	}
}


void showSortingMenu(vector<Participant>& records)
{
	int item;

	while (true)
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1 - ������������� �� ����� " << endl
			<< "2 - ������������� �� ���� �������� " << endl
			<< "3 - ������������� �� �������� ����� " << endl
			<< "0 - �����" << endl;
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			sortRecordsByName(records);
			showData(records);
			break;

		case 2:
			sortRecordsByYear(records);
			showData(records);
			break;

		case 3:
			sortRecordsByPlace(records);
			showData(records);
			break;

		default:
			cout << "�������� ��� ���" << endl;
			break;
		}
	}
}


void sortRecordsByName(vector<Participant>& records)
{
	sort(records.begin(), records.end(), sortByName);
}

bool sortByName(Participant participant_a, Participant participant_b)
{
	return participant_a.name < participant_b.name;
}


void sortRecordsByYear(vector<Participant>& records)
{
	sort(records.begin(), records.end(), sortByYear); 
}

bool sortByYear(Participant participant_a, Participant participant_b)
{
	return participant_a.year < participant_b.year;
}

bool sortByYearDesc(Participant participant_a, Participant participant_b)
{
	return participant_a.year > participant_b.year;
}


void sortRecordsByPlace(vector<Participant>& records)
{
	sort(records.begin(), records.end(), sortByPlace);
}

bool sortByPlace(Participant participant_a, Participant participant_b)
{
	return participant_a.place < participant_b.place;
}


void Task(vector<Participant>& records)
{
	// �� ������� ������ ����������� ������������ ������� ������ ������ ���� ���� � ��������� �������� �����������
	Task1(records);

	// ���������� �� 12 ���
	Task2(records);
}


void Task1(vector<Participant>& records)
{
	map<string, vector<Participant>> list;
	for (int i = 0; i < records.size(); i++)
	{
		map <string, vector<Participant>> ::iterator it = list.find(records[i].instrument);

		if (it == list.end()) {
			vector<Participant> v;
			list[records[i].instrument] = v;
			list[records[i].instrument].push_back(records[i]);
		}
		else {
			it->second.push_back(records[i]);
		}
	}

	for (map <string, vector<Participant>> ::iterator it = list.begin(); it != list.end(); it++)
	{
		cout << it->first << endl;
		sortRecordsByPlace(it->second);
		showHeader();
		for (int i = 0; i < it->second.size(); i++)
		{
			Participant p = it->second[i];
			cout << endl;
			cout << " |    " << p.name << "     |    "
				<< p.country << "   |" << p.year << "(" << getCurrentYear() - p.year << " ���/���/�)" << "|       "
				<< p.instrument << "       |    " << p.place << "    |" << endl;
			cout << "  ---------------------------------------------------------------------------------------------- " << endl;
		}
		cout << endl;
	}
}


void Task2(vector<Participant>& records)
{
	bool flag = false;

	sort(records.begin(), records.end(), sortByYearDesc);
	cout << "��� ���������� �� 12 ���: " << endl;
	for (int i = 0; i < records.size(); i++)
	{
		if (records[i].year >= getCurrentYear() - 12) {
			if (!flag) {
				showHeader();
			}
			cout << endl;
			Participant p = records[i];
			cout << " |    " << p.name << "     |    "
				<< p.country << "   |" << p.year << "(" << getCurrentYear() - p.year << " ���/���/�)" << "|       "
				<< p.instrument << "       |    " << p.place << "    |" << endl;
			cout << "  ---------------------------------------------------------------------------------------------- " << endl;
			flag = true;
		}
	}
	if (!flag) {
		cout << "����� ���������� ���." << endl;
	}
}


void deleteData(vector<Participant>& records)
{
	int item;
	cout << "�� ����� ������ �������� ��� ������?" << endl;
		cout << "1 - ��" << endl
			<< "2 - ���" << endl;
		cout << "������� ���� �����: ";
	item = getNumber();
	if (item == 1) {
		records.clear();
		writeRecordFile(records);
		cout << "������ ������� �������!" << endl;
	}
	else if (item == 2) {
		return;
	}
	else {
		cout << "������� ��� ���." << endl;
	}
}


int getCurrentYear()
{
	struct tm localtime;
	time_t now = time(NULL);
	localtime_s(&localtime, &now);

	return 1900 + localtime.tm_year;
}
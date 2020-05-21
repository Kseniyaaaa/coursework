#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <time.h>

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
	cout << " |        " << "      ФИО     " << "        | "
		<< "    Страна   " << " | " << "   Год   " << "  |"
		<< "     Инструмент " << "    |" << "  Место " << " |" << endl;
	cout << "  ============================================================================================== " << endl;
}


void addRecord(vector<Participant>& records)
{
	Participant* record = new Participant;

	cout << "Введите ФИО участника: ";
	getline(cin, record->name);
	cout << "Введите страну, которую он представляет: ";
	getline(cin, record->country);
	cout << "Введите его/её год рождения: ";
	record->year = getNumber();
	cout << "Введите инструмент, на котором он играет: ";
	getline(cin, record->instrument);
	cout << "Введите занятое им/ей место: ";
	record->place = getNumber();
	cout << endl;

	records.push_back(*record);
	writeToEndRecordsFile(*record);
}


void editData(vector<Participant>& records)
{
	int i;
	cout << "Введите номер записи, которую хотите отредактировать: ";
	i = getNumber();

	if (i >= 0 && i < records.size())
	{
		editionMenu(records[i]);
		writeRecordFile(records);
	}
	else cout << "Такой записи не существует." << endl;
}


void editionMenu(Participant& record)
{
	string name, country, instrument;
	int item, year, place;

	while (true)
	{
		cout << "1. Изменить ФИО " << endl
			<< "2. Изменить страну " << endl
			<< "3. Изменить год рождения " << endl
			<< "4. Изменить инструмент " << endl
			<< "5. Изменить занятое место " << endl
			<< "0. ВЫХОД" << endl;
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			cout << "Введите ФИО: " << endl;
			record.name = name;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, record.name);
			break;

		case 2:
			cout << "Введите страну: ";
			cin >> country;
			record.country = country;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, record.country);
			break;

		case 3:
			cout << "Измените год рождения: ";
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			year = getNumber();
			record.year = year;
			break;

		case 4:
			cout << "Измените инструмент: ";
			cin >> instrument;
			record.instrument = instrument;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, record.instrument);
			break;

		case 5:
			cout << "Измените занятое место: ";
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			place = getNumber();
			record.place = place;
			break;

		default:
			cout << "Выберите еще раз." << endl;
			break;
		}
	}
}


void deleteRecord(vector<Participant>& records)
{
	int i;
	cout << "Введите номер записи, который хотите удалить: ";
	i = getNumber();

	if (i >= 0 && i < records.size())
	{
		records.erase(records.begin() + i);
		writeRecordFile(records);
	}
	else cout << "Такой записи не существует." << endl;
}


void showFindingMenu(vector<Participant>& records)
{
	int item;

	while (true)
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1 - Найти по имени " << endl
			<< "2 - Найти по году рождения " << endl
			<< "3 - Найти по занятому месту " << endl
			<< "0 - ВЫХОД" << endl;
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
			cout << "Выберите еще раз" << endl;
			break;
		}
	}
}


void findRecordByName(vector<Participant>& records)
{
	int i;
	string name;
	cout << "Введите ФИО искомого участника: ";
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, name);
	bool flag = false;

	for (i = 0; i < records.size(); i++)
	{
		if (records[i].name.find(name) != string::npos)
		{
			showHeader();
			showRecord(records[i]);
			flag = true;
		}
	}
	if (!flag) {
		cout << "Такого участника нет." << endl;
	}
}


void findRecordByYear(vector<Participant>& records)
{
	int i, year;
	cout << "Введите год рождения искомого участника: ";
	year = getNumber();
	bool flag = false;

	for (i = 0; i < records.size(); i++)
	{
		if (year == records[i].year)
		{
			showHeader();
			showRecord(records[i]);
			flag = true;
		}
	}
	if (!flag) {
		cout << "Такого участника нет." << endl;
	}
}


void findRecordByPlace(vector<Participant>& records)
{
	int i, place;
	cout << "Введите занятое искомым участником место: ";
	place = getNumber();
	bool flag = false;

	for (i = 0; i < records.size(); i++)
	{
		if (place == records[i].place)
		{
			showHeader();
			showRecord(records[i]);
			flag = true;
		}
	}
	if (!flag) {
		cout << "Такого участника нет." << endl;
	}
}


void showSortingMenu(vector<Participant>& records)
{
	int item;

	while (true)
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1 - Отсортировать по имени " << endl
			<< "2 - Отсортировать по году рождения " << endl
			<< "3 - Отсортировать по занятому месту " << endl
			<< "0 - ВЫХОД" << endl;
		item = getNumber();
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			sortRecordsByName(records);
			break;

		case 2:
			sortRecordsByYear(records);
			break;

		case 3:
			sortRecordsByPlace(records);
			break;

		default:
			cout << "Выберите еще раз" << endl;
			break;
		}
	}
}


void sortRecordsByName(vector<Participant>& records)
{
	sort(records.begin(), records.end(), SortByName);
	showHeader();
	for (int i = 0; i < records.size(); i++)
	{
		showRecord(records[i]);
	}
}

bool SortByName(Participant participant_a, Participant participant_b)
{
	return participant_a.name < participant_b.name;
}


void sortRecordsByYear(vector<Participant>& records)
{
	sort(records.begin(), records.end(), SortByYear); 
	showHeader();
	for (int i = 0; i < records.size(); i++)
	{
		showRecord(records[i]);
	}
}

bool SortByYear(Participant participant_a, Participant participant_b)
{
	return participant_a.year < participant_b.year;
}


void sortRecordsByPlace(vector<Participant>& records)
{
	sort(records.begin(), records.end(), SortByPlace);
	showHeader();
	for (int i = 0; i < records.size(); i++)
	{
		showRecord(records[i]);
	}
}

bool SortByPlace(Participant participant_a, Participant participant_b)
{
	return participant_a.place < participant_b.place;
}


void Task(vector<Participant>& records)
{
	// По каждому классу музыкальных инструментов вывести список первых трех мест с указанием возраста победителей
	/*for (int i = 0; i < records.size(); i++)
	{
		cout << records[i].year - getCurrentYear() << " лет" << endl;
	}*/

	// Победители до 12 лет
	bool flag = false;

	//sortRecordsByYear(records);
	for (int i = 0; i < records.size(); i++)
	{
		if (records[i].year >= 2008) {
			cout << "Все победители до 12 лет: " << endl;
			cout << endl;
			showHeader();
			sortRecordsByYear(records);
			cout << " |    " << records[i].name << "     |    "
				<< records[i].country << "    |    " << records[i].year << "     |       "
				<< records[i].instrument << "       |    " << records[i].place << "    |" << endl;
			cout << "  ---------------------------------------------------------------------------------------------- " << endl;
			flag = true;
		}
		else {
			break;
		}
	}
	if (!flag) {
		cout << "Такого участника нет." << endl;
	}
}


void deleteData(vector<Participant>& records)
{
	records.clear();
	writeRecordFile(records);
}


//int getCurrentYear()
//{
//	struct tm localtime;
//	time_t now = time(NULL);
//	localtime_s(&localtime, &now);
//
//	return 1900 + localtime.tm_year; // tm_year: years since 1900
//}
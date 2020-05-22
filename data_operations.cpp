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
	while (true) {
		record->year = getNumber();
		if (record->year < getCurrentYear()) {
			break;
		}
		else {
			cout << "Введите правильный год рождения (<" << getCurrentYear() << "): ";
		}
	}

	cout << "Введите инструмент, на котором он играет: ";
	getline(cin, record->instrument);
	cout << "Введите занятое им/ей место: ";
	record->place = getNumber();
	cout << endl;

	records.push_back(*record);
	writeToEndRecordsFile(*record);
	cout << "Запись успешно добавлена!" << endl;
}


void editData(vector<Participant>& records)
{
	int i;
	cout << "Введите номер записи, которую хотите отредактировать: ";
	i = getNumber() - 1;

	if (i >= 0 && i < records.size())
	{
		editionMenu(records[i]);
		writeRecordFile(records);
		cout << "Запись успешно отредактирована!" << endl;
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
			while (true) {
				year = getNumber();
				if (year < getCurrentYear()) {
					break;
				}
				else {
					cout << "Введите правильный год рождения (<" << getCurrentYear() << "): ";
				}
			}
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
	int item;
	cout << "Введите номер записи, который хотите удалить: ";
	i = getNumber() - 1;

	while (i >= 0 && i < records.size())
	{
		cout << "Вы точно хотите удалить запись?" << endl;
		cout << "1 - Да" << endl
			<< "2 - Нет" << endl;
		cout << "Введите свой ответ: ";
		item = getNumber();
		if (item == 1) {
			records.erase(records.begin() + i);
			writeRecordFile(records);
			cout << "Запись успешно удалена!" << endl;
			break;
		}
		else if (item == 2) {
			return;
		}
		else {
			cout << "Введите еще раз." << endl;
		}
	}
	if (i > records.size()) {
		cout << "Такой записи не существует." << endl;
	}
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
			cout << "Выберите еще раз" << endl;
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
	// По каждому классу музыкальных инструментов вывести список первых трех мест с указанием возраста победителей
	Task1(records);

	// Победители до 12 лет
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
				<< p.country << "   |" << p.year << "(" << getCurrentYear() - p.year << " лет/год/а)" << "|       "
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
	cout << "Все победители до 12 лет: " << endl;
	for (int i = 0; i < records.size(); i++)
	{
		if (records[i].year >= getCurrentYear() - 12) {
			if (!flag) {
				showHeader();
			}
			cout << endl;
			Participant p = records[i];
			cout << " |    " << p.name << "     |    "
				<< p.country << "   |" << p.year << "(" << getCurrentYear() - p.year << " лет/год/а)" << "|       "
				<< p.instrument << "       |    " << p.place << "    |" << endl;
			cout << "  ---------------------------------------------------------------------------------------------- " << endl;
			flag = true;
		}
	}
	if (!flag) {
		cout << "Таких участников нет." << endl;
	}
}


void deleteData(vector<Participant>& records)
{
	int item;
	cout << "Вы точно хотите очистить все данные?" << endl;
		cout << "1 - Да" << endl
			<< "2 - Нет" << endl;
		cout << "Введите свой ответ: ";
	item = getNumber();
	if (item == 1) {
		records.clear();
		writeRecordFile(records);
		cout << "Данные успешно удалены!" << endl;
	}
	else if (item == 2) {
		return;
	}
	else {
		cout << "Введите еще раз." << endl;
	}
}


int getCurrentYear()
{
	struct tm localtime;
	time_t now = time(NULL);
	localtime_s(&localtime, &now);

	return 1900 + localtime.tm_year;
}
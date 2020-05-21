#pragma once

#include "account_operations.h"
#include "structures.h"
#include <vector>

void showData(vector<Participant> records);
void showRecord(Participant record);
void showHeader();
void addRecord(vector<Participant>& records);
void editData(vector<Participant>& records);
void editionMenu(Participant& record);
void deleteRecord(vector<Participant>& records);

void showFindingMenu(vector<Participant>& records);
void findRecordByName(vector<Participant>& records);
void findRecordByYear(vector<Participant>& records);
void findRecordByPlace(vector<Participant>& records);

void showSortingMenu(vector<Participant>& records);
void sortRecordsByName(vector<Participant>& records);
bool sortByName(Participant participant_a, Participant participant_b);
void sortRecordsByYear(vector<Participant>& records);
bool sortByYear(Participant participant_a, Participant participant_b);
bool sortByYearDesc(Participant participant_a, Participant participant_b);
void sortRecordsByPlace(vector<Participant>& records);
bool sortByPlace(Participant participant_a, Participant participant_b);

void Task(vector<Participant>& records);
void Task1(vector<Participant>& records);
void Task2(vector<Participant>& records);

void deleteData(vector<Participant>& records);

int getCurrentYear();

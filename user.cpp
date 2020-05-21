#include "data_operations.h"
#include "user.h"
#include "structures.h"

#include <iostream>

using namespace std;

void showUserMenu(vector<Participant> records)
{
	int item;
	while (true)
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1. Просмотреть данные о конкурсе" << endl
			<< "2. Найти участника конкурса" << endl
			<< "3. Отсортировать данные " << endl
			<< "4. Выполнить инд задание " << endl
			<< "0. ВЫХОД" << endl;
		cin >> item;
		cout << endl;

		switch (item)
		{
		case 0:
			return;

		case 1:
			showData(records);
			break;

		case 2:
			showFindingMenu(records);
			break;

		case 3:
			showSortingMenu(records);
			break;

		case 4:
			Task(records);
			break;

		default:
			cout << "Выберите еще раз" << endl;
			break;
		}
	}
}

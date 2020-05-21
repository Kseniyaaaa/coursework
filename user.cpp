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
		cout << "1. ����������� ������ � ��������" << endl
			<< "2. ����� ��������� ��������" << endl
			<< "3. ������������� ������ " << endl
			<< "4. ��������� ��� ������� " << endl
			<< "0. �����" << endl;
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
			cout << "�������� ��� ���" << endl;
			break;
		}
	}
}

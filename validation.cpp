#include "validation.h"

#include <iostream>

using namespace std;

bool isNumberNumeric()
{
	if (cin.get() == '\n') return true;
	else
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
}

int getNumber()
{
	int item;
	while (true)
	{
		cin >> item;
		if (isNumberNumeric() && item >= 0)
		{
			break;
		}
		else if (item < 0) {
			cout << "������� ������������� �����: ";
		}
		else
		{
			cout << "������������ ���� ������!" << endl;
			cout << "������� �������� ������: ";
		}
	}
	
	return item;
}
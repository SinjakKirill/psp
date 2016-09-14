// checkip.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

int main()
{
	string ip;
	string mask = "255.255.255.255";
	
	int IntMask[4];
	convertMaskIP(mask, IntMask);
	for (int i = 0; i < 4; i++)
	{
		cout << IntMask[i] << " ";
	}
	cout << endl << "Number One:" << quantityHosts(IntMask) << endl;
	cout << endl;
	if (checkMask(IntMask))
		cout << "correct!";
	else
		cout << "incorrect!";
	_getch();
    return 0;
}


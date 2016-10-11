// checkip.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

int main()
{
	string ip = "0.0.0.1";
	string mask = "255.255.255.0";
	
	int IntMask[4];
	int IntIp[4];
	convertMaskIP(mask, IntMask);
	convertMaskIP(ip, IntIp);

	if (checkIp(ip) && checkMask(IntMask)) {
		cout << "\n\n\t\tIP ADRESS:\t";
		for (int i = 0; i < 4; i++)
			cout << IntIp[i] << ".";
		cout << "\n\n\t\tMask:     \t";
		for (int i = 0; i < 4; i++)
			cout << IntMask[i] << ".";
		cout << "\n\n\t\tClass IP: \t" << classIp(IntIp);
		cout << "\n\n\t\tNumber HOSTS:\t" << quantityHosts(IntMask);
	}
	else {
		cout << "\n\n\t\tincorrekt mask or ip!\n\n";
	}

	_getch();
    return 0;
}


// checkip.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <regex>
#include <string>


using namespace std;

string ip;
regex regIp("^(25[0-5]|2[0-4][0-9]|[0-1][0-9]{2}|[0-9]{2}|[0-9])(\.(25[0-5]|2[0-4][0-9]|[0-1][0-9]{2}|[0-9]{2}|[0-9])){3}$");
regex regMask("");

int main()
{
	cout << "Enter ip addres:\t";
	cin >> ip;
	if (regex_match(ip, regIp))
		cout << "\t Ip correct!" << endl;
	else cout << "\ Ip incorrect!"<< endl;
	_getch();
    return 0;
}


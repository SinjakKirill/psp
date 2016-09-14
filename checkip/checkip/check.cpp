#include "stdafx.h"
#include "check.h"
#include <regex>

bool checkIp(std::string ip)
{
	std::regex ipRegex("^(25[0-5]|2[0-4][0-9]|[0-1][0-9]{2}|[0-9]{2}|[0-9])(\.(25[0-5]|2[0-4][0-9]|[0-1][0-9]{2}|[0-9]{2}|[0-9])){3}$");
	//std::regex ipRegex("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");
	return std::regex_match(ip, ipRegex) ? true : false;
}

bool checkMask(int * mask)
{
	unsigned long maskBit;
	maskBit = mask[0];
	for (int i(1); i < 4; i++) {
		maskBit <<= 8;
		maskBit = maskBit + mask[i];
	}
	maskBit = ~maskBit;
	//cout << maskBit << "******";
	int checkNumber;
	bool point(true);
	while (point) {
		checkNumber = 1;
		checkNumber = checkNumber & maskBit;
		//cout << checkNumber << ".....";
		if (checkNumber == 1) {
			maskBit >>= 1;
		}
		else {
			point = false;
			break;
		}
	}
	//cout << maskBit << "!!!!!";

	return maskBit == 0 ? true : false;

	//std::regex maskRegex("/^(([12]?[0-9]{1,2}|2[0-4][0-9]|25[0-5])(\.|\/)){4}([1-2]?[0-9]|3[0-2])$/");
	//return std::regex_match(mask, maskRegex) ? true : false;
}

int quantityHosts(int * mask)
{
	unsigned long t;
	t = mask[0];
	for (int i(1); i < 4; i++) {
		t = t << 8;
		t = t + mask[i];
	}
	t = ~t;
	int quantity(0);
	while (t != 0) {
		quantity++;
		t = t >> 1;
	}
	return quantity;
}

void convertMaskIP(std::string mask, int * maskInt)
{
	char Tetrada[3];
	int number = 0;
	int tickTetrad = 0;
	for (int i(0); i < mask.length(); i++) {
		if (mask[i] != '.')
		{
			Tetrada[number] = mask[i];
			number++;
		}
		if (mask[i] == '.' || mask[i + 1] == '\0')
		{
			maskInt[tickTetrad] = atoi(Tetrada);
			tickTetrad++;
			number = 0;
			for (int j(0); j < 3; j++)
			{
				Tetrada[j] = '\0';
			}
		}
	}

}

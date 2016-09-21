#include "stdafx.h"
#include "check.h"
#include <regex>

bool checkIp(std::string ip)
{
	std::regex ipRegex("^(25[0-5]|2[0-4][0-9]|[0-1][0-9]{2}|[0-9]{2}|[0-9])(\.(25[0-5]|2[0-4][0-9]|[0-1][0-9]{2}|[0-9]{2}|[0-9])){3}$");
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
	int checkNumber;
	bool point(true);
	while (point) {
		checkNumber = 1;
		checkNumber = checkNumber & maskBit;
		if (checkNumber == 1) {
			maskBit >>= 1;
		}
		else {
			point = false;
			break;
		}
	}
	return maskBit == 0 ? true : false;
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
	return pow(2, quantity) - 2;
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

std::string classIp(int * ipAddress)
{
	if (ipAddress[0] < 127) {
		return "A";
	}
	if (ipAddress[0] == 127) {
		return "localhost";
	}
	if (ipAddress[0] > 127 && ipAddress[0] < 192) {
		return "B";
	}
	if (ipAddress[0] > 191 && ipAddress[0] < 224) {
		return "C";
	}
	if (ipAddress[0] > 223 && ipAddress[0] < 240) {
		return "D";
	}
	if (ipAddress[0] > 239 && ipAddress[0] < 255) {
		return "E";
	}
	return std::string();
}

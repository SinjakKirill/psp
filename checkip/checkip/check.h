#pragma once
#include "stdafx.h"

bool checkIp(std::string ip);
bool checkMask(int * mask);
int quantityHosts(int * mask);
void convertMaskIP(std::string mask, int* maskInt);


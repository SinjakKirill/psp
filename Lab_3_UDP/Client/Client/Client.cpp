// ClientU.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "WinSock2.h"

#include <iostream>
#include <string>
#include <ctime>
#include <conio.h>

using namespace std;

#pragma comment(lib, "WS2_32.lib") 
#pragma warning(disable : 4996)

string  GetErrorMsgText(int code)
{
	string msgText;
	switch (code)                      // �������� ���� ��������  
	{
	case WSAEINTR: msgText = "������ ������� �������� ";         break;
	case WSAEACCES: msgText = "���������� ����������";        break;
	case WSAEFAULT: msgText = "��������� �����"; break;
	case WSAEINVAL: msgText = "������ � ��������� "; break;
	case WSAEMFILE: msgText = "������� ����� ������ �������"; break;
	case WSAEWOULDBLOCK: msgText = "������ �������� ����������"; break;
	case WSAEINPROGRESS: msgText = "�������� � �������� ��������"; break;
	case WSAEALREADY: msgText = "�������� ��� ����������� "; break;
	case WSAENOTSOCK: msgText = "����� ����� ����������� "; break;
	case WSAEDESTADDRREQ: msgText = "��������� ����� ������������ "; break;
	case WSAEMSGSIZE: msgText = "��������� ������� �������  "; break;
	case WSAEPROTOTYPE: msgText = "������������ ��� ��������� ��� ������ "; break;
	case WSAENOPROTOOPT: msgText = "������ � ����� ���������"; break;
	case WSAEPROTONOSUPPORT: msgText = "�������� �� �������������� "; break;
	case WSAESOCKTNOSUPPORT: msgText = "��� ������ �� �������������� "; break;
	case WSAEOPNOTSUPP: msgText = "�������� �� �������������� "; break;
	case WSAEPFNOSUPPORT: msgText = "��� ���������� �� �������������� "; break;
	case WSAEAFNOSUPPORT: msgText = "��� ������� �� �������������� ����������"; break;
	case WSAEADDRINUSE: msgText = "����� ��� ������������ "; break;
	case WSAEADDRNOTAVAIL: msgText = "����������� ����� �� ����� ���� �����������"; break;
	case WSAENETDOWN: msgText = "���� ��������� "; break;
	case WSAENETUNREACH: msgText = "���� �� ���������"; break;
	case WSAENETRESET: msgText = "���� ��������� ����������"; break;
	case WSAECONNABORTED: msgText = "����������� ����� ����� "; break;
	case WSAECONNRESET: msgText = "����� ������������� "; break;
	case WSAENOBUFS: msgText = "�� ������� ������ ��� �������"; break;
	case WSAEISCONN: msgText = "����� ��� ���������"; break;
	case WSAENOTCONN: msgText = "����� �� ���������"; break;
	case WSAESHUTDOWN: msgText = "������ ��������� send: ����� �������� ������"; break;
	case WSAETIMEDOUT: msgText = "���������� ���������� ��������  �������"; break;
	case WSAECONNREFUSED: msgText = "���������� ���������  "; break;
	case WSAEHOSTDOWN: msgText = "���� � ����������������� ���������"; break;
	case WSAEHOSTUNREACH: msgText = "��� �������� ��� ����� "; break;
	case WSAEPROCLIM: msgText = "������� ����� ��������� "; break;
	case WSASYSNOTREADY: msgText = "���� �� �������� "; break;
	case WSAVERNOTSUPPORTED: msgText = "������ ������ ���������� "; break;
	case WSANOTINITIALISED: msgText = "�� ��������� ������������� WS2_32.DLL"; break;
	case WSAEDISCON: msgText = "����������� ����������"; break;
	case WSATYPE_NOT_FOUND: msgText = "����� �� ������ "; break;
	case WSAHOST_NOT_FOUND: msgText = "���� �� ������"; break;
	case WSATRY_AGAIN: msgText = "������������������ ���� �� ������ "; break;
	case WSANO_RECOVERY: msgText = "��������������  ������ "; break;
	case WSANO_DATA: msgText = "��� ������ ������������ ���� "; break;
	case WSA_INVALID_HANDLE: msgText = "��������� ���������� �������  � �������   "; break;
	case WSA_INVALID_PARAMETER: msgText = "���� ��� ����� ���������� � �������   "; break;
	case WSA_IO_INCOMPLETE: msgText = "������ �����-������ �� � ���������� ���������"; break;
	case WSA_IO_PENDING: msgText = "�������� ���������� �����  "; break;
	case WSA_NOT_ENOUGH_MEMORY: msgText = "�� ���������� ������ "; break;
	case WSA_OPERATION_ABORTED: msgText = "�������� ���������� "; break;
	default:                msgText = "***ERROR***";      break;
	};
	return msgText;
};


string  SetErrorMsgText(string msgText, int code)
{
	return  msgText + GetErrorMsgText(code);
};


int main()
{
	setlocale(LC_ALL, "Russian");

	WSADATA wsadata;
	SOCKET sS;

	try {

		if (WSAStartup(MAKEWORD(2, 0), &wsadata) == SOCKET_ERROR)
			throw SetErrorMsgText("Startup: ", WSAGetLastError());

		if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("Socket: ", WSAGetLastError());

		SOCKADDR_IN to;
		to.sin_family = AF_INET;
		to.sin_port = htons(2000);
		to.sin_addr.s_addr = inet_addr("127.0.0.1");


		int lto = sizeof(to);


		char mbuf[100] = "",                    //����� ����� 
			ibuf[50],
			mbufNumber[50] = "",
			obuf[20] = "Hello";  //����� ������
		int count,
			lobuf = 0;                    //���������� ������������ ����

		cout << "���������� ������������ ���������: ";
		cin >> count;


		clock_t time;
		time = clock();

		char str[] = "Hello!";

		for (int i = 0; i < count; i++)
		{
			if (sendto(sS, str, sizeof(str), 0, (LPSOCKADDR)&to, sizeof(to)) == SOCKET_ERROR)
				throw SetErrorMsgText("Sendto: ", WSAGetLastError());

			if (recvfrom(sS, mbuf, sizeof(mbuf), 0, (LPSOCKADDR)&to, &lto) == SOCKET_ERROR)
				throw SetErrorMsgText("Recvfrom: ", WSAGetLastError());

			cout << "Port: " << to.sin_port << "\t" << mbuf << endl;
			time = clock() - time;
			cout << (double)time / CLOCKS_PER_SEC << "\n";
		}
		

		if (closesocket(sS) == SOCKET_ERROR)
			throw SetErrorMsgText("Close socket: ", WSAGetLastError());
		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup: ", WSAGetLastError());
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText;
	}

	_getch();
	return 0;
}




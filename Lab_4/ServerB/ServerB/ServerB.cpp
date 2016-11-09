// ServerB.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "iostream"
#include "string.h"
#include "locale"
#include "time.h"
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib")

using namespace std;

string GetErrorMsgText(int code)
{
	string msgText;

	switch (code)
	{
	case WSAEINTR:				 msgText = "������ ������� ��������\n";						  break;
	case WSAEACCES:				 msgText = "���������� ����������\n";						  break;
	case WSAEFAULT:				 msgText = "��������� �����\n";								  break;
	case WSAEINVAL:				 msgText = "������ � ���������\n";							  break;
	case WSAEMFILE:				 msgText = "������� ����� ������ �������\n";				  break;
	case WSAEWOULDBLOCK:		 msgText = "������ �������� ����������\n";					  break;
	case WSAEINPROGRESS:		 msgText = "�������� � �������� ��������\n";				  break;
	case WSAEALREADY: 			 msgText = "�������� ��� �����������\n";					  break;
	case WSAENOTSOCK:   		 msgText = "����� ����� �����������\n";						  break;
	case WSAEDESTADDRREQ:		 msgText = "��������� ����� ������������\n";				  break;
	case WSAEMSGSIZE:  			 msgText = "��������� ������� �������\n";				      break;
	case WSAEPROTOTYPE:			 msgText = "������������ ��� ��������� ��� ������\n";		  break;
	case WSAENOPROTOOPT:		 msgText = "������ � ����� ���������\n";					  break;
	case WSAEPROTONOSUPPORT:	 msgText = "�������� �� ��������������\n";					  break;
	case WSAESOCKTNOSUPPORT:	 msgText = "��� ������ �� ��������������\n";				  break;
	case WSAEOPNOTSUPP:			 msgText = "�������� �� ��������������\n";					  break;
	case WSAEPFNOSUPPORT:		 msgText = "��� ���������� �� ��������������\n";			  break;
	case WSAEAFNOSUPPORT:		 msgText = "��� ������� �� �������������� ����������\n";	  break;
	case WSAEADDRINUSE:			 msgText = "����� ��� ������������\n";						  break;
	case WSAEADDRNOTAVAIL:		 msgText = "����������� ����� �� ����� ���� �����������\n";	  break;
	case WSAENETDOWN:			 msgText = "���� ���������\n";								  break;
	case WSAENETUNREACH:		 msgText = "���� �� ���������\n";							  break;
	case WSAENETRESET:			 msgText = "���� ��������� ����������\n";					  break;
	case WSAECONNABORTED:		 msgText = "����������� ����� �����\n";						  break;
	case WSAECONNRESET:			 msgText = "����� �������������\n";							  break;
	case WSAENOBUFS:			 msgText = "�� ������� ������ ��� �������\n";				  break;
	case WSAEISCONN:			 msgText = "����� ��� ���������\n";							  break;
	case WSAENOTCONN:			 msgText = "����� �� ���������\n";							  break;
	case WSAESHUTDOWN:			 msgText = "������ ��������� send: ����� �������� ������\n";  break;
	case WSAETIMEDOUT:			 msgText = "���������� ���������� ��������  �������\n";		  break;
	case WSAECONNREFUSED:		 msgText = "���������� ���������\n";						  break;
	case WSAEHOSTDOWN:			 msgText = "���� � ����������������� ���������\n";			  break;
	case WSAEHOSTUNREACH:		 msgText = "��� �������� ��� �����\n";						  break;
	case WSAEPROCLIM:			 msgText = "������� ����� ���������\n";						  break;
	case WSASYSNOTREADY:		 msgText = "���� �� ��������\n";							  break;
	case WSAVERNOTSUPPORTED:	 msgText = "������ ������ ����������\n";					  break;
	case WSANOTINITIALISED:		 msgText = "�� ��������� ������������� WS2_32.DLL\n";		  break;
	case WSAEDISCON:			 msgText = "����������� ����������\n";						  break;
	case WSATYPE_NOT_FOUND:		 msgText = "����� �� ������\n";								  break;
	case WSAHOST_NOT_FOUND:		 msgText = "���� �� ������\n";								  break;
	case WSATRY_AGAIN:			 msgText = "������������������ ���� �� ������\n";			  break;
	case WSANO_RECOVERY:		 msgText = "�������������� ������\n";						  break;
	case WSANO_DATA:			 msgText = "��� ������ ������������ ����\n";				  break;
	case WSA_INVALID_HANDLE:	 msgText = "��������� ���������� �������  � �������\n";		  break;
	case WSA_INVALID_PARAMETER:	 msgText = "���� ��� ����� ���������� � �������\n";			  break;
	case WSA_IO_INCOMPLETE:		 msgText = "������ �����-������ �� � ���������� ���������\n"; break;
	case WSA_IO_PENDING:		 msgText = "�������� ���������� �����\n";					  break;
	case WSA_NOT_ENOUGH_MEMORY:	 msgText = "�� ���������� ������\n";						  break;
	case WSA_OPERATION_ABORTED:	 msgText = "�������� ����������\n";							  break;
	case WSAEINVALIDPROCTABLE:	 msgText = "��������� ������\n";							  break;
	case WSAEINVALIDPROVIDER:	 msgText = "������ � ������ �������\n";						  break;
	case WSAEPROVIDERFAILEDINIT: msgText = "���������� ���������������� ������\n";			  break;
	case WSASYSCALLFAILURE:		 msgText = "��������� ���������� ���������� ������\n";		  break;
	default:					 msgText = "Error\n";										  break;
	};
	return msgText;
}

string SetErrorMsgText(string msg, int code)
{
	string m = msg;
	m += GetErrorMsgText(code);
	return m;
}

bool getRequestFromClient(char* name, short port, struct sockaddr* from, int * flen)
{
	SOCKET bS;

	try
	{
		if ((bS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("GETSocket: ", WSAGetLastError());

		SOCKADDR_IN serv;
		serv.sin_family = AF_INET;
		serv.sin_addr.s_addr = INADDR_ANY;
		serv.sin_port = htons(port);

		if (bind(bS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
			throw SetErrorMsgText("GETBind: ", WSAGetLastError());

		char ibuf[10];
		if ((recvfrom(bS, ibuf, sizeof(ibuf), NULL, from, flen)) == WSAETIMEDOUT)
			throw SetErrorMsgText("GETRecvFrom: ", WSAGetLastError());

		closesocket(bS);

		//cout << endl << "Message: " << ibuf << endl;

		if (strcmp(name, ibuf) != 0)
			return false;
		else return true;

		//return true;
	}
	catch (string errorMsgText)
	{
		closesocket(bS);
		cout << endl << errorMsgText << endl;
		return false;
	}
}

bool putAnswerToClient(char* name, struct sockaddr* to, int* lto)
{
	SOCKET bS;

	try
	{
		if ((bS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("PUTSocket: ", WSAGetLastError());


		if ((sendto(bS, name, strlen(name) + 1, NULL, to, *lto)) == SOCKET_ERROR)
			throw SetErrorMsgText("PUTSendTo: ", WSAGetLastError());


		closesocket(bS);

		return true;
	}
	catch (string errorMsgText)
	{
		closesocket(bS);
		cout << endl << errorMsgText << endl;
		return false;
	}
}

bool checkFunction(char* name, short port, struct sockaddr* from, int * flen)
{
	SOCKET bS;

	try
	{
		if ((bS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("check_Socket: ", WSAGetLastError());

		int optval = 10000;
		if (setsockopt(bS, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
			throw SetErrorMsgText("check_SetSockOpt: ", WSAGetLastError());


		if ((sendto(bS, name, strlen(name) + 1, NULL, from, *flen)) == SOCKET_ERROR)
			throw SetErrorMsgText("check_SendTo:", WSAGetLastError());


		char buf[10];
		if (setsockopt(bS, SOL_SOCKET, SO_RCVTIMEO, (const char*)&optval, sizeof(int)) == SOCKET_ERROR)
			throw "Error: check_SetSockOpt";

		if ((recvfrom(bS, buf, sizeof(buf), NULL, from, flen)) == WSAETIMEDOUT)
			throw SetErrorMsgText("check_RecvFrom: ", WSAGetLastError());

		closesocket(bS);

		if (strcmp(name, buf) != 0)
			return false;
		else
			return true;
	}
	catch (string errorMsgText)
	{
		closesocket(bS);
		cout << endl << errorMsgText << endl;
		return false;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "Russian");
	cout << "\t\t\tServerB.\n";

	try
	{
		WSADATA wsaData;

		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup: ", WSAGetLastError());

		SOCKADDR_IN clnt;
		SOCKADDR_IN serv;

		serv.sin_port = htons(2000);
		serv.sin_family = AF_INET;
		serv.sin_addr.s_addr = INADDR_BROADCAST;

		int lc = sizeof(serv);

		/*if (checkFunction("Hello", 2000, (sockaddr*)&serv, &lc))
			cout << "Find server" << inet_ntoa(serv.sin_addr) << endl;
		else
			cout << "Servers not found" << endl;*/

		while (true)
		{
			lc = sizeof(clnt);
			if (getRequestFromClient("Hello", 2000, (sockaddr*)&clnt, &lc))
			{
				cout << "\nnew Client: " << inet_ntoa(clnt.sin_addr) << endl;
				if (!putAnswerToClient("Hello", (sockaddr*)&clnt, &lc))
					cout << "Error: putAnswerToClient" << endl;
				cout << "\n";
			}
			else
				cout << "Error (��������� ����, �� ������� �� ��� ������)\n";
		}

		WSACleanup();
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText << endl;
	}

	return 0;
}


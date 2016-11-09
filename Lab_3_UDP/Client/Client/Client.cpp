// ClientU.cpp: определяет точку входа для консольного приложения.
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
	switch (code)                      // проверка кода возврата  
	{
	case WSAEINTR: msgText = "Работа функции прервана ";         break;
	case WSAEACCES: msgText = "Разрешение отвергнуто";        break;
	case WSAEFAULT: msgText = "Ошибочный адрес"; break;
	case WSAEINVAL: msgText = "Ошибка в аргументе "; break;
	case WSAEMFILE: msgText = "Слишком много файлов открыто"; break;
	case WSAEWOULDBLOCK: msgText = "Ресурс временно недоступен"; break;
	case WSAEINPROGRESS: msgText = "Операция в процессе развития"; break;
	case WSAEALREADY: msgText = "Операция уже выполняется "; break;
	case WSAENOTSOCK: msgText = "Сокет задан неправильно "; break;
	case WSAEDESTADDRREQ: msgText = "Требуется адрес расположения "; break;
	case WSAEMSGSIZE: msgText = "Сообщение слишком длинное  "; break;
	case WSAEPROTOTYPE: msgText = "Неправильный тип протокола для сокета "; break;
	case WSAENOPROTOOPT: msgText = "Ошибка в опции протокола"; break;
	case WSAEPROTONOSUPPORT: msgText = "Протокол не поддерживается "; break;
	case WSAESOCKTNOSUPPORT: msgText = "Тип сокета не поддерживается "; break;
	case WSAEOPNOTSUPP: msgText = "Операция не поддерживается "; break;
	case WSAEPFNOSUPPORT: msgText = "Тип протоколов не поддерживается "; break;
	case WSAEAFNOSUPPORT: msgText = "Тип адресов не поддерживается протоколом"; break;
	case WSAEADDRINUSE: msgText = "Адрес уже используется "; break;
	case WSAEADDRNOTAVAIL: msgText = "Запрошенный адрес не может быть использован"; break;
	case WSAENETDOWN: msgText = "Сеть отключена "; break;
	case WSAENETUNREACH: msgText = "Сеть не достижима"; break;
	case WSAENETRESET: msgText = "Сеть разорвала соединение"; break;
	case WSAECONNABORTED: msgText = "Программный отказ связи "; break;
	case WSAECONNRESET: msgText = "Связь восстановлена "; break;
	case WSAENOBUFS: msgText = "Не хватает памяти для буферов"; break;
	case WSAEISCONN: msgText = "Сокет уже подключен"; break;
	case WSAENOTCONN: msgText = "Сокет не подключен"; break;
	case WSAESHUTDOWN: msgText = "Нельзя выполнить send: сокет завершил работу"; break;
	case WSAETIMEDOUT: msgText = "Закончился отведенный интервал  времени"; break;
	case WSAECONNREFUSED: msgText = "Соединение отклонено  "; break;
	case WSAEHOSTDOWN: msgText = "Хост в неработоспособном состоянии"; break;
	case WSAEHOSTUNREACH: msgText = "Нет маршрута для хоста "; break;
	case WSAEPROCLIM: msgText = "Слишком много процессов "; break;
	case WSASYSNOTREADY: msgText = "Сеть не доступна "; break;
	case WSAVERNOTSUPPORTED: msgText = "Данная версия недоступна "; break;
	case WSANOTINITIALISED: msgText = "Не выполнена инициализация WS2_32.DLL"; break;
	case WSAEDISCON: msgText = "Выполняется отключение"; break;
	case WSATYPE_NOT_FOUND: msgText = "Класс не найден "; break;
	case WSAHOST_NOT_FOUND: msgText = "Хост не найден"; break;
	case WSATRY_AGAIN: msgText = "Неавторизированный хост не найден "; break;
	case WSANO_RECOVERY: msgText = "Неопределенная  ошибка "; break;
	case WSANO_DATA: msgText = "Нет записи запрошенного типа "; break;
	case WSA_INVALID_HANDLE: msgText = "Указанный дескриптор события  с ошибкой   "; break;
	case WSA_INVALID_PARAMETER: msgText = "Один или более параметров с ошибкой   "; break;
	case WSA_IO_INCOMPLETE: msgText = "Объект ввода-вывода не в сигнальном состоянии"; break;
	case WSA_IO_PENDING: msgText = "Операция завершится позже  "; break;
	case WSA_NOT_ENOUGH_MEMORY: msgText = "Не достаточно памяти "; break;
	case WSA_OPERATION_ABORTED: msgText = "Операция отвергнута "; break;
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


		char mbuf[100] = "",                    //буфер ввода 
			ibuf[50],
			mbufNumber[50] = "",
			obuf[20] = "Hello";  //буфер вывода
		int count,
			lobuf = 0;                    //количество отправленных байт

		cout << "Количество передаваемых сообщений: ";
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




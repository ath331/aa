#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <process.h>
#include <iostream>

using namespace std;

const static int  BUF_SIZE = 100;
const static int NAME_SIZE = 20;

using namespace std;
unsigned WINAPI SendMsg(void * arg);
unsigned WINAPI RecvMsg(void * arg);
void ErrorHandling(const char * msg);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];
char username[NAME_SIZE]; //유저 이름을 유저에게 직접 받기위한 변수

int main(int argc, const char *argv[])
{
	WSADATA wsaData;
	SOCKET hSock;
	SOCKADDR_IN servAdr;
	HANDLE hSndThread, hRcvThread;

	if (argc != 3) {
		cout << "Usage : " << argv[0] << " <IP> <port>\n" << endl;
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");
	cout << "Please Your Name : ";
	cin >> username;
	sprintf_s(name, "[%s]", username);
	hSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr(argv[1]);
	servAdr.sin_port = htons(atoi(argv[2]));

	if (connect(hSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("connect() error");

	hSndThread =
		(HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&hSock, 0, NULL);
	hRcvThread =
		(HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&hSock, 0, NULL);

	WaitForSingleObject(hSndThread, INFINITE);
	WaitForSingleObject(hRcvThread, INFINITE);

	closesocket(hSock);
	WSACleanup();
	return 0;
}

unsigned WINAPI SendMsg(void * arg)   // send thread main
{
	SOCKET hSock = *((SOCKET*)arg);
	char nameMsg[NAME_SIZE + BUF_SIZE];

	while (1)
	{
		fgets(msg, BUF_SIZE, stdin);
		if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
		{
			closesocket(hSock);
			exit(0);
		}
		sprintf_s(nameMsg, "%s %s", name, msg);//sprintf 사용으로 뷁뷁뷁안뜬다
		send(hSock, nameMsg, strlen(nameMsg)+1, 0); //+1로 NULL추가(?)
	}
	return 0;
}

unsigned WINAPI RecvMsg(void * arg)   // read thread main
{
	int hSock = *((SOCKET*)arg);
	char nameMsg[NAME_SIZE + BUF_SIZE];

	int strLen;
	while (1)
	{
		strLen = recv(hSock, nameMsg, NAME_SIZE + BUF_SIZE - 1, 0);
		if (strlen != 0)
		{
			if (strLen == -1)
				return -1;
			nameMsg[strLen] = 0;
			fputs(nameMsg, stdout);
		}
	}
	return 0;
}

void ErrorHandling(const char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

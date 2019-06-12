#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include<iostream> 
using namespace std;
#include <vector>
#include <cstdio>
#include "./header/server_class.h"
#include "./header/client_class.h"

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "Uszge : " << argv[0] << "<port>" << '\n';
		exit(1);
	}
	Server server(argv[1]);
	server.sc_accept();

	return 0;
}

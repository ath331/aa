#pragma once

#include <iostream>
using namespace std;

class Server
{
	int serv_sock;
	int clnt_sock;
	pthread_mutex_t mutx;
	struct sockaddr_in serv_adr;
	struct sockaddr_in clnt_adr;
	int clnt_adr_sz;
	pthread_t t_id;
public:
	Server(char* port);
	~Server();

	void sc_accept();
	void error_handling(const char *message);
};

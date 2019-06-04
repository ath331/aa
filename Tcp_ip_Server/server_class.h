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

class Server
{
	int serv_sock;
	int clnt_sock;
	vector<int> CS;
	pthread_mutex_t mutx;
	struct sockaddr_in serv_adr;
	struct sockaddr_in clnt_adr;
	int clnt_adr_sz;
	pthread_t t_id;
public:
	Server(char* port);
	~Server();

	void sc_accept();
	struct Arg;
	static void* handle_clnt_t(void* arg_t);
	void* handle_clnt(int arg);
	void send_msg(char *msg, int len);
	void error_handling(const char *message);
};

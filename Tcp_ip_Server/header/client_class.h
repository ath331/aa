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

class Client
{
	pthread_mutex_t mutx;
	pthread_t t_id;
public:
	Client();
	~Client();
	
	vector<int> CS;
	struct Arg;
	static void* handle_clnt_t(void* arg_t);
	void* handle_clnt(int arg);
	void send_msg(char *msg, int len);
};

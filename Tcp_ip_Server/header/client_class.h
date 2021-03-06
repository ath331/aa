#pragma once

#include <pthread.h>

#include<iostream> 
using namespace std;
#include <vector>

class Client_Manager
{
	pthread_mutex_t mutx;
	pthread_t t_id;
public:
	Client_Manager(){};
	Client_Manager(int clnt_sock);
	~Client_Manager(){};
	
	static	vector<int> CS;
	struct Arg
	{
		Client_Manager* client;
		int asock;
	};
	static void* handle_clnt_t(void* arg_t);
	void* handle_clnt(int arg);
	void send_msg(char *msg, int len);
};


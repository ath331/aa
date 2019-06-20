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

const static int BUF_SIZE = 100;
const static int MAX_CLNT = 256;

class Client_Manager
{
	pthread_mutex_t mutx;
	pthread_t t_id;
public:
	Client_Manager(){pthread_mutex_init(&mutx,NULL);};
	~Client_Manager();
	
	vector<int> CS;
	struct Arg
	{
        	Client_Manager* client;
        	int asock;
	};
	static void* handle_clnt_t(void* arg_t);
	void* handle_clnt(int arg);
	void send_msg(char *msg, int len);
};

void* Client_Manager::handle_clnt_t(void* arg_t)
	{
		Arg* pArg = (Arg*) arg_t;
		pArg->client->handle_clnt(pArg->asock);
	}

void* Client_Manager::handle_clnt(int arg)
	{
		int clnt_sock = arg;
		int str_len = 0;
		char msg[BUF_SIZE];

		size_t len = sizeof(msg);
		cout << "people : " << CS.size() << endl;
		while((str_len = read ( clnt_sock, msg, len+1)) != 0 && str_len!= 0 )
			send_msg(msg, len);
	
		shutdown(clnt_sock, SHUT_WR); //graceful close
		str_len = read(clnt_sock, msg, len+1);
		pthread_mutex_lock(&mutx);
		for( auto iter = CS.begin() ; iter < CS.end() ; iter++ )//remove client
		{
			if(clnt_sock == *iter)
			{
				cout << "remove : " << &iter << endl;
				iter = CS.erase(iter);
			}
		}
		cout << "people : " << CS.size() << endl;
		pthread_mutex_unlock(&mutx);

		close(clnt_sock);
	}

void Client_Manager::send_msg(char *msg, int len)
	{
		pthread_mutex_lock(&mutx);
		for(auto i = 0 ; i<CS.size();i++)
			write(CS[i], msg, len+1);
		pthread_mutex_unlock(&mutx);
	}

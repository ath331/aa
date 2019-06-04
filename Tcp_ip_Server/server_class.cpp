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
#include "server_class.h"

const static int  BUF_SIZE = 100;
const static int MAX_CLNT= 256;

Server::Server(char* port)
	{
		serv_sock = socket(PF_INET, SOCK_STREAM, 0);
		if( serv_sock == -1 )
			error_handling("socket() error!");

		memset(&serv_adr, 0, sizeof(serv_adr));
		serv_adr.sin_family = AF_INET;
	        serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
		serv_adr.sin_port = htons(atoi(port));

		if(bind(serv_sock,  (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1 )
		        error_handling("bind[] error!");
		if(listen(serv_sock, 5) == -1 )
			error_handling("listen[] error!");
	}

Server::~Server(){};

struct Server::Arg
{
	Server* server;
	int asock;
};

void Server::sc_accept()
	{
		pthread_mutex_init(&mutx, nullptr );

		 while(1)
		{	
			clnt_adr_sz = sizeof(clnt_adr);
			clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_adr, (socklen_t *)&clnt_adr_sz);
			Arg arg = {this, clnt_sock};

			pthread_mutex_lock(&mutx);
			CS.push_back(clnt_sock);
			pthread_mutex_unlock(&mutx);

	                pthread_create(&t_id, nullptr, handle_clnt_t, reinterpret_cast<void*>(&arg));
			pthread_detach(t_id);	
			printf("Connected clinet IP : %s \n", inet_ntoa(clnt_adr.sin_addr));
		}
		 close(serv_sock);

	}


void* Server::handle_clnt_t(void* arg_t)
	{
		Arg* pArg = (Arg*) arg_t;
		pArg->server->handle_clnt(pArg->asock);
	}

void* Server::handle_clnt(int arg)
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
		cout << "client out " << endl;
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

void Server::send_msg(char *msg, int len)
	{		
		pthread_mutex_lock(&mutx);
		for(auto i = 0 ; i<CS.size();i++)
			write(CS[i], msg, len+1);
		pthread_mutex_unlock(&mutx);
	}

void Server::error_handling(const char *message)
	{
	        fputs(message, stderr);
		fputc('\n', stderr);
		exit(1);
	}

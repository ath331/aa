#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include <iostream>
using namespace std;
#include <cstdio>

#include "./header/client_class.h"
#include "./header/server_class.h"

const static int BUF_SIZE = 100;
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

void Server::sc_accept()
	{
		pthread_mutex_init(&mutx, nullptr );

		 while(1)
		{
			clnt_adr_sz = sizeof(clnt_adr);
			clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_adr, (socklen_t *)&clnt_adr_sz);
			Client_Manager client(clnt_sock);
			Client_Manager::Arg arg;
			arg={nullptr,clnt_sock};

	                pthread_create(&t_id, nullptr, client.handle_clnt_t, reinterpret_cast<void*>(&arg));
			pthread_detach(t_id);	
			printf("Connected clinet IP : %s \n", inet_ntoa(clnt_adr.sin_addr));
		}
		 close(serv_sock);

	}



void Server::error_handling(const char *message)
	{
	        fputs(message, stderr);
		fputc('\n', stderr);
		exit(1);
	}

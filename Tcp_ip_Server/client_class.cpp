#include <stdio.h>

#include "./header/client_class.h"

const static int  BUF_SIZE = 100;
const static int MAX_CLNT= 256;

struct Client::Arg
{
	Client* client;
	int asock;
};
Client::Client()
{
};
Client::~Client(){};

void* Client::handle_clnt_t(void* arg_t)
	{
		Arg* pArg = (Arg*) arg_t;
		pArg->client->handle_clnt(pArg->asock);
	}

void* Client::handle_clnt(int arg)
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
		//cout << "client out " << endl;
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

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

#define BUF_SIZE  100
#define MAX_CLNT 256

void * handle_clnt(void * arg);
void send_msg(char * msg, int len);
void error_handling(const char *message);

int clnt_cnt = 0;
vector<int> CS; //add vector
pthread_mutex_t mutx;

int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;
		
	struct sockaddr_in serv_adr;
	struct sockaddr_in clnt_adr;
	int clnt_adr_sz;
	pthread_t t_id;

	
	if(argc != 2)
	{
		cout << "Uszge : " << argv[0] << "<port>" << '\n';
		exit(1);
	}	

	pthread_mutex_init(&mutx, NULL );
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if( serv_sock == -1 )
		error_handling("socket() error!");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock,  (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1 )
		error_handling("bind[] error!");

	if(listen(serv_sock, 5) == -1 )
		error_handling("listen[] error!");
	
	while(1)
	{

		clnt_adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_adr, (socklen_t *)&clnt_adr_sz);
		pthread_mutex_lock(&mutx);
		CS.push_back(clnt_sock);
		pthread_mutex_unlock(&mutx);

		pthread_create(&t_id, NULL, handle_clnt, (void*) &clnt_sock );
		pthread_detach(t_id);
		printf("Connected clinet IP : %s \n", inet_ntoa(clnt_adr.sin_addr));
	}

	close(serv_sock);

	return 0;
	

}

void * handle_clnt(void * arg)
{
	int clnt_sock =* ((int*) arg);
	int str_len = 0, i;
	char msg[BUF_SIZE];
	vector<int>::iterator iter;

	ssize_t len = sizeof(msg);
	
	while((str_len = read ( clnt_sock, msg, len+1)) != 0 && str_len!= 0 )		
		send_msg(msg, len);
		
	pthread_mutex_lock(&mutx);
	for( i=0 ; i=clnt_sock ; i++ )//remove client
	{
		if(clnt_sock == CS[i])
		{
			while( i++ < CS.size())
				CS[i] = CS[i+1];
				//CS.erase(i);
			break;
		}
	} //vector.erase
	clnt_cnt--;
	pthread_mutex_unlock(&mutx);
	close(clnt_sock);
	return NULL;
}

void send_msg(char * msg, int len)
{
	int i;
	pthread_mutex_lock(&mutx);
	for(vector<int>::size_type i = 0; i < CS.size() ; i++ )
		write(CS[i], msg, len+1);
	pthread_mutex_unlock(&mutx);
}

void error_handling(const char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

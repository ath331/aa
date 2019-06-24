#include <pthread.h>

#include<iostream> 
using namespace std;
#include <vector>

class Client_Manager
{
	pthread_mutex_t mutx;
	pthread_t t_id;
public:
	Client_Manager(){pthread_mutex_init(&mutx,NULL);};
	~Client_Manager(){};
	
	vector<int> CS;
	struct Arg;
	static void* handle_clnt_t(void* arg_t);
	void* handle_clnt(int arg);
	void send_msg(char *msg, int len);
};

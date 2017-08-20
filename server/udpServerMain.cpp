#include "udpserver.h"
#include <unistd.h>

static void * runRecv(void* arg)
{
	udpserver* _svrp = (udpserver*)arg;

	string msg;
	for(;;){
		_svrp->recvData(msg); //recv data
		cout<<"client"<<msg<<endl;
	}
}

static void* runSend(void* arg)
{

	udpserver* _svrp = (udpserver*)arg;

	for(;;){
		_svrp->brocast(); //guang bo
	}
}
static void usage(char* proc)
{
	cout<<"Usage: "<< proc<<"[local_ip]"<<"[local_port]"<<endl;
}
//./server 127.0.0.1 8080
int main(int argc, char*argv[])
{
	if(argc != 3){
		usage(argv[0]);
		exit(1);
	}
	
	int port = atoi(argv[2]);
	udpserver svr(argv[1], port);
	svr.initServer();
	daemon(0, 0);
	pthread_t recv_thread, send_thread;
	pthread_create(&recv_thread, NULL, runRecv, &svr);
	pthread_create(&send_thread, NULL, runSend, &svr);

	pthread_join(recv_thread, NULL);
	pthread_join(send_thread, NULL);
	return 0;
}

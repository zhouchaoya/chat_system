#include "udpclient.h"
#include "data_Type.h"

static void usage(char* proc)
{
	cout<<"Usage: "<< proc<<"[remote_ip]"<<"[remote_port]"<<endl;
}
//./client 127.0.0.1 8080
int main(int argc, char*argv[])
{
	if(argc != 3){
		usage(argv[0]);
		exit(1);
	}
	
	int port = atoi(argv[2]);
	udpclient cli(argv[1], port);
	cli.initclient();
	while(1){
	string sendString;
	string recvString;
	dataType data;
	data.nick_name = "fly_pig";
	data.school = "SUST";
	data.msg = "hello world";
	data.cmd = "None";
	data.ValueTostring(sendString);

	cli.sendData(sendString);
	cout<<"send done..."<<endl;
//	cli.sendData(msg);
	sleep(1);
//	msg = "";
	cout<<"123456"<<endl;
	cli.recvData(recvString);
	cout<<"recv echo:"<<recvString<<endl;
	}
	return 0;
}

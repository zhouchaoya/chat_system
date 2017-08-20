#include <signal.h>
#include "udpclient.h"
#include "data_Type.h"
#include "window.h"


static void usage(char* proc)
{
	cout<<"Usage: "<< proc<<"[remote_ip]"<<"[remote_port]"<<endl;
}

window win;
string nick_name;
string school;
dataType sendData;
dataType recvData;
udpclient* sig_cli = NULL;

static void *run_header(void* arg)
{
	string msg = "welcom to chat_system!";
	int step = 1;
	while(1){
	win.createHeader();
	int h, w;
	getmaxyx(win.header, h, w);
	win.putStrToWin(win.header, h/2, step++, msg);
	win.refreshMyWindow(win.header);
	win.clrNumsLines(win.header, h/2, 1);
	step %= w;
	step = (step == 0)?1 : step;
	usleep(300000);
	//string str;
	//win.getStringFromWin(win.input,str);

	//getmaxyx(win.output, h, w);
	//win.putStrToWin(win.output, 1, 1, str);
	//win.refreshMyWindow(win.output);
	}

}
static void* run_output_friend(void* arg)
{
	udpclient *_cli = (udpclient*)arg;
	int point = 1;
	win.createOutput();
	win.createFriendList();
	for( ; ; ){
		int fpoint = 1;
		win.refreshMyWindow(win.output);
		win.refreshMyWindow(win.friend_list);

		string str;
		_cli->recvData(str);
		recvData.stringToValue(str);//
		string tips = recvData.nick_name;  // zhangsan-SUST# nihao
		tips += "-";
		tips += recvData.school;  // gongju zidonghua shengcheng daima
	
		//friend list
		string newFriend = tips;
		int h, w;
		
		if(recvData.cmd == "QUIT"){
			_cli->deleteUser(newFriend); //shan chu haoyou			
		}else{
			tips += "#";
			tips += recvData.msg;
			getmaxyx(win.output, h, w);
			win.putStrToWin(win.output, point++, 1, tips);
		    _cli->addUser(newFriend);   //tianjia haoyouliebiao   ruhe fen ye xianshi??
		}

		getmaxyx(win.friend_list, h, w);
		win.clrNumsLines(win.friend_list, 1, h-1); //xian cha chu
		vector<string>::iterator iter = (_cli->flist).begin();

		for(; iter != (_cli->flist).end(); iter++){
			win.putStrToWin(win.friend_list, fpoint++, 1, *iter);  //fang haoyou
		}
		//win.putStrToWin(win.friend_list, fpoint, 1, newFriend); //vector baocun friend
		
		win.refreshMyWindow(win.output);
		win.refreshMyWindow(win.friend_list);

		point %= (h-1);
		if(point == 0){
			win.clrNumsLines(win.output, 1, h-1);
			win.createOutput();
			win.refreshMyWindow(win.input);
			
		}
		point = (point == 0)?1 : point;
		usleep(300000);
	}
}
static void*run_input(void* arg)
{
	udpclient *_cli = (udpclient*)arg;
	while(1){
		win.createInput();
		win.refreshMyWindow(win.input);
		string tips = "Please Enter: ";

		int h, w;
		getmaxyx(win.input, h, w);
		win.putStrToWin(win.input, 1, 1, tips);
		win.refreshMyWindow(win.input);
		
		string str;
		win.getStringFromWin(win.input, str);	
	
		sendData.nick_name = nick_name;
		sendData.school = school;
		sendData.msg = str;
		sendData.cmd = "None";

		string sendString;
		sendData.ValueTostring(sendString);
		
		_cli->sendData(sendString); //fasong shuju
		win.clrNumsLines(win.input, 1, 1); // qing ping
		usleep(20000);
	}
}

void sendQuit(int sig)
{
	sendData.nick_name = nick_name;
	sendData.school = school;
	sendData.msg = "None";
	sendData.cmd = "QUIT";
	string sendString;
	sendData.ValueTostring(sendString);
	sig_cli->sendData(sendString);
	exit(0);
}
//./client 127.0.0.1 8080 nick_name school
int main(int argc, char*argv[])
{
	if(argc != 5){
		usage(argv[0]);
		exit(1);
	}
	

	int port = atoi(argv[2]);
	udpclient cli(argv[1], port);
	
	sig_cli = &cli;
	struct sigaction act;  //signal
	act.sa_handler = sendQuit;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(2, &act, NULL);

	nick_name = argv[3];
	school = argv[4];

	cli.initclient();

	pthread_t top;
	pthread_t middle;
	pthread_t buttom;

	pthread_create(&top, NULL, run_header, NULL);
	pthread_create(&middle, NULL, run_output_friend, (void*)&cli);
	pthread_create(&buttom, NULL, run_input, (void*)&cli);

	pthread_join(top, NULL);
	pthread_join(middle, NULL);
	pthread_join(buttom, NULL);
//	while(1){
//	string sendString;
//	string recvString;
//	dataType data;
//	data.nick_name = "fly_pig";
//	data.school = "SUST";
//	data.msg = "hello world";
//	data.cmd = "None";
//	data.ValueTostring(sendString);
//
//	cli.sendData(sendString);
//	cout<<"send done..."<<endl;
////	cli.sendData(msg);
//	sleep(1);
////	msg = "";
//	cout<<"123456"<<endl;
//	cli.recvData(recvString);
//	cout<<"recv echo:"<<recvString<<endl;
//	}
	return 0;
}

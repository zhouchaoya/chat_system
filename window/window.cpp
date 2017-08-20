#include "window.h"

window::window()
{
	initscr();
}


void window::createHeader()
{
	int _h = LINES/5;
	int _w = COLS;
	int _y = 0;
	int _x = 0;
	header = newwin(_h, _w, _y, _x);

	box(header, 0, 0);

}
void window::clrNumsLines(WINDOW* win, int begin, int nums)
{
	while(nums-- > 0){
		wmove(win, begin, 0);
		wclrtoeol(win);
	}

}
void window::getStringFromWin(WINDOW* win, string &outString)
{
	char buf[1024];
	buf[0] = 0;
	wgetnstr(win, buf, sizeof(buf));
	outString = buf;  //string lei chongzai
}
void window::putStrToWin(WINDOW* win, int start_y, int start_x, string& msg)
{
	mvwaddstr(win, start_y, start_x, msg.c_str());//zhi ding chuangkou fangshuju
}
void window::refreshMyWindow(WINDOW* win)
{
	wrefresh(win);
}
void window::createOutput()
{

	int _h = LINES*3/5;
	int _w = COLS*3/4;
	int _y = LINES/5;
	int _x = 0;
	output = newwin(_h, _w, _y, _x);

	box(output, 0, 0);
}
void window::createFriendList()
{

	int _h = LINES*3/5;
	int _w = COLS/4;
	int _y = LINES/5;
	int _x = COLS*3/4;
	friend_list = newwin(_h, _w, _y, _x);

	box(friend_list, 0, 0);
}
void window::createInput()
{
	int _h = LINES/5;
	int _w = COLS;
	int _y = LINES*4/5;
	int _x = 0;
	input = newwin(_h, _w, _y, _x);

	box(input, 0, 0);

}
window::~window()
{
	delwin(header);
	delwin(output);
	delwin(friend_list);
	delwin(input);
	endwin();
}

#ifdef _DEBUG_
int main()
{
	window win;
	win.createHeader();
	win.refreshMyWindow(win.header);
	win.createOutput();
	win.refreshMyWindow(win.output);
	win.createFriendList();
	win.refreshMyWindow(win.friend_list);
	win.createInput();
	win.refreshMyWindow(win.input);
	string msg = "Welcome To Mychat_system";
	int h = 0;
	int w = 0;
	int step = 0;
	while(1){
	win.createHeader();
	getmaxyx(win.header, h, w);
	win.putStrToWin(win.header, h/2, step++, msg);
	win.refreshMyWindow(win.header);
	win.clrNumsLines(win.header, h/2, 1);
	step %= w;
	usleep(300000);
	string str;
	win.getStringFromWin(win.input,str);

	getmaxyx(win.output, h, w);
	win.putStrToWin(win.output, 1, 1, str);
	win.refreshMyWindow(win.output);
	}
//#endif
		
	return 0;
}


#endif

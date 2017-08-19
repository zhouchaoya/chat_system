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
	endwin();
}

int main()
{
	window win;
	win.createHeader();
	win.refreshMyWindow(win.header);
	sleep(2);
	win.createOutput();
	win.refreshMyWindow(win.output);
	sleep(2);
	win.createFriendList();
	win.refreshMyWindow(win.friend_list);
	sleep(2);
	win.createInput();
	win.refreshMyWindow(win.input);
	sleep(2);
	
	return 0;
}

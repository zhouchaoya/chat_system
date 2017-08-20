#ifndef _WINDOW_H
#define _WINDOW_H


#include <iostream>
#include <ncurses.h>
#include <strstream>
#include <string>

using namespace std;
class window
{
	public:
		window();
		void createHeader();
		void createOutput();
		void createFriendList();
		void createInput();
		void refreshMyWindow(WINDOW* win);
		void putStrToWin(WINDOW* win, int start_y, int start_x, string& msg);
		void getStringFromWin(WINDOW* win, string &outString);
		void clrNumsLines(WINDOW* win, int begin, int nums);
		~window();
	public:
		WINDOW* header;  //chaungkoujubing
		WINDOW* output;
		WINDOW* friend_list;
		WINDOW* input;
};




#endif

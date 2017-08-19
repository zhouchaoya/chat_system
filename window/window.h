#ifndef _WINDOW_H
#define _WINDOW_H


#include <iostream>
#include <ncurses.h>
#include <strstream>

class window
{
	public:
		window();
		void createHeader();
		void createOutput();
		void createFriendList();
		void createInput();
		void refreshMyWindow(WINDOW* win);
		~window();
	public:
		WINDOW* header;  //chaungkoujubing
		WINDOW* output;
		WINDOW* friend_list;
		WINDOW* input;
};




#endif

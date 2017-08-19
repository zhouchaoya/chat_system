#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_

#include <iostream>
#include <string>

#include "jsonApi.h"

#define SIZE 1024
using namespace std;

class dataType
{
	public:
		int stringToValue(string& instring); //fan xu lie hua
		int ValueTostring(string& outString);// xu lie hua 
	public:
		string nick_name;
		string school;
		string msg;
		string cmd;
};






#endif

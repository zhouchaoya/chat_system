#ifndef _JSONAPI_H_
#define _JSONAPI_H_

#include "json/json.h"
#include<iostream>
#include <string>

using namespace std;
class jsonApi
{
	public:
		jsonApi();
		static int serialize(Json::Value &val, string &outString);
		static int deSerialize(string &inString, Json::Value &val);
		~jsonApi();
	private:


};






#endif

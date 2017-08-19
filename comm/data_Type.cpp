#include "data_Type.h"


int dataType::stringToValue(string &inString)
// fan xu lie hua
{
	Json::Value v;
	jsonApi::deSerialize(inString, v);
	nick_name = v["nick_name"].asString();
	school = v["school"].asString();
	msg = v["msg"].asString();
	cmd = v["cmd"].asString();
	return 0;
}
int dataType::ValueTostring(string& outString)
//xu lie hua 
{
	Json::Value v;
	v["nick_name"] = nick_name;
	v["school"] = school;
	v["msg"] = msg;
	v["cmd"] = cmd;
	return jsonApi::serialize(v, outString);
}






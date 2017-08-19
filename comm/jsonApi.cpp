#include "jsonApi.h"

jsonApi::jsonApi()
{

}
int jsonApi::serialize(Json::Value &val, string &outString)
{
#ifdef _FAST_JSON
	Json::FastWriter w;
	outString = w.write(val);
#else
	Json::StyledWriter w;
	outString = w.write(val);
#endif
}

int jsonApi::deSerialize(string &inString, Json::Value &val)
{
	Json::Reader r;
	if(r.parse(inString, val, false)){
		return 0;
	}
}
jsonApi::~jsonApi()
{

}


//int main()
//{
//	jsonApi obj;
//	Json::Value v;
//	v["nick_name"] = "fly_pig";
//	v["school"] = "SUST";
//	v["msg"] = "hello world";
//	v["cmd"] = "None";
//	string str;
//	obj.serialize(v, str);
//	cout<<str<<endl;
//	return 0;
//}

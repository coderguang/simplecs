#ifndef LANUCHRESULT_TOS_H_
#define LANUCHRESULT_TOS_H_
#include "Message_tos.h"
#include <string.h>
#include <string>
using namespace std;

#pragma pack(1)
class LanuchResult_tos:public Message_tos
{
public:
		int setting;
		char name[NAMESIZE];
		char lastLanuch[LASTLANUCHSIZE];
		char lastIP[LASTIPSIZE];

		LanuchResult_tos(string n,string lastTime,string lastip,int s){
				//cout<<"in proto name="<<n<<"  time="<<lastTime<<"  ip="<<lastip<<endl;
				//get the right result from db 
				//belown had happen somethings make the value exception
				//Don't use sizeof to get the length of string ,user it's lenght
				memcpy(name,n.c_str(),n.length()+1);	
				memcpy(lastLanuch,lastTime.c_str(),lastTime.length()+1);	
				memcpy(lastIP,lastip.c_str(),lastip.length()+1);
				//cout<<"time size="<<sizeof(lastTime.c_str())<<endl;
				//cout<<"timestr size="<<sizeof(lastTime)<<endl;
				//cout<<"timestrlen size="<<lastTime.length()<<endl;
				//memcpy(name,n.c_str(),NAMESIZE);	
				//memcpy(lastLanuch,lastTime.c_str(),LASTLANUCHSIZE);	
				//memcpy(lastIP,lastip.c_str(),LASTIPSIZE);
				setting=s;
		}
		
};

#endif

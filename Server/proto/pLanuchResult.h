#ifndef PLANUCHRESULT_H_
#define PLANUCHRESULT_H_
#include "Message.h"
#include <string.h>
#include <string>
using namespace std;

static const int NAMESIZE=10;
static const int LASTLANUCHSIZE=30;
static const int LASTIPSIZE=15;

class pLanuchResult:public Message
{
public:
		char name[NAMESIZE];
		char lastLanuch[LASTLANUCHSIZE];
		char lastIP[LASTIPSIZE];
		int setting;

		pLanuchResult(string n,string lastTime,string lastip,int s){
				//cout<<"in proto name="<<n<<"  time="<<lastTime<<"  ip="<<lastip<<endl;
				//get the right result from db 
				//belown had happen somethings make the value exception
				//Don't use sizeof to get the length of string ,user it's lenght
				id=pLanuchResultID;
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

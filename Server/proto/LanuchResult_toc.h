#ifndef LANUCHRESULT_TOC_H_
#define LANUCHRESULT_TOC_H_
#include "Message.h"
#include <string.h>
#include <string>
using namespace std;

static const int NAMESIZE=8;
static const int LASTIPSIZE=16;
static const int LASTLANUCHSIZE=32;

#pragma pack(1)
//#pragma pack(PACKSIZE)
class LanuchResult_toc:public Message
{
public:
		int account_id;
		int setting;
		char name[NAMESIZE];
		char lastIP[LASTIPSIZE];
		char lastLanuch[LASTLANUCHSIZE];
		
		LanuchResult_toc(){
			id=pLanuchResultID;
			error_code=0;
		}

		LanuchResult_toc(string n,string lastTime,string lastip,int s,int a_id){
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
				account_id=a_id;
		}
		
};

#endif

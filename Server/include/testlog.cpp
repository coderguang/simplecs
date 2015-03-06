#include <iostream>
#include "Logger.h"
#include "LogInterface.h"
using namespace std;

int main(){
	MLog(DBLog,FATAL,"hello Fatal! dblog");
	MLog(DBLog,ERROR,"hello,ERROR,dblog");
	MLog(RegitLog,WARN,"this is warming,regit");
	MLog(UpdatePasswdLog,INFO,"hello,info,updatej");
	MLog(UpdatePasswdLog,DEBUG,"this is debug,update");

}

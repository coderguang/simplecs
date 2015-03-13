#include <iostream>
#include "Logger.h"
#include <unistd.h>
#include "LogInterface.h"
using namespace std;

int main(){
	int n=2;
	for(int i=0;i<n;i++){
		if(fork()==0){
			Log(DBLog,FATAL,"hello Fatal! dblog");
			Log(DBLog,ERROR,"hello,ERROR,dblog");
			Log(RegitLog,WARN,"this is warming,regit");
			Log(UpdatePasswdLog,INFO,"hello,info,updatej");
			Log(UpdatePasswdLog,DEBUG,"this is debug,update");
			LogFileClose();
		}
	}

}

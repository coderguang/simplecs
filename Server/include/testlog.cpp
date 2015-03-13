#include <iostream>
#include <unistd.h>
//#include "LogInterface.h"
#include "Logger.h"
using namespace std;

void logMsg(int i,Logger &log){
			string s="hello,log";
			s=s+" from thread"+IntToStr(i);
			cout<<s<<endl;
			log.Log(DBLog,FATAL,s);
			//log.Log(LanuchLog,ERROR,s);
			//log.Log(RegitLog,WARN,s);
			//log.Log(UpdatePasswdLog,INFO,s);
			//log.Log(ResultLog,DEBUG,s);
			//log.Log(GetResultLog,DEBUG,s);

}

int main(){
			Logger log;
			vector<thread> ths;
			for(int i=0;i<10;i++){
				cout<<"i="<<i<<endl;
				ths.push_back(thread{logMsg,i,ref(log)});
			}
			for(auto &t:ths)
				t.join();
			cout<<"log end!"<<endl;
			exit(0);
}

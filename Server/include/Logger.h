#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include <fstream>
#include "Func.h"
#include "LogConstant.h"
using namespace std;

class Logger{

private:
	string dbFile="log/dbLog";
	ofstream dbLog;

	string regitFile="log/regitLog";
	ofstream regitLog;
 
	string updatePasswdFile="log/updatePasswdLog";
	ofstream updatePasswdLog;
	
	string lanuchFile="log/lanuchLog";
	ofstream lanuchLog;

	string resultFile="log/resultLog";
	ofstream resultLog;

	string getResultFile="log/getResultLog";
	ofstream getResultLog;

	void Init(){
		dbLog.open(dbFile.c_str());
		if(!dbLog.is_open()){
			cout<<"dbFile open failed!"<<endl;	
		}
		regitLog.open(regitFile.c_str());
		if(!regitLog.is_open()){
			cout<<"regitFile open failed!"<<endl;
		}

		updatePasswdLog.open(updatePasswdFile.c_str());
		if(!updatePasswdLog.is_open()){
			cout<<"updateFile open failed!"<<endl;
		}

		lanuchLog.open(lanuchFile.c_str());
		if(!lanuchLog.is_open()){
			cout<<"lanuchFile open failed"<<endl;
		}
		
		resultLog.open(resultFile.c_str());
		if(!resultLog.is_open()){
			cout<<"resultFile open failed!"<<endl;
		}

		getResultLog.open(getResultFile.c_str());
		if(!getResultLog.is_open()){
			cout<<"getResultFile open failed"<<endl;
		}
		

	}

	void LogMsg(LogType type,string &msg,string typeMsg){
		string time=GetTimeNow();
		switch(type){
			case DBLog: 
				dbLog<<time<<" "<<typeMsg<<":"<<msg<<endl;
				break;
			case RegitLog:
				regitLog<<time<<" "<<typeMsg<<":"<<msg<<endl;				
				break;
			case UpdatePasswdLog:
				updatePasswdLog<<time<<" "<<typeMsg<<":"<<msg<<endl;
				break;
			case LanuchLog:
				lanuchLog<<time<<" "<<typeMsg<<":"<<msg<<endl;
				break;
			case ResultLog:
				resultLog<<time<<" "<<typeMsg<<":"<<msg<<endl;
				break;
			case GetResultLog:
				getResultLog<<time<<" "<<typeMsg<<":"<<msg<<endl;
				break;
		}
	}

	Logger(){
		Init();
	}

	Logger(Logger&)=delete;
	static Logger *instance;

public:
	static Logger *GetInstance(){
		if(nullptr==instance)	
			instance=new Logger();
		return instance;
	}	

	void Log(LogType type,Level level,string &msg){
		if(FATAL==level&&FATALFLAG){ 
			LogMsg(type,msg,"Fatal");
		}else if(ERROR==level&&ERRORFLAG){ 
			LogMsg(type,msg,"Error");
		}else if(WARN==level&&WARNFLAG){
			LogMsg(type,msg,"Warmming");
		}else if(INFO==level&&INFOFLAG){
			LogMsg(type,msg,"Info");
		}else if(DEBUG==level&&DEBUGFLAG){
			LogMsg(type,msg,"Debug");
		}
	}
	



};
Logger *Logger::instance;//=nullptr;

#endif 

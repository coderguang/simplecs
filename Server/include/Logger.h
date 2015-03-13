#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include <fstream>
#include "Func.h"
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include "LogConstant.h"
using namespace std;

class Logger{

protected:
	string dbFile="log/dbLog";
	ofstream dbLog;
	queue<string> dbQueue;
	mutex dbMutex;
	condition_variable dbVar;
	thread dbThread;

	string regitFile="log/regitLog";
	ofstream regitLog;
	queue<string> regitQueue;
	mutex regitMutex;
	condition_variable regitVar;
	thread regitThread;
 
	string updatePasswdFile="log/updatePasswdLog";
	ofstream updatePasswdLog;
	queue<string> updatePasswdQueue;
	mutex updatePasswdMutex;
	condition_variable updatePasswdVar;
	thread updatePasswdThread;
	
	string lanuchFile="log/lanuchLog";
	ofstream lanuchLog;
	queue<string> lanuchQueue;
	mutex lanuchMutex;
	condition_variable lanuchVar;
	thread lanuchThread;

	string resultFile="log/resultLog";
	ofstream resultLog;
	queue<string> resultQueue;
	mutex resultMutex;
	condition_variable resultVar;
	thread resultThread;

	string getResultFile="log/getResultLog";
	ofstream getResultLog;
	queue<string> getResultQueue;
	mutex getResultMutex;
	condition_variable getResultVar;
	thread getResultThread;

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

	//for close the filestream
	void LogFileCloseIner(){
		dbLog.close();
		regitLog.close();
		updatePasswdLog.close();
		lanuchLog.close();
		resultLog.close();
		getResultLog.close();

		delete instance;
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
	
	void LogFileClose(){
		LogFileCloseIner();
	}


};
Logger *Logger::instance;//=nullptr;

#endif 

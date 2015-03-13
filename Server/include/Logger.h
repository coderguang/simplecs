#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include <fstream>
#include "Func.h"
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
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
	//thread dbThread;

	string regitFile="log/regitLog";
	ofstream regitLog;
	queue<string> regitQueue;
	mutex regitMutex;
	condition_variable regitVar;
	//thread regitThread;
 
	string updatePasswdFile="log/updatePasswdLog";
	ofstream updatePasswdLog;
	queue<string> updatePasswdQueue;
	mutex updatePasswdMutex;
	condition_variable updatePasswdVar;
	//thread updatePasswdThread;
	
	string lanuchFile="log/lanuchLog";
	ofstream lanuchLog;
	queue<string> lanuchQueue;
	mutex lanuchMutex;
	condition_variable lanuchVar;
	//thread lanuchThread;

	string resultFile="log/resultLog";
	ofstream resultLog;
	queue<string> resultQueue;
	mutex resultMutex;
	condition_variable resultVar;
	//thread resultThread;

	string getResultFile="log/getResultLog";
	ofstream getResultLog;
	queue<string> getResultQueue;
	mutex getResultMutex;
	condition_variable getResultVar;
	//thread getResultThread;
	
	bool mExit;//to decide the thread should exit
	//bool mStart;//to decide the thread shoule start
	vector<thread> ths;

	void Init(){
		
		//mExit=false;
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

		//dbThread=thread{&LogDBMsg,this};
		/**
		ths.push_back(thread{LogDBMsg});
		ths.push_back(thread{LogRegitMsg});
		ths.push_back(thread{LogUpdatePasswdMsg});
		ths.push_back(thread{LogLanuchMsg});
		ths.push_back(thread{LogResultMsg});
		ths.push_back(thread{LogGetResultMsg});
		//thread dbThread(LogDBMsg);
		*/	
		
	}

	//for close the filestream
	void LogFileCloseIner(){
	
		mExit=true;//to exit the background thread
		
		//to Notify all condition
		dbVar.notify_all();
		regitVar.notify_all();
		updatePasswdVar.notify_all();
		lanuchVar.notify_all();
		resultVar.notify_all();
		getResultVar.notify_all();

		//wait all the thread finish
		//dbThread.join();
		//regitThread.join();
		//updatePasswdThread.join();
		//lanuchThread.join();
		//resultThread.join();
		//getResultThread.join();
		/**
		for(auto &t:ths)
			t.join();
		*/	

		dbLog.close();
		regitLog.close();
		updatePasswdLog.close();
		lanuchLog.close();
		resultLog.close();
		getResultLog.close();

		delete instance;
	}
	//db background thread work
	void LogDBMsg(){
		//start loop
		unique_lock<mutex> lock(dbMutex);
		dbVar.notify_all();
		while(true){
			dbVar.wait(lock);
			lock.unlock();
			while(true){
				lock.lock();
				if(dbQueue.empty()){
					break;
				}else{
					dbLog<<dbQueue.front()<<endl;
					dbQueue.pop();
				}
				lock.unlock();
			}
			if(mExit)
				break;
		}

	}

	void LogRegitMsg(){
		unique_lock<mutex> lock(regitMutex);
		regitVar.notify_all();
		while(true){
			regitVar.wait(lock);
			lock.unlock();
			while(true){
				lock.lock();
				if(regitQueue.empty()){
					break;
				}else{
					regitLog<<regitQueue.front()<<endl;
					regitQueue.pop();
				}
				lock.unlock();
			}
			if(mExit)
				break;
		}

	}

	void LogUpdatePasswdMsg(){
		unique_lock<mutex> lock(updatePasswdMutex);
		updatePasswdVar.notify_all();
		while(true){
			updatePasswdVar.wait(lock);
			lock.unlock();
			while(true){
				lock.lock();
				if(updatePasswdQueue.empty()){
					break;
				}else{
					updatePasswdLog<<updatePasswdQueue.front()<<endl;
					updatePasswdQueue.pop();
				}
				lock.unlock();
			}
			if(mExit)
				break;
		}

	}

	void LogLanuchMsg(){
		unique_lock<mutex> lock(lanuchMutex);
		lanuchVar.notify_all();
		while(true){
			lanuchVar.wait(lock);
			lock.unlock();
			while(true){
				lock.lock();
				if(lanuchQueue.empty()){
					break;
				}else{
					lanuchLog<<lanuchQueue.front()<<endl;
					lanuchQueue.pop();
				}
				lock.unlock();
			}
			if(mExit)
				break;
		}

	}

	void LogResultMsg(){
		unique_lock<mutex> lock(resultMutex);
		resultVar.notify_all();
		while(true){
			resultVar.wait(lock);
			lock.unlock();
			while(true){
				lock.lock();
				if(resultQueue.empty()){
					break;
				}else{
					resultLog<<resultQueue.front()<<endl;
					resultQueue.pop();
				}
				lock.unlock();
			}
			if(mExit)
				break;
		}

	}


	void LogGetResultMsg(){
		unique_lock<mutex> lock(getResultMutex);
		getResultVar.notify_all();
		while(true){
			getResultVar.wait(lock);
			lock.unlock();
			while(true){
				lock.lock();
				if(getResultQueue.empty()){
					break;
				}else{
					getResultLog<<getResultQueue.front()<<endl;
					getResultQueue.pop();
				}
				lock.unlock();
			}
			if(mExit)
				break;
		}

	}

	void LogMsg(LogType type,string &msg,string typeMsg){
		string time=GetTimeNow();
		string mMsg=time+" "+typeMsg+":"+msg;
		switch(type){
			case DBLog:{
					unique_lock<mutex> lock(dbMutex);
					dbQueue.push(mMsg);
					dbVar.notify_all();
				}
				break;
			case RegitLog:{
					unique_lock<mutex> lock(regitMutex);
					regitQueue.push(mMsg);
					regitVar.notify_all();
				}
				break;
			case UpdatePasswdLog:{
					unique_lock<mutex> lock(updatePasswdMutex);
					updatePasswdQueue.push(mMsg);
					updatePasswdVar.notify_all();
				}
				break;
			case LanuchLog:{
					unique_lock<mutex> lock(lanuchMutex);
					lanuchQueue.push(mMsg);
					lanuchVar.notify_all();
				}
				break;
			case ResultLog:{
					unique_lock<mutex> lock(resultMutex);
					resultQueue.push(mMsg);
					resultVar.notify_all();
				}
				break;
			case GetResultLog:{
					unique_lock<mutex> lock(getResultMutex);
					getResultQueue.push(mMsg);
					getResultVar.notify_all();
				}
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

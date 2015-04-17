#include <iostream>
#include "Logger.h"
using namespace std;

Logger Logger::*logInstance;
void Logger::Init(){
		
	//	cout<<"come to init"<<endl;
		mExit=false;
		dbLog.open(dbFile.c_str(),ios_base::app);
		if(!dbLog.is_open()){
			cout<<"dbFile open failed!"<<endl;	
		}
		regitLog.open(regitFile.c_str(),ios_base::app);
		if(!regitLog.is_open()){
			cout<<"regitFile open failed!"<<endl;
		}

		updatePasswdLog.open(updatePasswdFile.c_str(),ios_base::app);
		if(!updatePasswdLog.is_open()){
			cout<<"updateFile open failed!"<<endl;
		}

		lanuchLog.open(lanuchFile.c_str(),ios_base::app);
		if(!lanuchLog.is_open()){
			cout<<"lanuchFile open failed"<<endl;
		}
		
		resultLog.open(resultFile.c_str(),ios_base::app);
		if(!resultLog.is_open()){
			cout<<"resultFile open failed!"<<endl;
		}

		getResultLog.open(getResultFile.c_str(),ios_base::app);
		if(!getResultLog.is_open()){
			cout<<"getResultFile open failed"<<endl;
		}
		
		//cout<<"start to create thread"<<endl;

		dbThread=thread{&Logger::LogDBMsg,this};
		unique_lock<mutex> dblock(dbStartMutex);
		dbStartVar.wait(dblock,[&](){return dbStart==true;});

		//cout<<"create dbThread success"<<endl;

		regitThread=thread{&Logger::LogRegitMsg,this};
		unique_lock<mutex> regitlock(regitStartMutex);
		regitStartVar.wait(regitlock,[&]{return regitStart==true;});

		lanuchThread=thread{&Logger::LogLanuchMsg,this};
		unique_lock<mutex> lanuchlock(lanuchStartMutex);
		lanuchStartVar.wait(lanuchlock,[&]{return lanuchStart==true;});

		updatePasswdThread=thread{&Logger::LogUpdatePasswdMsg,this};
		unique_lock<mutex> updatePasswdlock(updatePasswdStartMutex);
		updatePasswdStartVar.wait(updatePasswdlock,[&]{return updatePasswdStart==true;});

		resultThread=thread{&Logger::LogResultMsg,this};
		unique_lock<mutex> resultlock(resultStartMutex);
		resultStartVar.wait(resultlock,[&]{return resultStart==true;});

		getResultThread=thread{&Logger::LogGetResultMsg,this};
		unique_lock<mutex> getResultlock(getResultStartMutex);
		getResultStartVar.wait(getResultlock,[&]{return getResultStart==true;});
		
	}

	//for close the filestream
	//void Logger::LogFileCloseIner(){
	Logger::~Logger(){
	
		//cout<<"exit the thread"<<endl;
		mExit=true;//to exit the background thread
		
		//to Notify all condition
		dbVar.notify_all();
		regitVar.notify_all();
		updatePasswdVar.notify_all();
		lanuchVar.notify_all();
		resultVar.notify_all();
		getResultVar.notify_all();

		//wait all the thread finish
		dbThread.join();
		regitThread.join();
		updatePasswdThread.join();
		lanuchThread.join();
		resultThread.join();
		getResultThread.join();

		dbLog.close();
		regitLog.close();
		updatePasswdLog.close();
		lanuchLog.close();
		resultLog.close();
		getResultLog.close();

		delete logInstance;
	}
	//db background thread work
	void Logger::LogDBMsg(){
		//cout<<"come to LogDBMsg"<<endl;
		//start loop
		unique_lock<mutex> lock(dbMutex);
		
		dbStart=true;
		dbStartVar.notify_all();

		while(true){
		//	cout<<"come to loop"<<endl;
			dbVar.wait(lock);
			lock.unlock();
			while(true){
				lock.lock();
				if(dbQueue.empty()){
		//			cout<<"dbqueue is empty"<<endl;
					break;
				}else{
					dbLog<<dbQueue.front()<<endl;
					//cout<<"write to log "<<endl<<dbQueue.front()<<endl<<endl;
					dbQueue.pop();
				}
				lock.unlock();
			}
			
			if(mExit)
				break;
		}

	}

	void Logger::LogRegitMsg(){
		unique_lock<mutex> lock(regitMutex);
		regitStart=true;
		regitStartVar.notify_all();
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

	void Logger::LogUpdatePasswdMsg(){
		unique_lock<mutex> lock(updatePasswdMutex);
		updatePasswdStart=true;
		updatePasswdStartVar.notify_all();
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

	void Logger::LogLanuchMsg(){
		unique_lock<mutex> lock(lanuchMutex);
		lanuchStart=true;
		lanuchStartVar.notify_all();
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

	void Logger::LogResultMsg(){
		unique_lock<mutex> lock(resultMutex);
		resultStart=true;
		resultStartVar.notify_all();
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


	void Logger::LogGetResultMsg(){
		unique_lock<mutex> lock(getResultMutex);
		getResultStart=true;
		getResultStartVar.notify_all();
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

	void Logger::LogMsg(LogType type,string &msg,string typeMsg){
	//	cout<<"come to LogMsg :"<<msg<<endl;
		string time=GetTimeNow();
		string mMsg=time+" "+typeMsg+":"+msg;
		switch(type){
			case DBLog:{
					unique_lock<mutex> lock(dbMutex);
				//	cout<<"push msg to dbqueue��"<<msg<<endl;
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

	Logger::Logger(){
		Logger::Init();
	}

	Logger *Logger::logInstance;

	Logger *Logger::GetInstance(){
		if(nullptr==Logger::logInstance)	
			logInstance=new Logger();
		return logInstance;
	}	

	void Logger::Log(LogType type,Level level,string &msg){
	//	cout<<"come to log func"<<endl;
		if(FATAL==level&&FATALFLAG){ 
	//		cout<<"case to Fatal"<<endl;
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
	/**
	void Logger::LogFileClose(){
		LogFileCloseIner();
	}*/


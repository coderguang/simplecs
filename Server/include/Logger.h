#ifndef M_LOG_H_
#define M_LOG_H_

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
	thread dbThread;
	bool dbStart;
	mutex dbStartMutex;
	condition_variable dbStartVar;

	string regitFile="log/regitLog";
	ofstream regitLog;
	queue<string> regitQueue;
	mutex regitMutex;
	condition_variable regitVar;
	thread regitThread;
	bool regitStart;
	mutex regitStartMutex;
	condition_variable regitStartVar;
 
	string updatePasswdFile="log/updatePasswdLog";
	ofstream updatePasswdLog;
	queue<string> updatePasswdQueue;
	mutex updatePasswdMutex;
	condition_variable updatePasswdVar;
	thread updatePasswdThread;
	bool updatePasswdStart;
	mutex updatePasswdStartMutex;
	condition_variable updatePasswdStartVar;
	
	string lanuchFile="log/lanuchLog";
	ofstream lanuchLog;
	queue<string> lanuchQueue;
	mutex lanuchMutex;
	condition_variable lanuchVar;
	thread lanuchThread;
	bool lanuchStart;
	mutex lanuchStartMutex;
	condition_variable lanuchStartVar;

	string resultFile="log/resultLog";
	ofstream resultLog;
	queue<string> resultQueue;
	mutex resultMutex;
	condition_variable resultVar;
	thread resultThread;
	bool resultStart;
	mutex resultStartMutex;
	condition_variable resultStartVar;

	string getResultFile="log/getResultLog";
	ofstream getResultLog;
	queue<string> getResultQueue;
	mutex getResultMutex;
	condition_variable getResultVar;
	thread getResultThread;
	bool getResultStart;
	mutex getResultStartMutex;
	condition_variable getResultStartVar;
	
	bool mExit;//to decide the thread should exit
	
	
	void Init();

	//for close the filestream
	void LogFileCloseIner();
	//db background thread work
	void LogDBMsg();

	void LogRegitMsg();

	void LogUpdatePasswdMsg();

	void LogLanuchMsg();

	void LogResultMsg();


	void LogGetResultMsg();

	void LogMsg(LogType type,string &msg,string typeMsg);

	Logger();

	Logger(Logger&)=delete;
	static Logger *instance;

public:
	static Logger *GetInstance();
	
	void Log(LogType type,Level level,string &msg);
	
	void LogFileClose();

};
#endif 

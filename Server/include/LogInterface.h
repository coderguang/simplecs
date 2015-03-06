#ifndef LOG_INTERFACE_H_
#define LOG_INTERFACE_H_
#include "Logger.h"
#include "LogConstant.h"
using namespace std;

void Log(LogType type,Level level,string msg){
	Logger::GetInstance()->Log(type,level,msg);
}


#endif 

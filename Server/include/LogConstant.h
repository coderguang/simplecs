#ifndef LOG_CONSTANT_H_
#define LOG_CONSTANT_H_

/**
 *this is the log level and log control
 * */

static const bool FATALFLAG=true; 
static const bool ERRORFLAG=true;
static const bool WARNFLAG=true;
static const bool INFOFLAG=true;
static const bool DEBUGFLAG=true;

/**
static const int FATAL=-1;
static const int ERROR=-2;
static const int WARN=-3;
static const int INFO=-4;
static const int DEBUG=-5;
*/
enum Level{FATAL,ERROR,WARN,INFO,DEBUG};
/**
 *this is the log file typle*
 */
enum LogType{DBLog,LanuchLog,RegitLog,UpdatePasswdLog,ResultLog,GetResultLog};


#endif 

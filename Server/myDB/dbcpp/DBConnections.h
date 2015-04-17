#ifndef DBCONNECTIONS_H_
#define DBCONNECTIONS_H_

#include <mysql.h> 
#include <string> 
#include <stdlib.h>
#include <sstream>
#include <iostream>
//#include <mutex>  //do not make it to be a background process like log
#include "DBErr.h"
#include "../../include/Func.h"
#include "../../struct/lanuch.h"
#include "../../struct/result.h"
#include "../../struct/resultAll.h"
#include "../../log/LogInterface.h"
#include "DBConstant.h"

using namespace std;


enum ConnType{REGIT,LANUCH,SECURE,RESULT,GETRESULT};
//simple instances
class DBConnections
{
protected:
	MMYSQL *regit;
	MMYSQL *lanuch;
	MMYSQL *secure;
	MMYSQL *result;
	MMYSQL *getResult;
/**
	MMYSQL *regit[REGITMAX];
	MMYSQL *lanuch[LANUCHMAX];
	MMYSQL *secure[SECUREMAX];
	MMYSQL *result[RESULTMAX];
	MMYSQL *getResult[GETRESULTMAX];

	mutex regitMutex[REGITMAX];
	mutex lanuchMutex[LANUCHMAX];
	mutex secureMutex[SECUREMAX];
	mutex resultMutex[RESULTMAX];
	mutex getResultMutex[GETRESULTMAX];
*/
 	void initDB();
	
	//close all conn
	void DBClose();

	MMYSQL *GetFree(ConnType type);
	void FreeResult(MYSQL_RES **res);

	//interface for query
	/**
	type:who will query the sql
	sql:the sql query 
	res:result
	*/
	int MyQuery(ConnType type,string sql,MYSQL_RES **res);
		
	DBConnections();
	DBConnections(DBConnections &)=delete;
	static DBConnections *dbInstance;
	
//public
public:
	static DBConnections *GetInstance();

	//regit
	//for check the account when regit
	int CheckAccount(string account);

	//for regit a accounts
	int RegitAccount(string account,string passwd,string email,string name,int question,string answer);
	
//for forget the passwd	
	int ForgetPasswd(string account,string email,int question,string answer);

//for reset the passwd
	int ResetPasswd(string account,string newPasswd);
	//for lanuch
	int Lanuch(string account,string passwd,string ip,struct Lanuch &lanResult);

	//for exit the game
	//set this accounts status be false
	int ExitLanuch(int id);
	//for InsertResult 
	//need  update the accounts flag,result*
	int InsertResult(struct ResultAll &resultA);
	//for getResult
	int GetResult(int resultID,struct ResultAll &resultA);
	
	void Close();
};
#endif

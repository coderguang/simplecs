#ifndef DBINTERFACE_H_
#define DBINTERFACE_H_
#include <iostream>
#include "DBConnections.h"
using namespace std;

static int CheckAccount(string account){
	int rNum=DBConnections::GetInstance()->CheckAccount(account);
	return rNum;
}

static int RegitAccount(string account,string passwd,string email,string name,int questionID,string answer){
	int rNum=DBConnections::GetInstance()->RegitAccount(account,passwd,email,name,questionID,answer);
	return rNum;
}

static int ForgetPasswd(string account,string email,int questionID,string answer){
	int rNum=DBConnections::GetInstance()->ForgetPasswd(account,email,questionID,answer);
	return rNum;
}

static int ResetPasswd(string account,string newPasswd){
	int rNum=DBConnections::GetInstance()->ResetPasswd(account,newPasswd);
	return rNum;
}

static int LanuchAccount(string account,string passwd,Lanuch &lanResult){
	int rNum=DBConnections::GetInstance()->Lanuch(account,passwd,lanResult);
	return rNum;
}

static int InsertResult(ResultAll &result){
	int rNum=DBConnections::GetInstance()->InsertResult(result);
	return rNum;
}

static int GetResult(int resultID,ResultAll &result){
	int rNum=DBConnections::GetInstance()->GetResult(resultID,result);
	return rNum;
}

static void DBClose(){
	DBConnections::GetInstance()->Close();

}

#endif

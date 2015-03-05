#ifndef DBINTERFACE_H_
#define DBINTERFACE_H_
#include <iostream>
#include "DBConnections.cpp"
using namespace std;

int CheckAccount(string account){
	int rNum=DBConnections::GetInstance()->CheckAccount(account);
	return rNum;
}

int RegitAccount(string account,string passwd,string email,string name,int questionID,string answer){
	int rNum=DBConnections::GetInstance()_>RegitAccount(account,passwd,email,name,questionID,answer);
	return rNum;
}

int ForgetPasswd(string account,string email,int questionID,string answer){
	int rNum=DBConnections::GetInstance()->ForgetPasswd(account,email,questionID,answer);
	return rNum;
}

int ResetPasswd(string account,string newPasswd){
	int rNum=DBConnections::GetInstance()->ResetPasswd(account,newPasswd);
	return rNum;
}

int LanuchAccount(string account,string passwd,Lanuch &lanResult){
	int rNum=DBConnections::GetInstance()->Lanuch(account,passwd,lanResult);
	return rNum;
}

int InsertReuslt(ResultAll &result){
	int rNum=DBConnections::GetInstance()->InsertResult(result);
	return rNum;
}

int GetResult(int resultID,ResultAll &result){
	int rNum=DBConnections::GetInstance()->GetResult(resultID,result);
	return rNum;
}


#endif

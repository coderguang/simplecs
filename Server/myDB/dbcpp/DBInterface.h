#ifndef DBINTERFACE_H_
#define DBINTERFACE_H_
#include <iostream>
#include "DBConnections.h"
using namespace std;

int CheckAccount(string account){
	int rNum=DBConnections::GetInstance()->CheckAccount(account);
	return rNum;
}

int RegitAccount(string account,string passwd,string email,string name,int questionID,string answer){
	int rNum=DBConnections::GetInstance()->RegitAccount(account,passwd,email,name,questionID,answer);
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

int LanuchAccount(string account,string passwd,string ip,Lanuch &lanResult){
	//cout<<"come to dbinterface"<<endl;
	int rNum=DBConnections::GetInstance()->Lanuch(account,passwd,ip,lanResult);
	//cout<<"return lanuch interface is "<<rNum<<endl;
	return rNum;
}

void ExitLanuch(int id){
	DBConnections::GetInstance()->ExitLanuch(id);

}


int InsertResult(ResultAll &result){
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

#include <iostream> 
#include <unistd.h>
#include "DBConnections.cpp"
using namespace std;
int main()
{
	DBConnections::GetInstance();
	for(int i=0;i<1000;i++){
	if(fork()==0){ 	
	int sg3=DBConnections::GetInstance()->CheckAccount("sg3");
	
	int lj=DBConnections::GetInstance()->CheckAccount("lj");
	}
//	int regit1=DBConnections::GetInstance()->RegitAccount("regit1","regit1pw","coderguang@163","regit1N",1000,"haha");
//	cout<<"regit1="<<regit1<<endl;
//	int regit2=DBConnections::GetInstance()->RegitAccount("regit2","regit2pw","coderguang163","regit2N",1000,"haha");
//	cout<<"regit2="<<regit2<<endl;
	
}
/**
	DBConnections::GetInstance()->MyQuery(LANUCH,"select account,passwd,name,status,lastlanuch,lastIP,times from accounts");
	cout<<"ok1"<<endl;
	DBConnections::GetInstance()->MyQuery(SECURE,"update accounts set passwd='resetPasswd' where account='sg5'");
	DBConnections::GetInstance()->MyQuery(LANUCH,"select account,passwd,name from accounts");
*/



}

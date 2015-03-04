#include <iostream> 
#include <unistd.h>
#include "DBConnections.cpp"
using namespace std;
int main()
{


	DBConnections::GetInstance();
/**
	int sg3=DBConnections::GetInstance()->CheckAccount("sg3");
	cout<<"sg3="<<sg3<<endl;
	
	int lj=DBConnections::GetInstance()->CheckAccount("lj");
	cout<<"lj="<<lj<<endl;

	int regit1=DBConnections::GetInstance()->RegitAccount("regit1","regit1pw","coderguang@163","regit1N",1000,"haha");
	
	cout<<"regit1="<<regit1<<endl;
	int regit2=DBConnections::GetInstance()->RegitAccount("regit2","regit2pw","coderguang163","regit2N",1000,"haha");
	cout<<"regit2="<<regit2<<endl;
	
*/
	int forget=DBConnections::GetInstance()->ForgetPasswd("sg1","coderguang@gmail.com",1000,"sg1answe");
	cout<<"forget="<<forget<<endl;
	int forget1=DBConnections::GetInstance()->ForgetPasswd("sg1","coderguanggmail.com",1000,"sg1answe");
	cout<<"forget1="<<forget1<<endl;




}

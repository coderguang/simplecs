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
	

	int forget=DBConnections::GetInstance()->ForgetPasswd("sg1","coderguang@gmail.com",1000,"sg1answe");
	cout<<"forget="<<forget<<endl;
	int forget1=DBConnections::GetInstance()->ForgetPasswd("sg1","coderguanggmail.com",1000,"sg1answe");
	cout<<"forget1="<<forget1<<endl;

	int reset1=DBConnections::GetInstance()->ResetPasswd("sg1","newPasswd1");
	cout<<"reset1="<<reset1<<endl;
	int reset2=DBConnections::GetInstance()->ResetPasswd("sg15","newPasswd1");
	cout<<"reset2="<<reset2<<endl;

	Lanuch lan;
	int lan1=DBConnections::GetInstance()->Lanuch("sg7","sg7passwd",lan);
	cout<<"lan1="<<lan1<<endl;
	cout<<"lan.name="<<lan.name<<endl;
	cout<<"lan.lastlanuch="<<lan.lastlanuch<<endl;
	cout<<"lan.lastIP="<<lan.lastIP<<endl;
	cout<<"lan.setting="<<lan.setting<<endl;
*/	
	Result red1={1001,10,2,3,32545,18654,8640,30};
	Result red2={1002,23,2,3,32545,18654,8640,30};
	Result red3={1003,10,2,3,32545,18654,8640,30};
	Result red4={1004,10,2,3,32545,18654,8640,30};
	Result red5={1005,10,2,3,32545,18654,8640,30};
	Result blue1={1005,10,2,3,32545,18654,8640,30};
	Result blue2={1007,10,2,3,32545,18654,8640,30};
	Result blue3={1006,10,2,3,32545,18654,8640,30};
	Result blue4={1002,10,2,3,32545,18654,8640,30};
	Result blue5={1004,10,2,3,32545,18654,8640,30};

	ResultAll ra={red1,red2,red3,red4,red5,blue1,blue2,blue3,blue4,blue5};
	int ra1=DBConnections::GetInstance()->InsertResult(ra);
	cout<<"resultAll1="<<ra1<<endl;

}

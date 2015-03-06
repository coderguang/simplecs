#include <iostream> 
#include <unistd.h>
#include "DBInterface.h"
using namespace std;
int main()
{
    MLog(DBLog,FATAL,"hello Fatal! dblog");
	MLog(DBLog,ERROR,"hello,ERROR,dblog");
	MLog(RegitLog,WARN,"this is warming,regit");
	MLog(UpdatePasswdLog,INFO,"hello,info,updatej");
	MLog(UpdatePasswdLog,DEBUG,"this is debug,update");
	int sg3=CheckAccount("sg3");
	//cout<<"sg3="<<sg3<<endl;
	
	int lj= CheckAccount("lj");
	//cout<<"lj="<<lj<<endl;

	int regit1=RegitAccount("regit1","regit1pw","coderguang@163","regit1N",1000,"haha");
	
	//cout<<"regit1="<<regit1<<endl;
	int regit2=RegitAccount("regit2","regit2pw","coderguang163","regit2N",1000,"haha");
	//cout<<"regit2="<<regit2<<endl;
	

	int forget=ForgetPasswd("sg1","coderguang@gmail.com",1000,"sg1answe");
	//cout<<"forget="<<forget<<endl;
	int forget1=ForgetPasswd("sg1","coderguanggmail.com",1000,"sg1answe");
	//cout<<"forget1="<<forget1<<endl;

	int reset1=ResetPasswd("sg1","newPasswd1");
	//cout<<"reset1="<<reset1<<endl;
	int reset2=ResetPasswd("sg15","newPasswd1");
	//cout<<"reset2="<<reset2<<endl;

	Lanuch lan;
	int lan1=LanuchAccount("sg7","sg7passwd",lan);
	/**
	cout<<"lan1="<<lan1<<endl;
	cout<<"lan.name="<<lan.name<<endl;
	cout<<"lan.lastlanuch="<<lan.lastlanuch<<endl;
	cout<<"lan.lastIP="<<lan.lastIP<<endl;
	cout<<"lan.setting="<<lan.setting<<endl;
	
	Result red1={1001,10,2,3,12545,1654,840,10};
	Result red2={1002,15,4,6,13745,2634,964,20};
	Result red3={1003,20,6,9,15745,3754,1040,30};
	Result red4={1004,25,8,12,16545,48654,1140,40};
	Result red5={1005,30,10,15,17545,58654,1240,50};
	Result blue1={1006,35,12,18,18145,68654,1340,60};
	Result blue2={1007,40,14,21,19545,78654,1440,70};
	Result blue3={1008,45,16,24,20545,88654,1540,80};
	Result blue4={1009,50,18,27,21545,98654,1640,90};
	Result blue5={1010,55,20,30,22545,10654,1740,100};

	ResultAll ra={red1,red2,red3,red4,red5,blue1,blue2,blue3,blue4,blue5};
	int ra1=InsertResult(ra);
	cout<<"resultAll1="<<ra1<<endl;

	
	ResultAll r2;
	int gresult2=GetResult(100,r2);
	cout<<"gesult2="<<gresult2<<endl;
	int gresult3=GetResult(1002,r2);
	
	cout<<"get result2="<<gresult3<<endl;

	cout<<"red1.id="<<r2.red1.id<<"  kill="<<r2.red1.kill<<"  death="<<r2.red1.death<<"  assist="<<r2.red1.assist<<" "<<endl;
	cout<<"  harm="<<r2.red1.harm<<"  GetHarm="<<r2.red1.getHarm<<"  reHP="<<r2.red1.reHP<<"  nullGun="<<r2.red1.nullGun<<endl;
	
	cout<<"red2.id="<<r2.red2.id<<"  kill="<<r2.red2.kill<<"  death="<<r2.red2.death<<"  assist="<<r2.red2.assist<<" "<<endl;
	cout<<"  harm="<<r2.red2.harm<<"  GetHarm="<<r2.red2.getHarm<<"  reHP="<<r2.red2.reHP<<"  nullGun="<<r2.red2.nullGun<<endl;

	cout<<"red3.id="<<r2.red3.id<<"  kill="<<r2.red3.kill<<"  death="<<r2.red3.death<<"  assist="<<r2.red3.assist<<" "<<endl;
	cout<<"  harm="<<r2.red3.harm<<"  GetHarm="<<r2.red3.getHarm<<"  reHP="<<r2.red3.reHP<<"  nullGun="<<r2.red3.nullGun<<endl;
	
	cout<<"red4.id="<<r2.red4.id<<"  kill="<<r2.red4.kill<<"  death="<<r2.red4.death<<"  assist="<<r2.red4.assist<<" "<<endl;
	cout<<"  harm="<<r2.red4.harm<<"  GetHarm="<<r2.red4.getHarm<<"  reHP="<<r2.red4.reHP<<"  nullGun="<<r2.red4.nullGun<<endl;

	cout<<"red5.id="<<r2.red5.id<<"  kill="<<r2.red5.kill<<"  death="<<r2.red5.death<<"  assist="<<r2.red5.assist<<" "<<endl;
	cout<<"  harm="<<r2.red5.harm<<"  GetHarm="<<r2.red5.getHarm<<"  reHP="<<r2.red5.reHP<<"  nullGun="<<r2.red5.nullGun<<endl;
	
	cout<<"blue1.id="<<r2.blue1.id<<"  kill="<<r2.blue1.kill<<"  death="<<r2.blue1.death<<"  assist="<<r2.blue1.assist<<" "<<endl;
	cout<<"  harm="<<r2.blue1.harm<<"  GetHarm="<<r2.blue1.getHarm<<"  reHP="<<r2.blue1.reHP<<"  nullGun="<<r2.blue1.nullGun<<endl;

	cout<<"blue2.id="<<r2.blue2.id<<"  kill="<<r2.blue2.kill<<"  death="<<r2.blue2.death<<"  assist="<<r2.blue2.assist<<" "<<endl;
	cout<<"  harm="<<r2.blue2.harm<<"  GetHarm="<<r2.blue2.getHarm<<"  reHP="<<r2.blue2.reHP<<"  nullGun="<<r2.blue2.nullGun<<endl;
	
	cout<<"blue3.id="<<r2.blue3.id<<"  kill="<<r2.blue3.kill<<"  death="<<r2.blue3.death<<"  assist="<<r2.blue3.assist<<" "<<endl;
	cout<<"  harm="<<r2.blue3.harm<<"  GetHarm="<<r2.blue3.getHarm<<"  reHP="<<r2.blue3.reHP<<"  nullGun="<<r2.blue3.nullGun<<endl;

	cout<<"blue4.id="<<r2.blue4.id<<"  kill="<<r2.blue4.kill<<"  death="<<r2.blue4.death<<"  assist="<<r2.blue4.assist<<" "<<endl;
	cout<<"  harm="<<r2.blue4.harm<<"  GetHarm="<<r2.blue4.getHarm<<"  reHP="<<r2.blue4.reHP<<"  nullGun="<<r2.blue4.nullGun<<endl;
	
	cout<<"blue5.id="<<r2.blue5.id<<"  kill="<<r2.blue5.kill<<"  death="<<r2.blue5.death<<"  assist="<<r2.blue5.assist<<" "<<endl;
	cout<<"  harm="<<r2.blue5.harm<<"  GetHarm="<<r2.blue5.getHarm<<"  reHP="<<r2.blue5.reHP<<"  nullGun="<<r2.blue5.nullGun<<endl;
*/
}

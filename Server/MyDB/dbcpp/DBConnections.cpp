#include <mysql.h> 
#include <string> 
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <mutex>
#include "DBErr.h"
#include "../../include/Func.h"
extern "C"{
#include "DBConstant.h"
}

using namespace std;


enum TYPE{REGIT,LANUCH,SECURE,RESULT,GETRESULT};
//simple instances
class DBConnections
{
protected:
	MMYSQL *regit[REGITMAX];
	MMYSQL *lanuch[LANUCHMAX];
	MMYSQL *secure[SECUREMAX];
	MMYSQL *result[RESULTMAX];
	MMYSQL *getResult[GETRESULTMAX];

	void Log(string log){
		cout<<log<<endl;
	};

	DBConnections(){
		initDB();
	};
 	void initDB(){ 
		if(mysql_server_init(sizeof(server_args)/sizeof(char*),server_args,server_groups)){ 
			Log("unknow error");
			exit(1);
		};

		//init MMYSQL []
		for(int i=0;i<REGITMAX;i++){
			regit[i]=new MMYSQL;
			regit[i]->conn=nullptr;
			regit[i]->flag=0;
			regit[i]->conn=mysql_init(NULL);
			//connect to database.c_str()
			if(!mysql_real_connect(regit[i]->conn,server.c_str(),regitUser.c_str(),regitPasswd.c_str(),database.c_str(),0,NULL,0)){
				Log("regit connections false!");
				Log(mysql_error(regit[i]->conn));
				exit(1);
			}
		}
		for(int i=0;i<LANUCHMAX;i++){
			lanuch[i]=new MMYSQL;
			lanuch[i]->conn=nullptr;
			lanuch[i]->flag=0;
			lanuch[i]->conn=mysql_init(NULL);
			//connect to database.c_str()
			if(!mysql_real_connect(lanuch[i]->conn,server.c_str(),lanuchUser.c_str(),lanuchPasswd.c_str(),database.c_str(),0,NULL,0)){
				Log("lanuch connections false!");
				Log(mysql_error(lanuch[i]->conn));
				exit(1);
			}
		}

		for(int i=0;i<SECUREMAX;i++){ 
			secure[i]=new MMYSQL; 
			secure[i]->conn=nullptr;
			secure[i]->flag=0;
			secure[i]->conn=mysql_init(NULL);
			//connect to database.c_str()
			if(!mysql_real_connect(secure[i]->conn,server.c_str(),secureUser.c_str(),securePasswd.c_str(),database.c_str(),0,NULL,0)){
				Log("secure connections false!");
				Log(mysql_error(secure[i]->conn));
				exit(1);
			}
		}
		
		for(int i=0;i<RESULTMAX;i++){
			result[i]=new MMYSQL;
			result[i]->conn=nullptr;
			result[i]->flag=0;
			result[i]->conn=mysql_init(NULL);
			//connect to database.c_str()
			if(!mysql_real_connect(result[i]->conn,server.c_str(),resultUser.c_str(),resultPasswd.c_str(),database.c_str(),0,NULL,0)){
				Log("result connections false!");
				Log(mysql_error(result[i]->conn));
				exit(1);
			}
		}

		for(int i=0;i<GETRESULTMAX;i++){
			getResult[i]=new MMYSQL;
			getResult[i]->conn=nullptr;
			getResult[i]->flag=0;
			getResult[i]->conn=mysql_init(NULL);
			//connect to database.c_str()
			if(!mysql_real_connect(getResult[i]->conn,server.c_str(),getResultUser.c_str(),getResultPasswd.c_str(),database.c_str(),0,NULL,0)){
				Log("getResult connections false!");
				Log(mysql_error(getResult[i]->conn));
				exit(1);
			}
		}
	};

	MMYSQL *GetFree(TYPE type){
		switch(type){
			case REGIT:
				for(int i=0;i<REGITMAX;i++){
					if(0==regit[i]->flag){//free
						//lock();
						cout<<"regit "<<i<<"is use"<<endl; 
					 	regit[i]->flag=1;//set flag become busy	
						return regit[i];
					}
				};
				break;
			case LANUCH:
				for(int i=0;i<LANUCHMAX;i++){
					if(0==lanuch[i]->flag){//free
						//lock();
					 	lanuch[i]->flag=1;//set flag become busy	
						return lanuch[i];
					}
				};
				break;
			case SECURE:
				 for(int i=0;i<SECUREMAX;i++){
					if(0==secure[i]->flag){//free
						//lock();
					 	secure[i]->flag=1;//set flag become busy	
						return secure[i];
					}
				};
				break;
			case RESULT:
				 for(int i=0;i<RESULTMAX;i++){
					if(0==result[i]->flag){//free
						//lock();
					 	result[i]->flag=1;//set flag become busy	
						return result[i];
					}
				};
				break;
			case GETRESULT:
				 for(int i=0;i<GETRESULTMAX;i++){
					if(0==getResult[i]->flag){//free
						//lock();
					 	getResult[i]->flag=1;//set flag become busy	
						return getResult[i];
					}
				};
				break;
			} 
			//if no conn,return nullptr
			Log("no free conn for use");
			return nullptr;
	}
	static DBConnections *instance;

	//interface for query
	/**
	type:who will query the sql
	sql:the sql query 
	res:result
	*/
	int MyQuery(TYPE type,string sql,MYSQL_RES **res){
		if(0==sql.length())
			return SQL_NULL;
		//illegal type
		if(type!=REGIT&&type!=LANUCH&&type!=SECURE&&type!=RESULT&&type!=GETRESULT)
			return TYPE_ERROR; 
		MMYSQL *temp=GetFree(type); 
		if(temp==NULL)
			return NO_FREE_CONN;	
		int errNum;
		if(0!=(errNum=mysql_query(temp->conn,sql.c_str()))){
			Log(mysql_error(temp->conn));
			temp->flag=0;
		 	return errNum;	
		 
		}
		if(type==REGIT||type==LANUCH||type==GETRESULT){ 
			if(nullptr!=res)
			    *res=mysql_store_result(temp->conn);
		}	
		temp->flag=0;
		return OK;
	}
//public
public:
	static DBConnections *GetInstance(){
		if(nullptr==instance) {
			instance=new DBConnections();
		}
		return instance;
	};
	//regit
	//for check the account when regit
	int CheckAccount(string account){
		MYSQL_RES *mres;
		string sql="select account from accounts where account='"+account+"'";
		int returnNum=MyQuery(REGIT,sql,&mres);
		if(0==returnNum){
			if((int)mysql_num_rows(mres)==0)	{
				return OK;
			}else
				return HAD_REGIT;
		}else
			return returnNum;
		
	} 
	//for regit a accounts
	int RegitAccount(string account,string passwd,string email,string name,int question,string answer){
		string questionStr=IntToStr(question);
		string sql="insert into accounts values(null,'"+account+"','"+passwd+"','"+email+"','"+name+"','"+questionStr+"','"+answer+"',false,null,null,0,1000,0,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000)";
		 int rNum=MyQuery(REGIT,sql,nullptr);
		 return rNum;
			
	}
	
//for forget the passwd	
	int ForgetPasswd(string account,string email,int questionID,string answer){
			
			
			}
	
	
};
 //must initialize in out of class ,deny would link error!!!
DBConnections *DBConnections::instance=nullptr;

#include "DBConnections.h"
#include "DBConstant.h"

extern char* server_args[];
extern char *server_groups[];

DBConnections *DBConnections::dbInstance=nullptr;
void DBConnections::initDB(){ 
	
	InitLog();//must init log before use log
	if(mysql_server_init(sizeof(server_args)/sizeof(char*),server_args,server_groups)){ 
		Log(DBLog,FATAL,"database init failed!");
		exit(1);
	};
	
	//lastest version	
		regit=new MMYSQL;
		regit->conn=nullptr;
		regit->flag=0;
		regit->conn=mysql_init(NULL);
		if(!mysql_real_connect(regit->conn,server.c_str(),regitUser.c_str(),regitPasswd.c_str(),database.c_str(),0,NULL,0)){
			cout<<mysql_error(regit->conn);
			Log(DBLog,FATAL,"regitUser  connec failed!");
			Log(DBLog,FATAL,mysql_error(regit->conn));
			exit(1);
		}

		lanuch=new MMYSQL;
		lanuch->conn=nullptr;
		lanuch->flag=0;
		lanuch->conn=mysql_init(NULL);
		if(!mysql_real_connect(lanuch->conn,server.c_str(),lanuchUser.c_str(),lanuchPasswd.c_str(),database.c_str(),0,NULL,0)){
			Log(DBLog,FATAL,"lanuchUser connec failed!");
			Log(DBLog,FATAL,mysql_error(lanuch->conn));
			exit(1);
		}

		secure=new MMYSQL;
		secure->conn=nullptr;
		secure->flag=0;
		secure->conn=mysql_init(NULL);
		if(!mysql_real_connect(secure->conn,server.c_str(),secureUser.c_str(),securePasswd.c_str(),database.c_str(),0,NULL,0)){
			Log(DBLog,FATAL,"secureUser connec failed!");
			Log(DBLog,FATAL,mysql_error(secure->conn));
				exit(1);
		}

		result=new MMYSQL;
		result->conn=nullptr;
		result->flag=0;
		result->conn=mysql_init(NULL);
		if(!mysql_real_connect(result->conn,server.c_str(),resultUser.c_str(),resultPasswd.c_str(),database.c_str(),0,NULL,0)){
			Log(DBLog,FATAL,"resultUser connec failed!");
			Log(DBLog,FATAL,mysql_error(result->conn));
			exit(1);
		}

		getResult=new MMYSQL;
		getResult->conn=nullptr;
		getResult->flag=0;
		getResult->conn=mysql_init(NULL);
		if(!mysql_real_connect(getResult->conn,server.c_str(),getResultUser.c_str(),getResultPasswd.c_str(),database.c_str(),0,NULL,0)){
			Log(DBLog,FATAL,"getReusltUser connec failed!");
			Log(DBLog,FATAL,mysql_error(getResult->conn));
			exit(1);
		}
	/**
	//init MMYSQL []
	for(int i=0;i<REGITMAX;i++){
		regit[i]=new MMYSQL;
		regit[i]->conn=nullptr;
		regit[i]->flag=0;
		regit[i]->conn=mysql_init(NULL);
		//connect to database.c_str()
		if(!mysql_real_connect(regit[i]->conn,server.c_str(),regitUser.c_str(),regitPasswd.c_str(),database.c_str(),0,NULL,0)){
			Log(DBLog,FATAL,"regitUser  connec failed!");
			Log(DBLog,FATAL,mysql_error(regit[i]->conn));
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
			Log(DBLog,FATAL,"lanuchUser connec failed!");
			Log(DBLog,FATAL,mysql_error(lanuch[i]->conn));
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
			Log(DBLog,FATAL,"secureUser connec failed!");
			Log(DBLog,FATAL,mysql_error(secure[i]->conn));
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
			Log(DBLog,FATAL,"resultUser connec failed!");
			Log(DBLog,FATAL,mysql_error(result[i]->conn));
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
			Log(DBLog,FATAL,"getReusltUser connec failed!");
			Log(DBLog,FATAL,mysql_error(getResult[i]->conn));
			exit(1);
		}
	}
	*/
};
	
//close all conn
void DBConnections::DBClose(){
/**
	for(int i=0;i<REGITMAX;i++){
		mysql_close(regit[i]->conn);
	}
	
	for(int i=0;i<LANUCHMAX;i++){
		mysql_close(lanuch[i]->conn);
	}
	
	for(int i=0;i<SECUREMAX;i++){
		mysql_close(secure[i]->conn);
	}
	for(int i=0;i<RESULTMAX;i++){
		mysql_close(result[i]->conn);
	}
	for(int i=0;i<GETRESULTMAX;i++){
		mysql_close(getResult[i]->conn);
	}
	*/		
	mysql_close(regit->conn);
	mysql_close(lanuch->conn);
	mysql_close(secure->conn);
	mysql_close(result->conn);
	mysql_close(getResult->conn);
	
	mysql_server_end();
	delete dbInstance;
	Log(DBLog,INFO,"DBclose success!");

}

MMYSQL *DBConnections::GetFree(ConnType type){
	switch(type){
		case REGIT:
			/**
			for(int i=0;i<REGITMAX;i++){
				if(0==regit[i]->flag){//free
					//lock();
					unique_lock<mutex> lock(regitMutex[i]);
					//cout<<"regit "<<i<<"is use"<<endl; 
				 	regit[i]->flag=1;//set flag become busy	
					return regit[i];
				}
			};
			*/
			return regit;
			break;
		case LANUCH:
			/**
			for(int i=0;i<LANUCHMAX;i++){
				if(0==lanuch[i]->flag){//free
					unique_lock<mutex> lock(lanuchMutex[i]);
					//lock();
				 	lanuch[i]->flag=1;//set flag become busy	
					return lanuch[i];
				}
			};
			*/
			return lanuch;
			break;
		case SECURE:
			/**
			 for(int i=0;i<SECUREMAX;i++){
				if(0==secure[i]->flag){//free
					unique_lock<mutex> lock(secureMutex[i]);
					//lock();
				 	secure[i]->flag=1;//set flag become busy	
					return secure[i];
				}
			};
			*/
			return secure;
			break;
		case RESULT:
			/**
			 for(int i=0;i<RESULTMAX;i++){
				if(0==result[i]->flag){//free
					unique_lock<mutex> lock(resultMutex[i]);
					//lock();
				 	result[i]->flag=1;//set flag become busy	
					return result[i];
				}
			};
			*/
			return result;
			break;
		case GETRESULT:
			/**
			 for(int i=0;i<GETRESULTMAX;i++){
				if(0==getResult[i]->flag){//free
					unique_lock<mutex> lock(getResultMutex[i]);
					//lock();
				 	getResult[i]->flag=1;//set flag become busy	
					return getResult[i];
				}
			};
			*/
			return getResult;
			break;
		} 
		//if no conn,return nullptr
		Log(DBLog,DEBUG,"no free connects for sql");
		return nullptr;

}
	
void DBConnections::FreeResult(MYSQL_RES **res){
	//cout<<"come to free"<<endl;
	if(nullptr!=res){
	//	cout<<"res not null"<<endl;
		mysql_free_result(*res);
	}
	//cout<<"free complete"<<endl;
	
}

//interface for query
/**
type:who will query the sql
sql:the sql query 
res:result
*/
int DBConnections::MyQuery(ConnType type,string sql,MYSQL_RES **res){
	//cout<<"come to query"<<endl;
	if(0==sql.length()){
		Log(DBLog,DEBUG,"the sql.length=0");
		return SQL_NULL;
	}
	//illegal type
	if(type!=REGIT&&type!=LANUCH&&type!=SECURE&&type!=RESULT&&type!=GETRESULT){
		Log(DBLog,DEBUG,"the sql type is error");
		return TYPE_ERROR; 
	}
	MMYSQL *temp=GetFree(type); 
	if(temp==NULL)
		return NO_FREE_CONN;	
	int errNum;
	if(0!=(errNum=mysql_query(temp->conn,sql.c_str()))){
		string err="do sql query error! ";
		err=err+sql+"\n  "+mysql_error(temp->conn);
		if(REGIT==type)
			Log(RegitLog,INFO,err);
		else if(SECURE==type)
			Log(UpdatePasswdLog,INFO,err);
		else if(LANUCH==type)
			Log(LanuchLog,INFO,err);
		else if(RESULT==type)
			Log(ResultLog,INFO,err);
		else if(GETRESULT==type)
			Log(GetResultLog,INFO,err);
		temp->flag=0;

		//if error happen,free the res here
		FreeResult(res);
	 	return errNum;	
		 
	}
	if(type==REGIT||type==LANUCH||type==GETRESULT||type==SECURE){ 
		if(nullptr!=res)
		    *res=mysql_store_result(temp->conn);
	}	
	temp->flag=0;
	return OK;
}

DBConnections::DBConnections(){
	initDB();
};
	
DBConnections *DBConnections::GetInstance(){
	if(nullptr==dbInstance) {
		//Log(DBLog,INFO,"DBConnections init");
		dbInstance=new DBConnections();
	}
	return dbInstance;
};

//regit
//for check the account when regit
int DBConnections::CheckAccount(string account){
	MYSQL_RES *res;
	string sql="select account from accounts where account='"+account+"'";
	int rNum=MyQuery(REGIT,sql,&res);
	if(0==rNum){
		int rowLength=(int)mysql_num_rows(res);
		FreeResult(&res);
		if(0==rowLength)	{
			return OK;
		}else
			return HAD_REGIT;
	}else
		return rNum;
} 

//for regit a accounts
int DBConnections::RegitAccount(string account,string passwd,string email,string name,int question,string answer){
	string questionStr=IntToStr(question);
	string t=GetTimeNow();
	string sql="insert into accounts values(null,'"+account+"','"+passwd+"','"+email+"','"+name+"','"+questionStr+"','"+answer+"',false,'"+t+"',null,0,1000,0,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000)";
	int rNum=MyQuery(REGIT,sql,nullptr);
	if(0==rNum){
		Log(RegitLog,INFO,"regit "+account+"  success!");
		return OK;
	}else{	
		Log(RegitLog,INFO,"regit "+account+"  failed!");
		return rNum;
	}
		
}
	
//for forget the passwd	
int DBConnections::ForgetPasswd(string account,string email,int question,string answer){
	string questionStr=IntToStr(question);
	string sql="select account from accounts where account='"+account+"' AND  email='"+email+"' AND question='"+questionStr+"' AND answer='"+answer+"'";
	MYSQL_RES *res;
	int rNum=MyQuery(SECURE,sql,&res);
	if(0==rNum){
		int rowLength=(int)mysql_num_rows(res);
		FreeResult(&res);
		if(1==rowLength){
			Log(UpdatePasswdLog,INFO,"identity "+account+" success");
			return OK;
		}else if(0==rowLength){
			Log(UpdatePasswdLog,INFO,"identity "+account+" failed!");
			return ERR_IDENTITY; 
		}else 
			return rowLength;
	}else
			return rNum;

}

//for reset the passwd
int DBConnections::ResetPasswd(string account,string newPasswd){
		string sql="update accounts set passwd='"+newPasswd+"' where account='"+account+"'";
		int rNum=MyQuery(SECURE,sql,nullptr);
		if(0==rNum){
			Log(UpdatePasswdLog,INFO,"reset "+account+" passwd");
			return OK;
		}else{
			Log(UpdatePasswdLog,INFO,"reset "+account+" fail");
			return rNum;
		}
}
//for lanuch
int DBConnections::Lanuch(string account,string passwd,string ip,struct Lanuch &lanResult){
		//cout<<"come to lanuch"<<endl;
		string sql="select name,lastlanuch,lastIP,setting,id,status from accounts where account='"+account+"' AND passwd='"+passwd+"'";
		MYSQL_RES *res;
		int rNum=MyQuery(LANUCH,sql,&res);
		//cout<<"return is "<<rNum<<endl;
		if(0==rNum){
			int rowLegth=(int)mysql_num_rows(res);
			//cout<<"return len="<<rowLegth<<endl;
			if(1==rowLegth){
				MYSQL_ROW row;			
				if(NULL!=(row=mysql_fetch_row(res))){
					//if this account is using now
					
					if(1==StrToInt(row[5])){
						cout<<"this account is using now!"<<endl;
						return ACCOUNT_IS_USING;
					}/**else{
						//cout<<"row[5]="<<row[5]<<endl;
					}**/

					//cout<<"to set lanResultname"<<endl;
					lanResult.name=row[0];
					//cout<<"to set lanResultlanuch"<<endl;
					lanResult.lastlanuch=row[1];
					//cout<<"to set lanResultip"<<endl;
					lanResult.lastIP=row[2];
					//cout<<"to set lanResultsetting"<<endl;
					lanResult.setting=StrToInt(row[3]);
					lanResult.id=StrToInt(row[4]);

					//cout<<"start set lanuch struct"<<endl;
					Log(LanuchLog,INFO,"lanuch "+account+"  success!");
					//cout<<"set lanuch struct success"<<endl;
					
					//change the accunts status
					string t=GetTimeNow();

					string tsql="update accounts set lastlanuch='"+t+"' where account='"+account+"'";
					MyQuery(LANUCH,tsql,nullptr);
					string isql="update accounts set lastIP='"+ip+"' where account='"+account+"'";
					MyQuery(LANUCH,isql,nullptr);
					string ssql="update accounts set status=1 where account='"+account+"'";
					MyQuery(LANUCH,ssql,nullptr);
					
					//cout<<"update status success"<<endl;
					
					FreeResult(&res);
					return OK;
				}else{
					Log(LanuchLog,WARN,"failed to get lanuch account="+account);
					FreeResult(&res);
					return DBERROR;
				}
			}else{	
				FreeResult(&res);
			//	cout<<"here come"<<endl;
				Log(LanuchLog,INFO,"account:"+account+" not match the passwd");
			//	cout<<"account:"<<account<<" lanuch error"<<endl; 
				return ACCOUNT_PASSWD_ERROR;
			}
		}else 
			return rNum;
}


int DBConnections::ExitLanuch(int id){
					string ssql="update accounts set status=0 where id='"+IntToStr(id)+"'";
					MyQuery(LANUCH,ssql,nullptr);
}



//for InsertResult 
//need  update the accounts flag,result*
int DBConnections::InsertResult(struct ResultAll &resultA){ 
	string sql="insert into results values(DEFAULT,'"+IntToStr(resultA.red1.id)+"','"+IntToStr(resultA.red1.kill)+"','"+IntToStr(resultA.red1.death)+"','"+IntToStr(resultA.red1.assist)+"','"+IntToStr(resultA.red1.harm)+"','"+IntToStr(resultA.red1.getHarm)+"','"+IntToStr(resultA.red1.reHP)+"','"+IntToStr(resultA.red1.nullGun)+"','"+IntToStr(resultA.red2.id)+"','"+IntToStr(resultA.red2.kill)+"','"+IntToStr(resultA.red2.death)+"','"+IntToStr(resultA.red2.assist)+"','"+IntToStr(resultA.red2.harm)+"','"+IntToStr(resultA.red2.getHarm)+"','"+IntToStr(resultA.red2.reHP)+"','"+IntToStr(resultA.red2.nullGun)+"','"+IntToStr(resultA.red3.id)+"','"+IntToStr(resultA.red3.kill)+"','"+IntToStr(resultA.red3.death)+"','"+IntToStr(resultA.red3.assist)+"','"+IntToStr(resultA.red3.harm)+"','"+IntToStr(resultA.red3.getHarm)+"','"+IntToStr(resultA.red3.reHP)+"','"+IntToStr(resultA.red3.nullGun)+"','"+IntToStr(resultA.red4.id)+"','"+IntToStr(resultA.red4.kill)+"','"+IntToStr(resultA.red4.death)+"','"+IntToStr(resultA.red4.assist)+"','"+IntToStr(resultA.red4.harm)+"','"+IntToStr(resultA.red4.getHarm)+"','"+IntToStr(resultA.red4.reHP)+"','"+IntToStr(resultA.red4.nullGun)+"','"+IntToStr(resultA.red5.id)+"','"+IntToStr(resultA.red5.kill)+"','"+IntToStr(resultA.red5.death)+"','"+IntToStr(resultA.red5.assist)+"','"+IntToStr(resultA.red5.harm)+"','"+IntToStr(resultA.red5.getHarm)+"','"+IntToStr(resultA.red5.reHP)+"','"+IntToStr(resultA.red5.nullGun)+"','"+IntToStr(resultA.blue1.id)+"','"+IntToStr(resultA.blue1.kill)+"','"+IntToStr(resultA.blue1.death)+"','"+IntToStr(resultA.blue1.assist)+"','"+IntToStr(resultA.blue1.harm)+"','"+IntToStr(resultA.blue1.getHarm)+"','"+IntToStr(resultA.blue1.reHP)+"','"+IntToStr(resultA.blue1.nullGun)+"','"+IntToStr(resultA.blue2.id)+"','"+IntToStr(resultA.blue2.kill)+"','"+IntToStr(resultA.blue2.death)+"','"+IntToStr(resultA.blue2.assist)+"','"+IntToStr(resultA.blue2.harm)+"','"+IntToStr(resultA.blue2.getHarm)+"','"+IntToStr(resultA.blue2.reHP)+"','"+IntToStr(resultA.blue2.nullGun)+"','"+IntToStr(resultA.blue3.id)+"','"+IntToStr(resultA.blue3.kill)+"','"+IntToStr(resultA.blue3.death)+"','"+IntToStr(resultA.blue3.assist)+"','"+IntToStr(resultA.blue3.harm)+"','"+IntToStr(resultA.blue3.getHarm)+"','"+IntToStr(resultA.blue3.reHP)+"','"+IntToStr(resultA.blue3.nullGun)+"','"+IntToStr(resultA.blue4.id)+"','"+IntToStr(resultA.blue4.kill)+"','"+IntToStr(resultA.blue4.death)+"','"+IntToStr(resultA.blue4.assist)+"','"+IntToStr(resultA.blue4.harm)+"','"+IntToStr(resultA.blue4.getHarm)+"','"+IntToStr(resultA.blue4.reHP)+"','"+IntToStr(resultA.blue4.nullGun)+"','"+IntToStr(resultA.blue5.id)+"','"+IntToStr(resultA.blue5.kill)+"','"+IntToStr(resultA.blue5.death)+"','"+IntToStr(resultA.blue5.assist)+"','"+IntToStr(resultA.blue5.harm)+"','"+IntToStr(resultA.blue5.getHarm)+"','"+IntToStr(resultA.blue5.reHP)+"','"+IntToStr(resultA.blue5.nullGun)+"')"; 
	int rNum=MyQuery(RESULT,sql,nullptr);				
		if(0==rNum){ 
			Log(ResultLog,INFO,"insert result success!\n"+sql);
			return OK;
		}else{
			Log(ResultLog,INFO,"insert result failed!\n"+sql);
			return rNum;
		}

}
//for getResult
int DBConnections::GetResult(int resultID,struct ResultAll &resultA){
	string sql="select * from results where id='"+IntToStr(resultID)+"'";
	MYSQL_RES *res;
	int rNum=MyQuery(GETRESULT,sql,&res);
	if(0==rNum){
		MYSQL_ROW row;
		if(NULL!=(row=mysql_fetch_row(res))){
			//row[0] is the result id
			resultA.red1.id=StrToInt(row[1]);
			resultA.red1.kill=StrToInt(row[2]);
			resultA.red1.death=StrToInt(row[3]);
			resultA.red1.assist=StrToInt(row[4]);
			resultA.red1.harm=StrToInt(row[5]);
			resultA.red1.getHarm=StrToInt(row[6]);
			resultA.red1.reHP=StrToInt(row[7]);
			resultA.red1.nullGun=StrToInt(row[8]);

			resultA.red2.id=StrToInt(row[9]);
			resultA.red2.kill=StrToInt(row[10]);
			resultA.red2.death=StrToInt(row[11]);
			resultA.red2.assist=StrToInt(row[12]);
			resultA.red2.harm=StrToInt(row[13]);
			resultA.red2.getHarm=StrToInt(row[14]);
			resultA.red2.reHP=StrToInt(row[15]);
			resultA.red2.nullGun=StrToInt(row[16]);

			resultA.red3.id=StrToInt(row[17]);
			resultA.red3.kill=StrToInt(row[18]);
			resultA.red3.death=StrToInt(row[19]);
			resultA.red3.assist=StrToInt(row[20]);
			resultA.red3.harm=StrToInt(row[21]);
			resultA.red3.getHarm=StrToInt(row[22]);
			resultA.red3.reHP=StrToInt(row[23]);
			resultA.red3.nullGun=StrToInt(row[24]);

			resultA.red4.id=StrToInt(row[25]);
			resultA.red4.kill=StrToInt(row[26]);
			resultA.red4.death=StrToInt(row[27]);
			resultA.red4.assist=StrToInt(row[28]);
			resultA.red4.harm=StrToInt(row[29]);
			resultA.red4.getHarm=StrToInt(row[30]);
			resultA.red4.reHP=StrToInt(row[31]);
			resultA.red4.nullGun=StrToInt(row[32]);

			resultA.red5.id=StrToInt(row[33]);
			resultA.red5.kill=StrToInt(row[34]);
			resultA.red5.death=StrToInt(row[35]);
			resultA.red5.assist=StrToInt(row[36]);
			resultA.red5.harm=StrToInt(row[37]);
			resultA.red5.getHarm=StrToInt(row[38]);
			resultA.red5.reHP=StrToInt(row[39]);
			resultA.red5.nullGun=StrToInt(row[40]);

			resultA.blue1.id=StrToInt(row[41]);
			resultA.blue1.kill=StrToInt(row[42]);
			resultA.blue1.death=StrToInt(row[43]);
			resultA.blue1.assist=StrToInt(row[44]);
			resultA.blue1.harm=StrToInt(row[45]);
			resultA.blue1.getHarm=StrToInt(row[46]);
			resultA.blue1.reHP=StrToInt(row[47]);
			resultA.blue1.nullGun=StrToInt(row[48]);

			resultA.blue2.id=StrToInt(row[49]);
			resultA.blue2.kill=StrToInt(row[50]);
			resultA.blue2.death=StrToInt(row[51]);
			resultA.blue2.assist=StrToInt(row[52]);
			resultA.blue2.harm=StrToInt(row[53]);
			resultA.blue2.getHarm=StrToInt(row[54]);
			resultA.blue2.reHP=StrToInt(row[55]);
			resultA.blue2.nullGun=StrToInt(row[56]);

			resultA.blue3.id=StrToInt(row[57]);
			resultA.blue3.kill=StrToInt(row[58]);
			resultA.blue3.death=StrToInt(row[59]);
			resultA.blue3.assist=StrToInt(row[60]);
			resultA.blue3.harm=StrToInt(row[61]);
			resultA.blue3.getHarm=StrToInt(row[62]);
			resultA.blue3.reHP=StrToInt(row[63]);
			resultA.blue3.nullGun=StrToInt(row[64]);

			resultA.blue4.id=StrToInt(row[65]);
			resultA.blue4.kill=StrToInt(row[66]);
			resultA.blue4.death=StrToInt(row[67]);
			resultA.blue4.assist=StrToInt(row[68]);
			resultA.blue4.harm=StrToInt(row[69]);
			resultA.blue4.getHarm=StrToInt(row[70]);
			resultA.blue4.reHP=StrToInt(row[71]);
			resultA.blue4.nullGun=StrToInt(row[72]);

			resultA.blue5.id=StrToInt(row[73]);
			resultA.blue5.kill=StrToInt(row[74]);
			resultA.blue5.death=StrToInt(row[75]);
			resultA.blue5.assist=StrToInt(row[76]);
			resultA.blue5.harm=StrToInt(row[77]);
			resultA.blue5.getHarm=StrToInt(row[78]);
			resultA.blue5.reHP=StrToInt(row[79]);
			resultA.blue5.nullGun=StrToInt(row[80]);

			Log(GetResultLog,INFO,"get result "+IntToStr(resultID)+" success!");
			FreeResult(&res);
			return OK;
	}else{
			FreeResult(&res);
			Log(GetResultLog,INFO,"the result "+IntToStr(resultID)+" faile,result no exist!");
			return RESULT_NOT_EXIST;
	}
			
	}else{
			return rNum;
		}

	}
	
	void DBConnections::Close(){
		DBClose();
	}


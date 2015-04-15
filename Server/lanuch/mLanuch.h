#ifndef MLANUCH_H_
#define MLANUCH_H_

#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h> //for read write
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include "../proto/proto.h"
#include "../MyDB/dbcpp/DBInterface.h"
#include "../MyDB/dbcpp/DBErr.h"
#include "Rdwr.h"
using namespace std;

/**
 *	before do others ,it must lanuch the account 
 *
 *
 *
 */

static void mLanuchGame(int connfd,string ip){
	
	while(true){
			int id=0;
			int nread=read(connfd,&id,4);

			if(nread<0){
				if(errno!=EINTR){
						cout<<"socket disconnections...."<<endl;
						close(connfd);
						exit(1);
				}else
					 continue;			
			}else if(0==nread)	/*EOF of the stream */
					 continue;

			if(pLanuchID==id){
						cout<<"get the lanuch proto"<<endl;
						Lanuch_tos *ptr=new Lanuch_tos();
						//cout<<"&ptr="<<&ptr<<endl;
						memset(ptr,'\0',sizeof(Lanuch_tos));
						readn(connfd,&ptr->error_code,sizeof(Lanuch_tos)-4);
						cout<<"accounts="<<ptr->account<<"  passwd="<<ptr->passwd<<endl;
						string account=ptr->account;
						string passwd=ptr->passwd;
					//	cout<<"acc="<<account<<"  passwd="<<passwd<<endl;
						struct Lanuch lanResult;
						int rNum=LanuchAccount(account,passwd,ip,lanResult);
						cout<<"rNum="<<rNum<<endl;
						if(0==rNum){
					
							LanuchResult_toc *result=new LanuchResult_toc(lanResult.name,lanResult.lastlanuch,lanResult.lastIP,lanResult.setting);
							cout<<"name="<<result->name<<"  lastlanuch="<<result->lastLanuch<<"  lastip="<<result->lastIP<<"  setting="<<result->setting<<endl;
							
							cout<<"write id="<<result->id<<endl;
							//result->id=1001;
							result->error_code=0;
							writen(connfd,&result->id,sizeof(LanuchResult_toc));
							//writen(connfd,&result->id,4);
							cout<<"write proto complete"<<endl;
							//if it lanuch right,break this loop and come to the public room loop
							break;
						
						}else{
							Err_toc *err=new Err_toc(rNum);
							writen(connfd,&err->id,sizeof(Err_toc));
						}
					}
				

			}
	}


#endif

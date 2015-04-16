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
#include "../include/struct/shmServer.h"
#include "../include/Func.h"
#include "../include/InitFirst.h"
using namespace std;

/**
 *	before do others ,it must lanuch the account 
 *
 *
 *
 */

static void mLanuchGame(int connfd,string ip){

	//check the server user counter,if it bigger than MAX_USER,reject the new connections

	
	InitFirst();
	sem_wait(nummutex);
	//check the user counter  in the server
	if(numptr->counter>=MAX_USER){
			cout<<"come to server full!"<<endl;
			Err_toc *temp=new Err_toc(SERVER_FULL);
			writen(connfd,&temp->id,sizeof(Err_toc));
			sem_post(nummutex);
			DelayTime(5);
			exit(1);
	}
	sem_post(nummutex);
	
	
	while(true){
			int id=0;
			int nread=read(connfd,&id,4);

			if(nread<0){
				if(errno!=EINTR&&errno==EPIPE){
						cout<<"socket disconnections...."<<endl;
						close(connfd);
						exit(1);
				}else
					 continue;			
			}else if(0==nread)	/*EOF of the stream */
					 continue;

			if(pLanuchID==id){
						Lanuch_tos *ptr=new Lanuch_tos();
						memset(ptr,'\0',sizeof(Lanuch_tos));
						readn(connfd,&ptr->error_code,sizeof(Lanuch_tos)-4);

						cout<<"accounts="<<ptr->account<<"  passwd="<<ptr->passwd<<endl;
						string account=ptr->account;
						string passwd=ptr->passwd;
						struct Lanuch lanResult;
						int rNum=LanuchAccount(account,passwd,ip,lanResult);

						cout<<"rNum="<<rNum<<endl;
						if(0==rNum){
					
							//server counter ++
							sem_wait(nummutex);
							numptr->counter++;
							//cout<<"now server counter is "<<numptr->counter<<endl;
							sem_post(nummutex);


							//save this to the shmList				
							pid_t pid=getpid();

							sem_wait(listmutex);

							for(int i=0;i<MAX_USER;i++){
								if(0==listptr->flag[i]){
										listptr->flag[i]=1;//flag this is used
										listptr->id[i]=lanResult.id;
										listptr->pid[i]=(int)pid;
										cout<<"id="<<listptr->id[i]<<" in the listptr"<<endl;
										break;
								}
							}					

							sem_post(listmutex);
		

							LanuchResult_toc *result=new LanuchResult_toc(lanResult.name,lanResult.lastlanuch,lanResult.lastIP,lanResult.setting,lanResult.id);
							cout<<"name="<<result->name<<"  lastlanuch="<<result->lastLanuch<<"  lastip="<<result->lastIP<<"  setting="<<result->setting<<endl;
							
							result->error_code=0;
							writen(connfd,&result->id,sizeof(LanuchResult_toc));

							//if it lanuch right,break this loop and come to the public room loop
							//send the Party_toc
							
							Party_toc *ptemp=new Party_toc(1000,1001,1002,1003,1004,1005,1006,1007,1008,1009);	
							writen(connfd,&ptemp->id,sizeof(Party_toc));
							break;
						
						}else{
							Err_toc *err=new Err_toc(rNum);
							writen(connfd,&err->id,sizeof(Err_toc));
						}
					}
				

			}
}

#endif

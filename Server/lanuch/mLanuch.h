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
using namespace std;

/**
 *	before do others ,it must lanuch the account 
 *
 *
 *
 */

static void mLanuchGame(int connfd,string ip){

	//check the server user counter,if it bigger than MAX_USER,reject the new connections
	int fd;
	struct shmNum *shmptr;
	sem_t *smutex;
	
	fd=shm_open("mshmNum",O_RDWR,0644);
	if(fd<0){
		cout<<"child process open mshmNum failed!"<<endl;
		exit(1);
	}
	
	shmptr=(struct shmNum*)mmap(NULL,sizeof(struct shmNum),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

	close(fd);

	smutex=sem_open("msemNum",0);

	cout<<"come to here!="<<shmptr->counter<<endl;

	sem_wait(smutex);
	//check the user counter  in the server
	if(shmptr->counter>=MAX_USER){
			cout<<"come to server full!"<<endl;
			Err_toc *temp=new Err_toc(SERVER_FULL);
			writen(connfd,&temp->id,sizeof(Err_toc));
			sem_post(smutex);
			DelayTime(5);
			exit(1);
	}
	sem_post(smutex);
	
	
//open the shmList share memory
	int fdd;
	struct shmList *list;
	
	sem_t *lmutex;
	
	fdd=shm_open("mshmList",O_RDWR,0644);
	
	if(fdd<0){
		cout<<"open mshmList failed when mLanuchGame!"<<endl;
	}
	
	list=(struct shmList*)mmap(NULL,sizeof(struct shmList),PROT_READ|PROT_WRITE,MAP_SHARED,fdd,0);

	close(fdd);
	
	lmutex=sem_open("msemList",0);
	

	
	
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
					
							//server counter ++
							sem_wait(smutex);
							shmptr->counter++;
							//cout<<"now server counter is "<<shmptr->counter<<endl;
							sem_post(smutex);


							pid_t pid=getpid();
							//save this to the shmList				
							for(int i=0;i<MAX_USER;i++){
								if(0==list->flag[i]){
										list->flag[i]=1;//flag this is used
										list->id[i]=lanResult.id;
										list->pid[i]=(int)pid;
										cout<<"id="<<list->id[i]<<" in the list"<<endl;
										break;
								}
							}					
		

							LanuchResult_toc *result=new LanuchResult_toc(lanResult.name,lanResult.lastlanuch,lanResult.lastIP,lanResult.setting,lanResult.id);
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
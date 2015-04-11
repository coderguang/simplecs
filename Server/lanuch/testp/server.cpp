#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include "../../include/LogInterface.h"
#include "../../include/Func.h"
#include "../NetConstant.h"
#include "../../proto/proto.h"
#include "../../proto/protoID.h"
#include "../../MyDB/dbcpp/DBInterface.h"
/**
 *this is the server main process
 *all user process are fork from this process
 *after fork from this ,child process do it's own things
 *author:coderguagn
 *date:2014/04/08
 */

//the child process exit functions

void sig_chld_exit(int signo){
	pid_t pid;
	int stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0)
			cout<<"child "<<pid<<"  terminated!"<<endl;
	return ;

}
//read the stream after get the proto id
static ssize_t readn(int connfd,void *vptr,size_t len){

	size_t nleft; //the left character in stream
	ssize_t nread;	//had read character in stream
	
	char *ptr;

	ptr=(char*)vptr;

	nleft=len;
	
	while(nleft>0){
		if((nread=read(connfd,ptr,nleft))<0){
				if(errno==EINTR)
					nread=0;
				else
					return -1;
		}else if(0==nread){
				break;
		}
	
		nleft=nleft-nread;
		ptr=ptr+nread;
	}
	return (len-nleft);

};

//write the stream into the connfd
static ssize_t writen(int connfd,void *vptr,size_t len){

	size_t nleft;
	ssize_t nwritten;
	
	const char *ptr;
	ptr=(char*)vptr;
	nleft=len;

	while(nleft>0){
		if((nwritten=write(connfd,ptr,nleft))<=0){
				if(nwritten<0&&errno==EINTR){
						cout<<"nwritten<0"<<endl;
						nwritten=0;
				}else{
						cout<<"write to stream error"<<endl;
						exit(0);
				}

		}
		
		nleft=nleft-nwritten;
		ptr=ptr+nwritten;


	}
	return (len-nwritten);

}

//read the id to decide the proto

static void startProc(int connfd){
	
/**
	int flags=fcntl(connfd,F_GETFL,0);	//get the connfd status
	if(flags<0)
		cout<<"get connfd status failed"<<endl;
	
	flags&=~O_NONBLOCK;
	if(fcntl(connfd,F_SETFL,flags)<0)
		cout<<"set connfd status failed"<<endl;
*/	
	while(true){
			int id=0;
			int n=read(connfd,&id,4);
			if(n<0){
				if(errno!=EINTR){	//disconections
					cout<<"socket disconnections..."<<endl;
					close(connfd);
					exit(1);
				}else
					continue;
			}else if(0==n){ /*EOF in the stream*/
					continue;
			}
			//cout<<"n="<<n<<endl;	
			//cout<<"the id is "<<id<<endl;
			

			switch(id){
					case pLanuchID:
						cout<<"get the lanuch proto"<<endl;
						Lanuch_tos *ptr=new Lanuch_tos();
						//cout<<"&ptr="<<&ptr<<endl;
						memset(ptr,'\0',sizeof(Lanuch_tos));
						//readn(connfd,&ptr,sizeof(Lanuch_tos));
						readn(connfd,&ptr->error_code,sizeof(Lanuch_tos));
						cout<<"   accounts="<<ptr->account<<"  passwd="<<ptr->passwd<<endl;
						string account=ptr->account;
						string passwd=ptr->passwd;
					//	cout<<"acc="<<account<<"  passwd="<<passwd<<endl;
						struct Lanuch lanResult;
						int rNum=LanuchAccount(account,passwd,lanResult);
						cout<<"rNum="<<rNum<<endl;
						if(0==rNum){
					
							LanuchResult_toc *result=new LanuchResult_toc(lanResult.name,lanResult.lastlanuch,lanResult.lastIP,lanResult.setting);
							cout<<"name="<<result->name<<"  lastlanuch="<<result->lastLanuch<<"  lastip="<<result->lastIP<<"  setting="<<result->setting<<endl;
							
							cout<<"write id="<<result->id<<endl;
							//result->id=1001;
						//	writen(connfd,&result,sizeof(LanuchResult_toc));
							writen(connfd,&result->id,sizeof(LanuchResult_toc));
							//writen(connfd,&result->id,4);
							cout<<"write proto complete"<<endl;
						
							/**
							int test=1001;
							writen(connfd,&test,sizeof(test));
							*/
						}
					break;
				

			}
	}

}
int main(){
	int listenfd;	//the  listen  fd
	int connfd;	//the client fd;

	struct sockaddr_in cliaddr;	//client addr
	struct sockaddr_in servaddr;	//server addr
	
	//init the listenfd
	if(-1==(listenfd=socket(AF_INET,SOCK_STREAM,0))){
			cout<<"socket init failed!"<<endl;
			exit(0);
	}
	
	bzero(&servaddr,sizeof(servaddr));
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(PORT);
	servaddr.sin_addr.s_addr=INADDR_ANY;

	//bind the port
	if(-1==bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))){
			cout<<"bind the port failed!"<<endl;
			exit(0);
	}
	
	//listen
	
	if(-1==listen(listenfd,BACKLOG)){
		cout<<"listen failed"<<endl;
		exit(1);
	}
	//catch the child process exit
	signal(SIGCHLD,sig_chld_exit);
	
	while(true){
		
		socklen_t clilen=sizeof(cliaddr);

		connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
		
		//if(fork()==0){
				//string addr=inet_ntoa(cliaddr.sin_addr);
				//cout<<"client from "<<addr<<" lanuch"<<endl;
				//close(connfd);
				//exit(0);
				//cout<<"connfd="<<connfd<<endl;
				startProc(connfd);
				//exit(0);

		//}



	}

}


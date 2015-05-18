#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include "../log/LogInterface.h"
#include "../include/Func.h"
#include "NetConstant.h"
#include "Connection.h"
#include "../include/OpenShm.h"
#include "../struct/ShmServer.h"
#include "../gameOver/Sig_exit.h"
/**
 *this is the server main process
 *all user process are fork from this process
 *after fork from this ,child process do it's own things
 *author:coderguagn
 *date:2014/04/08
 */

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

	//open the share memory of mshmNum and mshmList
	//only main process will call this function
	openShmFunc();//in openShm.h  


	//must create sharememory first
	InitExit();//for sig_chld_exit share memory and semphor and init the game status
	
	InitFirst();//for sig_chld to updateParty it must open then


	//struct timeval tv=new timeval{5,0};
	struct timeval tv;
	tv.tv_sec=5;
	tv.tv_usec=0;
	
	
	while(true){
		
		socklen_t clilen=sizeof(cliaddr);

		connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
		
		if(fork()==0){
				//string addr=inet_ntoa(cliaddr.sin_addr);
				//cout<<"client from "<<addr<<" lanuch"<<endl;
				//close(connfd);
				//exit(0);
				//cout<<"connfd="<<connfd<<endl;
				string ip=inet_ntoa(cliaddr.sin_addr);	
/**
				if(0==setsockopt(listenfd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(int))){
					cout<<"set receive timeout sucess:connfd="<<connfd<<endl;
				}else{
					cout<<"set receive timeout fail:connfd="<<connfd<<endl;
				}

				if(0==setsockopt(listenfd,SOL_SOCKET,SO_SNDTIMEO,&tv,sizeof(int))){
					cout<<"set send timeout sucess:connfd="<<connfd<<endl;
				}else{
					cout<<"set receive timeout fail:connfd="<<connfd<<endl;
				}
**/
				if(0==setsockopt(connfd,SOL_SOCKET,SO_RCVTIMEO,(char*)&tv,sizeof(int))){
					cout<<"set receive timeout sucess:connfd="<<connfd<<endl;
				}else{
					cout<<"set receive timeout fail:connfd="<<connfd<<endl;
				}

				if(0==setsockopt(connfd,SOL_SOCKET,SO_SNDTIMEO,(char*)&tv,sizeof(int))){
					cout<<"set send timeout sucess:connfd="<<connfd<<endl;
				}else{
					cout<<"set receive timeout fail:connfd="<<connfd<<endl;
				}

				startProc(connfd,ip);
				
				//exit(0);

		}



	}

}


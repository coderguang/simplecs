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
#include "../include/openShm.h"
#include "../struct/shmServer.h"
#include "../gameOver/sig_exit.h"
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
	openShmFunc();//in openShm.h

	//must create sharememory first
	InitExit();//for sig_chld_exit share memory and semphore
	
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
				startProc(connfd,ip);
				//exit(0);

		}



	}

}


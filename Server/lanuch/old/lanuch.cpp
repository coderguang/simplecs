#include <stdio.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <iostream>
#include <sys/types.h> //for sockadd_in
#include <unistd.h> //for fork execl,
#include <sys/wait.h> //for waitpid
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../include/LogInterface.h"
#include "../include/Func.h"
#include "NetConstant.h"
using namespace std;

//when child exit,call this func to protect it become zombie
void sig_chld_exit(int signo){
	pid_t pid;
	int stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0)
		printf("child %d terminated\n",pid);
	return ;


}

int main(){
	int listenfd;//the listen fd
	int connfd;//the client fd
	
	struct sockaddr_in cliaddr;//client addr
	struct sockaddr_in servaddr;//server addr
	
	//listen
	if(-1==(listenfd=socket(AF_INET,SOCK_STREAM,0))){//use IPv4 and tcp
		cout<<"socket init failed"<<endl;
		exit(1);
	}
	
	bzero(&servaddr,sizeof(servaddr));//zero the server addr

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(PORT);
	servaddr.sin_addr.s_addr=INADDR_ANY;


	//bind the socket port
	if(-1==bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))){
		cout<<"bind failed!"<<endl;
		exit(1);
	}
	
	if(-1==listen(listenfd,BACKLOG)){
		cout<<"listen failed!"<<endl;
		exit(1);
	}
	
	signal(SIGCHLD,sig_chld_exit);//recive the child process SIGCHLD signal
	
	for(;;){
		socklen_t clilen=sizeof(cliaddr);	
		
		connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);//accept the client connections
		
		//cout<<"at time "<<GetTimeNow()<<" "<<inet_ntoa(cliaddr.sin_addr)<<" connectiosn"<<endl;
		
		//fork the child process
		if(fork()==0){
			while(true){
				char buf[MAXSIZE];
				int rval;
				//read the stream
				if((rval=read(connfd,buf,MAXSIZE))>0){
					cout<<"read the msg "<<buf<<endl;
				}
				string msg="hello,welcome to guang server\n";
				if(send(connfd,msg.c_str(),msg.length(),0)==-1){
					cout<<"send error!\n"<<endl;
					close(connfd);
					exit(0);
				}
				
			}

		}
		close(connfd);
	

	}
	
}

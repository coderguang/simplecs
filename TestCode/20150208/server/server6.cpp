/*
 * autho:chenshiguang
 * Data:2015-02-03
 * env:Centos 6.5
 * Builder:g++ clang++
 */  
  
#include <stdio.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <string.h>  
#include <sys/types.h>  
#include <netinet/in.h>  
#include <sys/socket.h>  //for connect,bind,listen,accept
#include <sys/wait.h>  
#include <unistd.h>  //for fork,execl,close
#include <arpa/inet.h> //for inet_aton
#include <thread>
#include <vector>
using namespace std;

#define PORT	9201  
#define BACKLOG 10  
#define MAXSIZE 1024  
  

void DoSend(int connfd){
	for (;;){
		char buf[MAXSIZE];
		int rval;
		if ((rval = read(connfd, buf, MAXSIZE)) < 0) {
			printf("read  msg  error!\n");
			close(connfd);
			break;
		}
		if (rval>0){
			//printf("%s\n", buf);
		}
		char* msg = "Hello,welcome to guang server\n";
		if (send(connfd, msg, strlen(msg), 0) == -1){
			printf("send msg  error!\n");
			close(connfd);
			break;;
		}
	}
}

void server() {  
	int	listenfd,connfd;
	pid_t	childpid;
	socklen_t	clilen;
	struct sockaddr_in cliaddr;  
	struct sockaddr_in servaddr;  

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr,sizeof(servaddr));  
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;  
   
	bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr));
	listen(listenfd, BACKLOG);

	//before accept fork the process
	for (; ;){
		clilen = sizeof(cliaddr);		
		connfd = accept(listenfd, (struct sockaddr*) &cliaddr, &clilen);
		printf("client from %s had connected!\n",(char*)inet_ntoa(cliaddr.sin_addr));		
		if ((childpid == fork()) == 0){//child  process
				char buf[MAXSIZE];
				int rval;
				if ((rval = read(connfd, buf, MAXSIZE)) < 0) {
					printf("read  msg  error!\n");
					close(connfd);
					break;
				}
				if (rval>0){
					//printf("%s\n", buf);
				}
				char* msg = "Hello,welcome to guang server\n";
				if (send(connfd, msg, strlen(msg), 0) == -1){
					printf("send msg  error!\n");
					close(connfd);
					break;;
				}
				thread t(DoSend, connfd);
				t.join();
		}
		close(connfd);
	 }
}  
int main() {
	server();
	return 0;  
}  

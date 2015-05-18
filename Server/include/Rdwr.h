#ifndef RDWR_H_
#define RDWR_H_

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
//#include <mman.h>
#include <semaphore.h>
using namespace std;


extern sem_t *netmutex;
//read the stream after get the proto id
static ssize_t readn(int connfd,void *vptr,size_t len){

	size_t nleft; //the left character in stream
	ssize_t nread;	//had read character in stream
	
	char *ptr;

	ptr=(char*)vptr;

	nleft=len;
	
	while(nleft>0){
		if((nread=read(connfd,ptr,nleft))<0){
				if(errno==EINTR){
					nread=0;
				}else if(errno==EWOULDBLOCK){
						cout<<"receive time out£¡"<<endl;
						continue;
				}else{
					return -1;
				}
		}else if(0==nread){
				break;
		}
	
		nleft=nleft-nread;
		ptr=ptr+nread;
	}
	return (len-nleft);

};


//write the stream into the connfd


//write the stream into the connfd
static ssize_t writen2(int connfd,void *vptr,size_t len){

	static int rwTimes=0;//user for controller the rewrite times,

	//cout<<"writen len="<<len<<endl;
	size_t nleft;
	ssize_t nwritten;

	
	
	const char *ptr;
	void *rptr=vptr; //use for rwrite if it write to stream error!

	ptr=(char*)vptr;


	nleft=len;

	while(nleft>0){
		if((nwritten=write(connfd,ptr,nleft))<=0){
				if(nwritten<0&&errno==EINTR){ //EINTR,write again
						cout<<"nwritten<0"<<endl;
						nwritten=0;
				}else if(nwritten<0&&errno==EWOULDBLOCK){
						cout<<"writen time out£¡"<<endl;
						continue;
				}else{
						cout<<"write to stream error! "<<rwTimes<<endl;
						return -1;

				}

		}
		
		nleft=nleft-nwritten;
		ptr=ptr+nwritten;


	}

	//reset the rwTimes
	
	rwTimes=0;

	return (len-nwritten);

}


static ssize_t writen(int connfd,void *vptr,size_t len){
	
	sem_wait(netmutex);
	int re=writen2(connfd,vptr,len);
	sem_post(netmutex);
	return re;


}

#endif

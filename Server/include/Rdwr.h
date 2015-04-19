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
using namespace std;



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
				}else{
						cout<<"write to stream error,rewriten..at "<<rwTimes<<endl;

						if(rwTimes<5){
							rwTimes++;
							writen(connfd,rptr,len);
						}else{
							cout<<"rewrite still error,give up try!"<<endl;
							rwTimes=0;
							return -1;
						}
						
						
					//	return -1;
				}

		}
		
		nleft=nleft-nwritten;
		ptr=ptr+nwritten;


	}

	//reset the rwTimes
	
	rwTimes=0;

	return (len-nwritten);

}



#endif

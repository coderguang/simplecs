#ifndef CONNECTION_H_
#define CONNECTION_H_

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

	size_t nleft;
	ssize_t nwritten;
	
	const char *ptr;
	ptr=(char*)vptr;


	while(nleft>0){
		if((nwritten=write(connfd,ptr,nleft))<=0){
				if(nwritten<0&&errno==EINTR){
						cout<<"nwritten<0"<<endl;
						nwritten=0;
				}else{
						cout<<"write to stream error"<<endl;
				}

		}
		
		nleft=nleft-nwritten;
		ptr=ptr+nwritten;


	}
	return (len-nwritten);

};

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
			int id;
			int n=read(connfd,&id,4);
			if(n<=0){
				continue;
			}
				
			cout<<"the id is "<<id<<endl;
			
			switch(id){
					case pLanuchID:
						cout<<"get the lanuch proto"<<endl;
						pLanuch *ptr=new pLanuch();
						readn(connfd,&ptr->account,sizeof(pLanuch)-4);
						cout<<"accounts="<<ptr->account<<"  passwd="<<ptr->passwd<<endl;
					break;
				

			}
	}

}

#endif
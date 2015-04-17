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
#include "../proto/Proto.h"
#include "../myDB/dbcpp/DBInterface.h"
#include "../myDB/dbcpp/DBErr.h"
#include "mLanuch.h"
#include "../include/Rdwr.h"
#include "../include/InitFirst.h"
#include "../include/Func.h"
#include "../publicRoom/UpdateParty.h"
using namespace std;

//static const int MAXPROTO=256;//the proto max size
//static const size_t idsize=4;
//read the id to decide the proto

static void startProc(int connfd,string ip){

	//every child process should call InitFirst at first
	
	InitFirst();
	
	
	//come to the lanuch loop
	mLanuchGame(connfd,ip);
	
	cout<<"lanuch success,come to publicRoom"<<endl;
	
	while(true){
				
			int id=0;
			int nread=read(connfd,&id,4);

			if(nread<0){
				if(errno!=EINTR){
						cout<<"socket disconnections in the public room...."<<endl;
						//if in the room disconnections.update the party
						//shouldn't do this in here ,because it doesn't call sig_exit,the flag and conn is valid,but the socket disconnects,it makes write stream error!
						//updateParty();
						//DelayTime(5);
						close(connfd);
						exit(1);
				}else
					 continue;			
			}else if(0==nread)	/*EOF of the stream */
					 continue;

				

	}

}

#endif

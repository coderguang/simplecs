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
#include "../MyDB/dbcpp/DBInterface.h"
#include "../MyDB/dbcpp/DBErr.h"
#include "mLanuch.h"
#include "Rdwr.h"
using namespace std;

//static const int MAXPROTO=256;//the proto max size
//static const size_t idsize=4;
//read the id to decide the proto

static void startProc(int connfd,string ip){

	//come to the lanuch loop
	mLanuchGame(connfd,ip);
	
	cout<<"lanuch success,come to publicRoom"<<endl;
	
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

				

	}

}

#endif

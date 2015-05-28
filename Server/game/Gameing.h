#ifndef GAMEING_H_
#define GAMEING_H_

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
#include "../include/Rdwr.h"
#include "../include/InitFirst.h"
#include "../include/Func.h"
#include "../publicRoom/UpdateParty.h"
#include "../proto/ProtoID.h"
#include "../struct/PersonData.h"
#include "../struct/ShmServer.h"
using namespace std;

void InGameLoop(int connfd){
	
	cout<<"game statr success,come to map"<<endl;
	
	while(true){

			sem_wait(statusmutex);
			if(IN_RESULT==statusptr->status){//game is over
				sem_post(statusmutex);
				exit(0);
			}
			sem_post(statusmutex);
				
			int id=0;
			int nread=read(connfd,&id,4);
			

			if(nread<0){
				if(errno!=EINTR){
						cout<<"socket disconnections in the gameMap...."<<endl;
						close(connfd);
						exit(1);
				}else{
					 continue;			
				}
			}else if(0==nread)	/*EOF of the stream */
					 continue;
			
				

	}

}

#endif

#ifndef IN_ROOM__H_
#define IN_ROOM_H_

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
using namespace std;

//when the game in room ,belown loop solve the proto
//
//only receive chat ,party_change,game_start proto

void InRoomLoop(int connfd){
	
	cout<<"lanuch success,come to publicRoom"<<endl;
	
	while(true){
				
			int id=0;
			int nread=read(connfd,&id,4);
			
			cout<<"the id is "<<id<<endl;

			if(nread<0){
				if(errno!=EINTR){
						cout<<"socket disconnections in the public room...."<<endl;
						//if in the room disconnections.update the party
						//shouldn't do this in here ,because it doesn't call sig_exit,the flag and conn is valid,but the socket disconnects,it makes write stream error!
						//updateParty();
						//DelayTime(5);
						close(connfd);
						exit(1);
				}else{
					 continue;			
				}
			}else if(0==nread)	/*EOF of the stream */
					 continue;
			
			if(pChatID==id){
					cout<<"receive the chat in the room"<<endl;

					Chat_tocs *temp=new Chat_tocs();
					memset(temp,'\0',sizeof(Chat_tocs));

					readn(connfd,&temp->error_code,sizeof(Chat_tocs)-4);
						
					temp->id=pChatID;
					
					cout<<"uid="<<temp->user_id<<"  msg="<<temp->msg<<endl;

					//writen(connfd,&temp->id,sizeof(Chat_tocs));
					//broadcast this msg to the all

					mBroadcast(ALL,temp,sizeof(Chat_tocs));
					
			}
				

	}

}

#endif

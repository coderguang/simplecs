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
			
			//cout<<"the id is "<<id<<endl;

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
					//cout<<"receive the chat in the room"<<endl;

					Chat_tocs *temp=new Chat_tocs();
					memset(temp,'\0',sizeof(Chat_tocs));

					readn(connfd,&temp->error_code,sizeof(Chat_tocs)-4);
						
					temp->id=pChatID;
					
					cout<<"uid="<<temp->user_id<<"  msg="<<temp->msg<<endl;

					//writen(connfd,&temp->id,sizeof(Chat_tocs));
					//broadcast this msg to the all

					mBroadcast(ALL,temp,sizeof(Chat_tocs));
					
			}else if(partyChangeID==id){//get the party change tos
					
					Party_change_tocs *temp=new Party_change_tocs();
					readn(connfd,&temp->error_code,sizeof(Party_change_tocs)-4);
					
					cout<<"get the party change proto"<<endl;

					//if perhaps make the death lock,if someone exit in here
					sem_wait(nummutex);//get the aother party's counter,if it is full,reject,otherwise,change the

					cout<<"come to num shm"<<endl;
					if(BLUE==PersonData::m_Party){
							if(numptr->redCounter>=(MAX_USER/2)){//if another party if full
									Err_toc *temp=new Err_toc(PARTY_IS_FULL);
									writen(connfd,&temp->id,sizeof(Err_toc));
							}else{//change the party
									numptr->blueCounter--;
									numptr->redCounter++;

									//reset the list
									sem_wait(listmutex);

									cout<<"come to list shm in blue"<<endl;
									for(int i=0;i<MAX_USER;i++){
										if(1==listptr->flag[i]&&PersonData::m_ID==listptr->id[i]){
													listptr->party[i]=RED;	
													//should change the PersonData
													PersonData::m_Party=RED;
										}					

									}
									sem_post(listmutex);
									
									updateParty();

									//talk to the client ,he's party is change
									Party_change_tocs *t=new Party_change_tocs();
									writen(connfd,&t->id,sizeof(Party_change_tocs));

							}
					}else if(RED==PersonData::m_Party){
							if(numptr->blueCounter>=(MAX_USER/2)){//if another party if full
									Err_toc *temp=new Err_toc(PARTY_IS_FULL);
									writen(connfd,&temp->id,sizeof(Err_toc));
							}else{//change the party
									numptr->blueCounter++;
									numptr->redCounter--;

									//reset the list
									sem_wait(listmutex);
									cout<<"come to list shm in blue"<<endl;

									for(int i=0;i<MAX_USER;i++){
										if(1==listptr->flag[i]&&PersonData::m_ID==listptr->id[i]){
													listptr->party[i]=BLUE;	
													PersonData::m_Party=BLUE;
										}					

									}
									sem_post(listmutex);

									updateParty();

									//talk to the client ,he's party is change
									Party_change_tocs *t=new Party_change_tocs();
									writen(connfd,&t->id,sizeof(Party_change_tocs));

							}
				}
				sem_post(nummutex);							

			}
				

	}

}

#endif

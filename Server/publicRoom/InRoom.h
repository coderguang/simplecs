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
#include "../struct/PersonData.h"
#include "../struct/ShmServer.h"
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
					
					cout<<"receive chat:uid="<<temp->user_id<<"  msg="<<temp->msg<<" err_code="<<temp->error_code<<endl;
					
					Chat_tocs *chat=new Chat_tocs();
					strcpy(chat->msg,temp->msg);

					cout<<"chat id="<<chat->user_id<<"  msg="<<chat->msg<<" err_code="<<temp->error_code<<endl;

					//writen(connfd,&temp->id,sizeof(Chat_tocs));
					//broadcast this msg to the all

					mBroadcast(ALL,chat,sizeof(Chat_tocs));

					//mBroadcast(ALL,temp,sizeof(Chat_tocs));
					
			}else if(partyChangeID==id){//get the party change tos
					
					Party_change_tocs *temp=new Party_change_tocs();
					readn(connfd,&temp->error_code,sizeof(Party_change_tocs)-4);
					
					cout<<"get the party change proto"<<endl;


					//to avoid the death lock,the mutex order is listmutex-->nummutex;
					//get the listmutex first to avoid the death lock

					sem_wait(listmutex);

					//if perhaps make the death lock,if someone exit in here
					sem_wait(nummutex);//get the aother party's counter,if it is full,reject,otherwise,change the

					cout<<"come to shm"<<endl;
					
					if(BLUE==PersonData::m_Party){

							//cout<<"now he is blue"<<endl;

							if(numptr->redCounter>=(MAX_USER/2)){//if another party if full
								
									//cout<<"can't join red,full!"<<endl;

									Err_toc *temp=new Err_toc(PARTY_IS_FULL);
									writen(connfd,&temp->id,sizeof(Err_toc));
		
									//post the mutex,the order is nummutex-->listmutex
									sem_post(nummutex);
									sem_post(listmutex);		
	
							}else{//change the party

									numptr->blueCounter--;
									numptr->redCounter++;

									//reset the list
									//sem_wait(listmutex); //the mutex order is listmutex-->nummutex to avoid the death lock

									//cout<<"come to list shm in blue"<<endl;

									for(int i=0;i<MAX_USER;i++){
										if(1==listptr->flag[i]&&PersonData::m_ID==listptr->id[i]){
													listptr->party[i]=RED;	
													//should change the PersonData
													PersonData::m_Party=RED;
													cout<<"change to red"<<endl;
										}					

									}

									sem_post(nummutex);
									sem_post(listmutex);
									
									updateParty();//this need the listmutex,so must post before this


									//talk to the client ,he's party is change
									Party_change_tocs *t=new Party_change_tocs();
									writen(connfd,&t->id,sizeof(Party_change_tocs));

							}
					}else if(RED==PersonData::m_Party){
							if(numptr->blueCounter>=(MAX_USER/2)){//if another party if full
									Err_toc *temp=new Err_toc(PARTY_IS_FULL);
									writen(connfd,&temp->id,sizeof(Err_toc));
									
									sem_post(nummutex);
									sem_post(listmutex);


							}else{//change the party
									numptr->blueCounter++;
									numptr->redCounter--;

									//reset the list
								//	sem_wait(listmutex);
									//cout<<"come to list shm in red"<<endl;

									for(int i=0;i<MAX_USER;i++){
										if(1==listptr->flag[i]&&PersonData::m_ID==listptr->id[i]){
													listptr->party[i]=BLUE;	
													PersonData::m_Party=BLUE;
													cout<<"change to Blue"<<endl;
				
										}					

									}

									sem_post(nummutex);
									sem_post(listmutex);

									updateParty();

									//talk to the client ,he's party is change
									Party_change_tocs *t=new Party_change_tocs();
									writen(connfd,&t->id,sizeof(Party_change_tocs));

							}
				}else{//if get something wrong and didn't cast any befor,post the mutex

							cout<<"didn't match any party!"<<endl;
							sem_post(nummutex);
							sem_post(listmutex);
				}

			}else if(gameStartID==id){//receive the start game proto


				GameStart_tocs *temp=new GameStart_tocs();

				readn(connfd,&temp->error_code,sizeof(GameStart_tocs)-4);

				if(1000==PersonData::m_ID){//check if this proto from sg

					//cout<<"receive the game start from sg"<<endl;
					//change ths game status
						
					
					sem_wait(statusmutex);
					//cout<<"get the status mutex"<<endl;
					statusptr->status=IN_GAME;
					//cout<<"set the status mutex"<<endl;
					sem_post(statusmutex);

					//broadcast the GameStart_tocs to every client
					//
					//
					//Chat_tocs *t=new Chat_tocs(1000,ALL,"game start after 10 seconds");
				
					//mBroadcast(ALL,t,sizeof(Chat_tocs));

					
					for(int i=0;i<40;i++){
						string str="game start after seconds  ";
						str+=IntToStr(i);
						Chat_tocs *t=new Chat_tocs(1000,ALL,str);
						mBroadcast(ALL,t,sizeof(Chat_tocs));
						DelayTime(5);
					 }

					DelayTime(10);

					mBroadcast(ALL,temp,sizeof(GameStart_tocs));
					
				}

			}else{//some error sream ,receive it and do nothing
					char buf[128];
					readn(connfd,&buf,128);


			}
				

	}

}

#endif

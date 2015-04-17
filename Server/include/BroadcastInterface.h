#ifndef BROARDCAST_INTERFACE_H_
#define BROARDCAST_INTERFACE_H_

//this is using for broardcast
//it have 3 arguments
//type: it decide this proto broardcast to who,blue or red or all
//proto: this it the proto
//len: the size of the proto

#include "struct/shmServer.h"
#include "../lanuch/Rdwr.h"
#include "../proto/Message.h"
#include "InitFirst.h"


using namespace std;

//use InitFirst functions to instead it's own init functions

static const int BLUE=1;
static const int RED=2;
static const int ALL=3; 

extern struct shmList *listptr;
extern struct shmNum *numptr;
extern sem_t *listmutex;
extern sem_t *nummutex;

//make a for loop to get the shmList's socket fd,check it flag does't it value or not
void mBroadcast(int type,Message	*msg,size_t len){
			

			sem_wait(listmutex);			
			cout<<"come to the broadcast"<<endl;
			/**
			for(int i=0;i<MAX_USER;i++){
				cout<<"in cast:i="<<i<<" flag="<<listptr->flag[i]<<" id="<<listptr->id[i]<<" pid="<<listptr->pid[i]<<endl;
			}**/

			if(BLUE==type){  //if this should be broadcast to blue party
						for(int i=0;i<MAX_USER;i++){
								if(1==listptr->flag[i]){  //if this is value
										if(BLUE==listptr->party[i]){
													writen(listptr->conn[i],msg,len);	//broadcast this proto to the socket fd;
											}	
								}
						}
			}else if(RED==type){  //if this should be broadcast to red party
						for(int i=0;i<MAX_USER;i++){
								if(1==listptr->flag[i]){  //if this is value
										if(RED==listptr->party[i]){
													writen(listptr->conn[i],msg,len);	//broadcast this proto to the socket fd;
											}	
								}
						}
			}else if(ALL==type){  //if this should be broadcast to blue party
						for(int i=0;i<MAX_USER;i++){
								if(1==listptr->flag[i]){  //if this is value
													writen(listptr->conn[i],msg,len);	//broadcast this proto to the socket fd;
								}	

						}
			}						
		
			sem_post(listmutex);
						
			cout<<"out of broadcast"<<endl;
}
		










#endif


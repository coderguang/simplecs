#ifndef BROARDCAST_INTERFACE_H_
#define BROARDCAST_INTERFACE_H_

//this is using for broardcast
//it have 3 arguments
//type: it decide this proto broardcast to who,blue or red or all
//proto: this it the proto
//len: the size of the proto

#include "strcut/shmServer.h"

using namespace std;

//before use this broadcast,must init it first by belown functions

static struct shmList *listPtr=nullptr;
static sem_t *listSem=nullptr;

static void InitBroadcast(){
		
		int fd;
		
		fd=shm_open("mshmList",O_RDWR,0644);
		
		if(fd<0){
				cout<<"when init the broadcast interface ,open the share memory failed!"<<endl;
		}
		
		listPtr=(struct shmList*)mmap(NULL,sizeof(struct shmList),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

		close(fd);

		listSem=sem_open("msemList",0);

}


static const int BLUE=1;
static const int RED=2;
static const int ALL=3; 


//make a for loop to get the shmList's socket fd,check it flag does't it value or not
static void mBroadcast(int type,Message *msg,int len){
			
			if(BLUE==type){  //if this should be broadcast to blue party
						for(int i=0;i<MAX_USER;i++){
								if(1==listPtr->flag[i]){  //if this is value
										if(BLUE==listPtr->party[i]){
													writen(listPtr->conn,msg,len);	//broadcast this proto to the socket fd;
											}	
								}
						}
			}else if(RED==type){  //if this should be broadcast to red party
						for(int i=0;i<MAX_USER;i++){
								if(1==listPtr->flag[i]){  //if this is value
										if(RED==listPtr->party[i]){
													writen(listPtr->conn,msg,len);	//broadcast this proto to the socket fd;
											}	
								}
						}
			}else if(ALL==type){  //if this should be broadcast to blue party
						for(int i=0;i<MAX_USER;i++){
								if(1==listPtr->flag[i]){  //if this is value
													writen(listPtr->conn,msg,len);	//broadcast this proto to the socket fd;
								}	

						}
			}						
						
}
		










#endif


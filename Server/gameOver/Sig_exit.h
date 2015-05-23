#ifndef SIG_EXIT_H_
#define SIG_EXIT_H_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include "../include/OpenShm.h"
#include "../struct/ShmServer.h"
#include "../myDB/dbcpp/DBInterface.h"
#include "../publicRoom/UpdateParty.h"
#include "../include/InitGameStatus.h"

/**
static struct shmList *sigList=nullptr;
static sem_t *sigListmutex=nullptr;

static struct shmNum *sigNum=nullptr;
static sem_t *sigNummutex=nullptr;
**/

struct shmList *sigList=nullptr;
sem_t *sigListmutex=nullptr;

struct shmNum *sigNum=nullptr;
sem_t *sigNummutex=nullptr;

extern struct shmStatus *statusptr;
extern sem_t *statusmutex;

void InitExit(){
		int fd;
		
		fd=shm_open("mshmList",O_RDWR,0644);
		if(fd<0){
			cout<<"open mshmList failed when init the sig_exit"<<endl;
		}
	
		sigList=(struct shmList*)mmap(NULL,sizeof(struct shmList),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		
		close(fd);

		sigListmutex=sem_open("msemList",0);

		if(SEM_FAILED==sigListmutex){
			cout<<"open msemList failed when init the sig_exit"<<endl;
		}

		
		int fdd;
		
		fdd=shm_open("mshmNum",O_RDWR,0644);
		if(fdd<0){
			cout<<"open mshmNum failed when init the sig_exit"<<endl;
		}
	
		sigNum=(struct shmNum*)mmap(NULL,sizeof(struct shmNum),PROT_READ|PROT_WRITE,MAP_SHARED,fdd,0);
		
		close(fdd);

		sigNummutex=sem_open("msemNum",0);

		if(SEM_FAILED==sigNummutex){
			cout<<"open msemNum failed when init the sig_exit"<<endl;
		}


		//init the status
		InitGameStatus();

}


//the child process exit functions
void sig_chld_exit(int signo){

	pid_t pid;
	int stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0){
			
			//change the share memory 
			cout<<"child "<<pid<<"  terminated!"<<endl;

			sem_wait(sigListmutex);

			for(int i=0;i<MAX_USER;i++){
				 if(1==sigList->flag[i]&&int(pid)==sigList->pid[i]){
							cout<<"the id="<<sigList->id[i]<<" exit!"<<endl;
							ExitLanuch(sigList->id[i]); //change the db status
		
							//change the party data
							sem_wait(sigNummutex);
							sigNum->counter--;

							if(BLUE==sigList->party[i])
								sigNum->blueCounter--;
							else if(RED==sigList->party[i])
								sigNum->redCounter--;
								
							if(0==sigNum->counter){
								sem_wait(statusmutex);
								statusptr->status=IN_ROOM;
								sem_post(statusmutex);
							}
								
							sem_post(sigNummutex);

							//reset all things
							sigList->flag[i]=0; //flag this free
							sigList->id[i]=0;
							sigList->pid[i]=0;
							sigList->conn[i]=0;
							sigList->party[i]=0;

							break;
				}


		}

		sem_post(sigListmutex);

		//if the game status is 1(in the public room ,it should be update the Party)

		sem_wait(mstatusmutex);
		if(IN_ROOM==mstatusptr->status){
				//cout<<"update when exit"<<endl;
				updateParty();
		}else{
				//cout<<"status ="<<mstatusptr->status<<endl;
		}
		sem_post(mstatusmutex);

	}
	
	
	cout<<"out of the sig_exit!"<<endl;
	//return ;

}

#endif


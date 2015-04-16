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
#include "openShm.h"
#include "../include/struct/shmServer.h"
#include "../MyDB/dbcpp/DBInterface.h"

//the child process exit functions



void sig_chld_exit(int signo){

	pid_t pid;
	int stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0){
	//change the share memory 
			int fd;
			struct shmNum *shmptr;
			sem_t *mutex;

			fd=shm_open("mshmNum",O_RDWR,0644);
			if(fd<0){
					cout<<"can't open mshmNum failed!"<<endl;
			}

			shmptr=(struct shmNum*)mmap(NULL,sizeof(struct shmNum),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		
			close(fd);
			
			mutex=sem_open("msemNum",0);
			sem_wait(mutex);
			shmptr->counter--;
			sem_post(mutex);


			cout<<"child "<<pid<<"  terminated!"<<endl;

			int fdd;
			
			struct shmList *listptr;
		
			sem_t *lmutex;

			fdd=shm_open("mshmList",O_RDWR,0644);
			if(fdd<0){
					cout<<"can't open mshmList failed!"<<endl;
			}
			
			listptr=(struct shmList*)mmap(NULL,sizeof(struct shmList),PROT_READ|PROT_WRITE,MAP_SHARED,fdd,0);
		
			close(fdd);

			lmutex=sem_open("msemList",0);
			
			sem_wait(lmutex);
			for(int i=0;i<MAX_USER;i++){
				 if(1==listptr->flag[i]&&(int)pid==listptr->pid[i]){
							cout<<"the id="<<listptr->id[i]<<" exit!"<<endl;
							ExitLanuch(listptr->id[i]); //change the db status
		
							//reset all things
							listptr->flag[i]=0; //flag this free
							listptr->id[i]=0;
							listptr->pid[i]=0;
							listptr->conn[i]=0;
							listptr->party[i]=0;
						
					}				


			}
			sem_post(lmutex);

	}
	
	
	return ;

}

#endif


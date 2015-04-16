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
#include "../include/InitFirst.h"


//the child process exit functions
void sig_chld_exit(int signo){

	pid_t pid;
	int stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0){
	//change the share memory 
	
			sem_wait(nummutex);
			numptr->counter--;
			sem_post(nummutex);


			cout<<"child "<<pid<<"  terminated!"<<endl;

			sem_wait(listmutex);
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
			sem_post(listmutex);

	}
	
	
	return ;

}

#endif


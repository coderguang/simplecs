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
			cout<<"child "<<pid<<"  terminated!"<<endl;

			sem_wait(listmutex);
			cout<<"to the exit list inner"<<endl;

			for(int i=0;i<MAX_USER;i++){

				 //cout<<"flag["<<i<<"]="<<listptr->flag[i]<<"  id="<<listptr->id[i]<<"  pid="<<pid<<" conn="<<listptr->conn[i]<<" party="<<listptr->party[i]<<endl;
				 cout<<"flag["<<i<<"]="<<listptr->flag[i]<<"  id="<<listptr->id[i]<<"  pid="<<pid<<endl;
				 if(pid==listptr->pid[i]){
						cout<<"pid==list->pid"<<endl;
				}else{
						cout<<"pid!=list->pid"<<endl;
				}
				 if(1==listptr->flag[i]&&(int)pid==listptr->pid[i]){
							cout<<"the id="<<listptr->id[i]<<" exit!"<<endl;
							ExitLanuch(listptr->id[i]); //change the db status
		
							//change the party data
							sem_wait(nummutex);
							numptr->counter--;

							if(BLUE==listptr->party[i])
								numptr->blueCounter--;
							else if(RED==listptr->party[i])
								numptr->redCounter--;

							sem_post(nummutex);

							//reset all things
							listptr->flag[i]=0; //flag this free
							listptr->id[i]=0;
							listptr->pid[i]=0;
							listptr->conn[i]=0;
							listptr->party[i]=0;

							break;
					}				


			}
		sem_post(listmutex);

	}
	
	
	return ;

}

#endif


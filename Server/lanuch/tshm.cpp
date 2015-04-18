#ifndef INIT_FIRST_H_
#define INIT_FIRST_H_

/**  Init the sharememory pointer and semphore at here
 *	 other functions all use this static pointer and semphore
 *
 *
 * **/

#include "../struct/ShmServer.h"
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <iostream>
using namespace std;

/**
static struct shmList *listptr=nullptr;
static sem_t  *listmutex=nullptr;

static struct shmNum *numptr=nullptr;
static sem_t *nummutex=nullptr;
**/


int main(){

		struct shmList *listptr=nullptr;
		sem_t  *listmutex=nullptr;

		struct shmNum *numptr=nullptr;
		sem_t *nummutex=nullptr;
		//open shmList 
		int fd;
		
		fd=shm_open("mshmList",O_RDWR,0644);

		if(fd<0){
			cout<<"open mshmList failed when init"<<endl;
		}

		listptr=(struct shmList*)mmap(NULL,sizeof(struct shmList),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		close(fd);
		listmutex=sem_open("msemList",0);
		if(SEM_FAILED==listmutex){
			cout<<"open msemList failed when init"<<endl;
		}


		//init the list array
		//
		
		cout<<"now the list is "<<endl;

		sem_wait(listmutex);
		for(int i=0;i<MAX_USER;i++){
			cout<<"flag["<<i<<"]="<<listptr->flag[i]<<"  id="<<listptr->id[i]<<"  pid="<<listptr->pid[i]<<" conn="<<listptr->conn[i]<<endl;
		}
		sem_post(listmutex);
		

		//open shmNum 
		
		int fdd;
		
		fdd=shm_open("mshmNum",O_RDWR,0644);

		if(fdd<0){
			cout<<"open mshmNum failed when init"<<endl;
		}

		numptr=(struct shmNum*)mmap(NULL,sizeof(struct shmNum),PROT_READ|PROT_WRITE,MAP_SHARED,fdd,0);
		close(fdd);
		nummutex=sem_open("msemNum",0);
		
		if(SEM_FAILED==nummutex){
			cout<<"open msemNum failed when init"<<endl;
		}

		sem_wait(nummutex);
		cout<<"sum="<<numptr->counter<<" blue="<<numptr->blueCounter<<" red="<<numptr->redCounter<<endl;
		sem_post(nummutex);


}






#endif

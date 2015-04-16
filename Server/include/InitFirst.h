#ifndef INIT_FIRST_H_
#define INIT_FIRST_H_

/**  Init the sharememory pointer and semphore at here
 *	 other functions all use this static pointer and semphore
 *
 *
 * **/

#include "struct/shmServer.h"
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <iostream>
using namespace std;


static struct shmList *listptr=nullptr;
static sem_t  *listmutex=nullptr;

static struct shmNum *numptr=nullptr;
static sem_t *nummutex=nullptr;



static void InitFirst(){
		//open shmList 
		int fd;
		
		fd=shm_open("mshmList",O_RDWR,0644);

		if(fd<0){
			cout<<"open mshmList when init"<<endl;
		}

		listptr=(struct shmList*)mmap(NULL,sizeof(struct shmList),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		close(fd);
		listmutex=sem_open("msemList",0);

		//open shmNum 
		int fdd;
		
		fdd=shm_open("mshmNum",O_RDWR,0644);

		if(fdd<0){
			cout<<"open mshmNum when init"<<endl;
		}

		numptr=(struct shmNum*)mmap(NULL,sizeof(struct shmNum),PROT_READ|PROT_WRITE,MAP_SHARED,fdd,0);
		close(fdd);
		nummutex=sem_open("msemNum",0);
		
	

}






#endif

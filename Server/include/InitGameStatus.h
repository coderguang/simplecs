#ifndef INIT_GAME_STATUS_H_
#define INIT_GAME_STATUS_H_
#include "../struct/ShmServer.h"
#include <iostream>
using namespace std;


struct shmStatus *mstatusptr=nullptr;
sem_t *mstatusmutex=nullptr;


void InitGameStatus(){

	int fd;
	fd=shm_open("mshmStatus",O_RDWR,0644);

	if(fd<0){
		cout<<"open the shmStatus failed when init the game status"<<endl;
	}
	
	mstatusptr=(struct shmStatus*)mmap(NULL,sizeof(struct shmStatus),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

	close(fd);

	mstatusmutex=sem_open("msemStatus",0);
	
	if(SEM_FAILED==mstatusmutex){
		cout<<"open msemStatus failed when init the game status"<<endl;
	}


	sem_wait(mstatusmutex);
	mstatusptr->status=IN_ROOM;//the first status is IN_ROOM
	//mstatusptr->status=IN_GAME;//test the client error show
	sem_post(mstatusmutex);




}

#endif

#ifndef OPEN_SHM_H_
#define OPEN_SHM_H_

#include "../include/struct/shmServer.h"

using namespace std;


//this function is using for create&open the mshmNum and mshmList share memory
//and create&open semaphore msemNum  and msemList
void openShmFunc(){
	
//open mshmNum and msemNum
	int fd;
	
	struct shmNum *ptr;
	
	//if exists,unlink it
	shm_unlink("mshmNum");

	fd=shm_open("mshmNum",O_RDWR|O_CREAT|O_EXCL,0644);

	if(fd<0){
		cout<<"open mshmNum share memory failed! in openShm.h"<<endl;
	}
	
	ftruncate(fd,sizeof(struct shmNum));
	ptr=(struct shmNum*)mmap(NULL,sizeof(struct shmNum),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

	close(fd);

	sem_t *mutex;

	sem_unlink("msemNum");

	mutex=sem_open("msemNum",O_CREAT|O_EXCL,0644,1);//init it only 1 resources

	sem_close(mutex);	
	
	

//open mshmList and msemList
	int fdd;
	
	struct shmList *pptr;
	
	//if exists,unlink it
	shm_unlink("mshmList");

	fdd=shm_open("mshmList",O_RDWR|O_CREAT|O_EXCL,0644);

	if(fdd<0){
		cout<<"open mshmList share memory failed! in openShm.h"<<endl;
	}
	
	ftruncate(fdd,sizeof(struct shmList));
	pptr=(struct shmList*)mmap(NULL,sizeof(struct shmList),PROT_READ|PROT_WRITE,MAP_SHARED,fdd,0);

	close(fdd);

	sem_t *mmutex;

	sem_unlink("msemList");

	mmutex=sem_open("msemList",O_CREAT|O_EXCL,0644,1);//init it only 1 resources

	sem_close(mmutex);	

	cout<<"open shmServer complete!"<<endl;

}







#endif

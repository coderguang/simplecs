#ifndef OPEN_SHM_H_
#define OPEN_SHM_H_

#include "../struct/ShmServer.h"

using namespace std;


//this function is using for create&open the mshmNum and mshmList share memory
//and create&open semaphore msemNum  and msemList
static void openShmFunc(){
	
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



//open mshmStatus and msemStatus
	int fddd;
	
	struct shmStatus *ppptr;
	
	//if exists,unlink it
	shm_unlink("mshmStatus");

	fddd=shm_open("mshmStatus",O_RDWR|O_CREAT|O_EXCL,0644);

	if(fddd<0){
		cout<<"open mshmStatus share memory failed! in openShm.h"<<endl;
	}
	
	ftruncate(fddd,sizeof(struct shmStatus));
	ppptr=(struct shmStatus*)mmap(NULL,sizeof(struct shmStatus),PROT_READ|PROT_WRITE,MAP_SHARED,fddd,0);

	close(fddd);

	sem_t *mmmutex;

	sem_unlink("msemStatus");

	mmmutex=sem_open("msemStatus",O_CREAT|O_EXCL,0644,1);//init it only 1 resources

	sem_close(mmmutex);	

//open the netmutex sem
	
	sem_t *netmutex;
	sem_unlink("netmutex");
	
	netmutex=sem_open("netmutex",O_CREAT|O_EXCL,0644,1); //this is when a process write proto to client 
	
	sem_close(netmutex);
	

	cout<<"open shmServer complete in openShm.h!"<<endl;


}







#endif

#include <iostream>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <queue>
#include "Logger.h"
#include "struct/shmLog.h"
/**
 *this is the log process,the server only this one log process
 *user Posix shm and the sem
 *more  producer and only one comsumer.
 *author:coderguang
 *date:2015/04/08
 */
using namespace std;


int main(int argc,char **argv){
	int fd;
	int index;//the last msg index in msgdata
	
	struct shmLogMsg *ptr;

	//delete the share memory if it exist!
	shm_unlink("mlogShm");
	
	fd=shm_open("mlogShm",O_RDWR|O_CREAT|O_EXCL,0644);
	
	if(fd<0){
		cout<<"create log share memory faild!"<<endl;
	}
	
	
	
	//ptr=(queue<mLogMsg>*)mmap(NULL,sizeof(mLogMsg)*MAXLOGQUEUE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	ptr=(shmLogMsg*)mmap(NULL,sizeof(shmLogMsg),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

	ftruncate(fd,sizeof(struct shmLogMsg));

	close(fd);

	/*init the array of offset*/
	for(index=0;index<MAXMSG;index++){
		ptr->msgoff[index]=index*MSGSIZE;
	}

 /*init the semaphore in share memory*/
	
	sem_init(&ptr->mutex,1,1);
	sem_init(&ptr->nempty,1,MAXMSG);
	sem_init(&ptr->nstored,1,0);

	/*this is the consumer*/

	index=0;
	while(true){
		sem_wait(&ptr->nstored);
		sem_wait(&ptr->mutex);
		long offset=ptr->msgoff[index];
		
		printf("index=%d: %s\n",index,&ptr->msgdata[offset]);
		string ms=(string)&ptr->msgdata[offset];
		Logger::GetInstance()->Log(ptr->type[offset],ptr->level[offset],ms);
		
		if(++index>=MAXMSG)
				index=0;
		
		sem_post(&ptr->mutex);
		sem_post(&ptr->nempty);


	}
	exit(0);


}
/**
 				sem_unlink("mlogMutex");
        sem_unlink("mlogProducer");
        sem_unlink("mlogComsumer");
*/

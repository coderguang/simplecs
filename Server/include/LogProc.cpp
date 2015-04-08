#include <iostream>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <queue>
#include "Logger.h"
/**
 *this is the log process,the server only this one log process
 *user Posix shm and the sem
 *more  producer and only one comsumer.
 *author:coderguang
 *date:2015/04/08
 */
using namespace std;

//the queue elements
struct mLogMsg{
	LogType type;
	Level level;
	string msg;
};
const int MAXLOGQUEUE=100;
queue<mLogMsg> logQue;//the log queue in share memory

struct shared{
	sem_t *mmutex;//producer's semaphore when it push msg to queue
	sem_t *producer;//it will post when producer works
	sem_t *comsumer;//it will post when comsumer works

};

int main(int argc,char **argv){
	int fd;
	queue<mLogMsg> *ptr;
	
	//delete the share memory if it exist!
	shm_unlink("mlogShm");
	
	fd=shm_open("mlogShm",O_RDWR|O_CREAT|O_EXCL,0644);
	
	if(fd<0){
		cout<<"create log share memory faild!"<<endl;
	}
	
	
	ftruncate(fd,sizeof(mLogMsg)*MAXLOGQUEUE);
	
	ptr=(queue<mLogMsg>*)mmap(NULL,sizeof(mLogMsg)*MAXLOGQUEUE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

	close(fd);

	
	sem_unlink("mlogMutex");
	sem_unlink("mlogProducer");
	sem_unlink("mlogComsumer");
	
	shared sharedSem;
	sharedSem.mmutex=sem_open("mlogMutex",O_CREAT|O_EXCL,0644,1);
	sharedSem.producer=sem_open("mlogProducer",O_CREAT|O_EXCL,0644,0);
	sharedSem.comsumer=sem_open("mlogComsumer",O_CREAT|O_EXCL,0644,MAXLOGQUEUE);

	//comsumer works
	while(true){
		sem_wait(sharedSem.producer);//wait the producer's push msg to the queue
		mLogMsg temp=ptr->front();//get the front 
		Logger::GetInstance()->Log(temp.type,temp.level,temp.msg);//push it to the background thread's queue
		ptr->pop();
		sem_post(sharedSem.comsumer);
	}


}

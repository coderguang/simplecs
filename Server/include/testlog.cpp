#include <iostream>
#include <unistd.h>
#include "LogInterface.h"
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "Func.h"
//#include "Logger.h"
using namespace std;


struct mLogMsg{
	LogType type;
	Level level;
	string msg;
};
//const int MAXLOGQUEUE=100;
//queue<mLogMsg> logQue;

struct shared{
	sem_t *mmutex;
	sem_t *producer;
	sem_t *comsumer;
};

int main(){
	int fd;
	//queue<mLogMsg> *ptr;
	mLogMsg *ptr;
	
	fd=shm_open("mlogShm",O_RDWR,0644);
	if(fd<0)
		cout<<"open share memory faild"<<endl;
	
	//ptr=(queue<mLogMsg>*)mmap(NULL,sizeof(mLogMsg)*MAXLOGQUEUE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	ptr=(mLogMsg*)mmap(NULL,sizeof(mLogMsg),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	
	close(fd);
	
	shared sharedSem;
	sharedSem.mmutex=sem_open("mlogMutex",O_RDWR);
	sharedSem.producer=sem_open("mlogProducer",O_RDWR);
	sharedSem.comsumer=sem_open("mlogComsumer",O_RDWR);

	pid_t pid;

	for(int i=0;i<4;i++){
		//if(fork()==0){
			pid=getpid();
			cout<<"come to fork "<<pid<<endl;
			sem_wait(sharedSem.comsumer);
			sem_wait(sharedSem.mmutex);
			string ms="i";
			ms+=IntToStr((int)pid);
			//mLogMsg temp={DBLog,ERROR,ms};
			//ptr=new mLogMsg{DBLog,ERROR};
			ptr->type=DBLog;
			ptr->level=ERROR;
			ptr->msg=ms;
			//ptr->push(temp);
			cout<<"push success"<<endl;
			sem_post(sharedSem.mmutex);
			sem_post(sharedSem.producer);
		//}
	}
		

}

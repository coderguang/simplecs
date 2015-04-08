#include <iostream>
#include <unistd.h>
#include <string.h>
#include "LogInterface.h"
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "Func.h"
#include "struct/shmLog.h"
using namespace std;

int main(){
	int fd;
	
	pid_t pid;	
	struct shmLogMsg *ptr;
	

	fd=shm_open("mlogShm",O_RDWR,0644);
	if(fd<0)
		cout<<"open share memory faild"<<endl;
	
	ptr=(shmLogMsg*)mmap(NULL,sizeof(shmLogMsg),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	
	close(fd);
	

	for(int i=0;i<4;i++){
		//if(fork()==0){
			pid=getpid();
			char mesg[MSGSIZE];
			//snprintf(mesg,MSGSIZE,"",(long)pid,i,DBLog,ERROR);
			
			sem_wait(&ptr->nempty);
			sem_wait(&ptr->mutex);
			
			long offset=ptr->msgoff[ptr->nput];

			if(++(ptr->nput)>=MAXMSG)	
				ptr->nput=0;
			
			sem_post(&ptr->mutex);
			ptr->type[offset]=DBLog;
			ptr->level[offset]=FATAL;
			string s="hello";
			s+=IntToStr((int)pid);
			strcpy(&ptr->msgdata[offset],s.c_str());
			sem_post(&ptr->nstored);

		//	exit(0);

		//}
		
	}
	//exit(0);
	while(true)
		;
		

}

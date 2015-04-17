#ifndef LOG_INTERFACE_H_
#define LOG_INTERFACE_H_
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../struct/shmLog.h"
#include "LogConstant.h"
#include <iostream>
#include <string.h>
using namespace std;
/**
 *all user process use this interface to log msg
 *author:coderguagn
 *date:2015/04/09
 */

static shmLogMsg *ptr;

static void InitLog(){

	int fd;
	fd=shm_open("mlogShm",O_RDWR,0644);
	if(fd<0)
		cout<<"open log share memory faild"<<endl;
	
	ptr=(shmLogMsg*)mmap(NULL,sizeof(shmLogMsg),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	
	close(fd);

}
//before call the Log,must call the InitLog before
static void Log(LogType type,Level level,string msg){
	
	sem_wait(&ptr->nempty);
	sem_wait(&ptr->mutex);

	long offset=ptr->msgoff[ptr->nput];
	
	if(++(ptr->nput)>=MAXMSG)
		ptr->nput=0;

	ptr->type[offset]=type;
	ptr->level[offset]=level;
	strcpy(&ptr->msgdata[offset],msg.c_str());
	
	sem_post(&ptr->mutex);	
	sem_post(&ptr->nstored);
	

	
	
}

#endif 

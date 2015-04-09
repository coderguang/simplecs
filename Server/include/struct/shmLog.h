#ifndef SHM_LOG_
#define SHM_LOG_
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../LogConstant.h"

/**
 *the share memory struct
 *use for the log process
 *autho:coderguang
 *date:2015/04/08
 *
 *
 */

const int MSGSIZE=256;//the msg max size
const int MAXMSG=32;//the max msg counter

struct shmLogMsg{
	sem_t mutex;	//the mutex
	sem_t nempty;	//the queue empty semaphore
	sem_t nstored;	//the queue had stored
	
	int nput;	//index into msgoff[]  for next put
	
	long msgoff[MAXMSG];	//offset in shared memory of each message
	LogType type[MAXMSG];	//the message type
	Level level[MAXMSG];	//the message level
	char msgdata[MSGSIZE*MAXMSG];	//the actual message


};


#endif

#ifndef SHM_SERVER_
#define SHM_SERVER_
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../LogConstant.h"

/**
 *the share memory struct
 *use for the server user counter
 *autho:coderguang
 *date:2015/04/15
 *
 *
 */

static const int MAX_USER=10;

struct shmNum{
	int counter;	//the server user counter;
	int blueCounter; // the blue party counter;
	int redCounter;	//the red party counter
};

struct shmList{
	int flag[MAX_USER]; //flag this [] is using or not,set by lanuch loop for 1 and exit process for 0
	int id[MAX_USER];		// the accounts id,set by lanuch loop
	int pid[MAX_USER];	//the user process pid ,set by lanuch loop
	int conn[MAX_USER];	//the user process socket fd
	int party[MAX_USER];	//the user party
	//pid_t pid[MAX_USER];

};


#endif

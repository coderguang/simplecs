#ifndef UPDATE_PARTY_H_
#define UPDATE_PARTY_H_
#include "struct/shmServer.h"
#include "../proto/Party_toc.h"
#include "BroadcastInterface.h"

//this functions is use to update the party when in the publicroom

static struct shmList *uptr;
static sem_t *umutex;

//when use updateParty,must use initUpateParty first

static void initUpdateParty(){
	int fd;
	fd=shm_open("mshmList",O_RDWR,0644);
	
	if(fd<0){
			cout<<"open mshmList failed when use init update party"<<endl;
	}
	
	uptr=(struct shmList*)mmap(NULL,sizeof(struct shmList),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);

	close(fd);

	umutex=sem_open("msemList",0);

}



static void updateParty(){
	int iblue=0; //the blue[] index
	int ired=0; //the red[] index
	
	Party_toc *temp=new Party_toc();
	
	sem_wait(umutex);

	for(int i=0;i<MAX_USER;i++){
		if(1==uptr->flag[i]){
				if(BLUE==uptr->party[i]){
					temp->blue[iblue++]=uptr->id[i]; //get the id to the party blue[] 
					continue;
				}else if(RED==uptr->party[i]){
					temp->red[ired++]=uptr->id[i];
					continue;
				}					
		}

	}
	sem_post(umutex);
	
	//full the other []
	
	while(iblue<(MAX_USER/2)){
			temp->blue[ibule++]=0;
	}

	while(ired<(MAX_USER/2)){
			temp->ired[ired++]=0;
	}
	
	//broadcast this to the all
	//
	mBroadcast(ALL,&temp->id,sizeof(Party_toc));


}









#endif

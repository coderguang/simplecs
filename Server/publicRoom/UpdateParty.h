#ifndef UPDATE_PARTY_H_
#define UPDATE_PARTY_H_
#include "../struct/ShmServer.h"
#include "../proto/Party_toc.h"
#include "../include/BroadcastInterface.h"
#include "../include/InitFirst.h"


extern struct shmList *listptr;
extern struct shmNum *numptr;

extern sem_t *listmutex;
extern sem_t *nummutex;


void updateParty(){
	int iblue=0; //the blue[] index
	int ired=0; //the red[] index
	
	Party_toc *temp=new Party_toc();
	
	sem_wait(listmutex);

	for(int i=0;i<MAX_USER;i++){
		if(1==listptr->flag[i]){
				if(BLUE==listptr->party[i]){
					temp->blue[iblue++]=listptr->id[i]; //get the id to the party blue[] 
					continue;
				}else if(RED==listptr->party[i]){
					temp->red[ired++]=listptr->id[i];
					continue;
				}					
		}

	}
	sem_post(listmutex);
	
	//full the other []
	
	while(iblue<(MAX_USER/2)){
			temp->blue[iblue++]=0;
	}

	while(ired<(MAX_USER/2)){
			temp->red[ired++]=0;
	}
	
	//broadcast this to the all
	//
	mBroadcast(ALL,temp,sizeof(Party_toc));


}









#endif

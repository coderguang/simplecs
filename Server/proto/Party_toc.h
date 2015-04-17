#ifndef PARTY_TOC_H_
#define PARTY_TOC_H_

#include "Message.h"
#include "ProtoID.h"
#include "../struct/ShmServer.h" //for MAX_USER;

#pragma pack(1)
class Party_toc:public Message{
public:
	//the party list id
	/**
	int r1;	
	int r2;
	int r3;
	int r4;
	int r5;

	int b1;
	int b2;
	int b3;
	int b4;
	int b5;
	**/
	
	
	int red[MAX_USER/2];
	int blue[MAX_USER/2];

	 Party_toc(){
			id=partyID;
			error_code=0;
	}

	Party_toc(int rr1,int rr2,int rr3,int rr4,int rr5,int bb1,int bb2,int bb3,int bb4,int bb5){

		id=partyID;
		error_code=0;

		red[0]=rr1;
		red[1]=rr2;
		red[2]=rr3;
		red[3]=rr4;
		red[4]=rr5;
		
		blue[0]=bb1;
		blue[1]=bb2;
		blue[2]=bb3;
		blue[3]=bb4;
		blue[4]=bb5;

		/**
		r1=rr1;
		r2=rr2;
		r3=rr3;
		r4=rr4;
		r5=rr5;

		b1=bb1;
		b2=bb2;
		b3=bb3;
		b4=bb4;
		b5=bb5;
		**/
	}


};




#endif

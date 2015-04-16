#ifndef PARTY_TOC_H_
#define PARTY_TOC_H_

#include "Message.h"
#include "protoID.h"

#pragma pack(1)
class Party_toc:public Message{
public:
	//the party list id
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

	 Party_toc(){
			id=partyID;
			error_code=0;
	}

};




#endif

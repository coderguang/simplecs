#ifndef PARTY_CHANGE_TOCS_H_
#define PARTY_CHANGE_TOCS_H_
#include "Message.h"

#pragma pack(1)

class Party_change_tocs:public Message{

public:
		Party_change_tocs(){
				id=partyChangeID;
				error_code=0;
		}



};





#endif


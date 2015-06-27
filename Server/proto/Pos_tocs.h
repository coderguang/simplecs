#ifndef POS_TOCS_H_
#define POS_TOCS_H_
#include "Message.h"

#pragma pack(1)
class Pos_tocs:public Message{
public:
	int userID;
	int x;
	int y;
	int z;
	
};





#endif

#ifndef GAME_START_TOCS_H_
#define GAME_START_TOCS_H_

#include "Message.h"

#pragma pack(1)
class GameStart_tocs:public Message{

public:
	GameStart_tocs(){
		id=gameStartID;
		error_code=0;
	}


};



#endif

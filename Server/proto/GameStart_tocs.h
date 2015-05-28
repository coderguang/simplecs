#ifndef GAME_START_TOCS_H_
#define GAME_START_TOCS_H_

#include "Message.h"

#pragma pack(1)
class GameStart_tocs:public Message{

public:
	int r1=0;
	int r2=0;
	int r3=0;
	int r4=0;
	int r5=0;
	
	int b1=0;
	int b2=0;
	int b3=0;
	int b4=0;
	int b5=0;


	GameStart_tocs(){
		id=gameStartID;
		error_code=0;
	}


};



#endif

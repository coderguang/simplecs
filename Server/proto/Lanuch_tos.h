#ifndef Lanuch_TOS_h_
#define Lanuch_TOS_h_
#include "Message_tos.h"

#pragma pack(1)
class Lanuch_tos:public Message_tos
{
	public:
		char account[ACCOUNTSIZE];
		char passwd[PASSWDSIZE];

		Lanuch_tos(){
		}

};


#endif

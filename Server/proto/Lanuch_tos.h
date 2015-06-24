#ifndef LANUCH_TOS_h_
#define LANUCH_TOS_h_
#include "Message.h"

//the accounts and passwd length ,decide on database
static const int ACCOUNTSIZE=8;
static const int PASSWDSIZE=16;

#pragma pack(1)
//#pragma pack(PACKSIZE)
class Lanuch_tos:public Message
{
	public:
		char account[ACCOUNTSIZE];
		int acclen;
		char passwd[PASSWDSIZE];
		int paslen;

		Lanuch_tos(){
		}

};


#endif

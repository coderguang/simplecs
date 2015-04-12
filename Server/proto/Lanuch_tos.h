#ifndef Lanuch_TOS_h
#define Lanuch_TOS_h_
#include "Message.h"

//the accounts and passwd length ,decide on database
static const int ACCOUNTSIZE=8;
static const int PASSWDSIZE=16;

#pragma pack(4)
class Lanuch_tos:public Message
{
	public:
		char account[ACCOUNTSIZE];
		char passwd[PASSWDSIZE];

		Lanuch_tos(){
		}

};


#endif
